#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_CODIGO 7
#define QTD_VOOS 64
#define MAX_NIVEL_COMBUSTIVEL 13

typedef struct voo{
    char codigo[TAM_CODIGO];
    char tipo_voo;
    int combustivel;
    int emergencia;
    struct voo* prox;
} Voo;

typedef struct fila{
    Voo *inicio;
    Voo *fim;
} Fila;


void set_hora_atual(int *horas, int *min);
void gera_aleatorios(int *aprox, int *decol, int *voos);
void aleatoriza_codigos_voos(char *codigos[QTD_VOOS]);
void insere_fila(Fila *fila, Voo *voo);
void gera_lista_decolagem(Voo *lista_inicial, Fila *fila);
void imprime_fila(Fila *fila);

Voo *gera_voos_decolagens_aproximacoes(int qtd_decolagens, int qtd_aproximacoes, char *codigos[QTD_VOOS]);
Voo *cria_voo(char *codigo, char tipo, int combustivel);
Voo *insere_voo(Voo *lista, Voo *novo_voo);
Voo *gera_lista_aproximacao(Voo *lista_inicial, Fila *fila);

Fila *cria_fila();

int verifica_avioes_sem_combustivel(Fila *fila);

void set_emergencia(Fila *fila);
void aciona_pista_aproximacao(Fila *aprox, int hora, int min, int *pista, int num_pista);
void aciona_pista_decolagem(Fila *decol, int hora, int min, int *pista, int num_pista);
void verifica_pistas(int *pista_1, int *pista_2, int *pista_3);
void incrementa_relogio(int *hora, int *min);
void verifica_combustivel(int *unidade_tempo, Fila *aprox);
void derruba_avioes(Fila *aprox);

void remove_fila(Fila *fila);
void libera_fila(Fila *fila);

int pistas_disponiveis(int pista_1, int pista_2, int pista_3);


int main(){

	char *codigos_voos[QTD_VOOS] = {"VG3001", "JJ4404", "LN7001", "TG1501", "GL7602", "TT1010", "AZ1009",
        "AZ1008", "AZ1010", "TG1506", "VG3002", "JJ4402", "GL7603", "RL7880", "AL0012", "TT4544",
        "TG1505", "VG3003", "JJ4403", "JJ4401", "LN7002", "AZ1002", "AZ1007", "GL7604", "AZ1006",
        "TG1503", "AZ1003", "JJ4403", "AZ1001", "LN7003", "AZ1004", "TG1504", "AZ1005", "TG1502",
        "GL7601", "TT4500", "RL7801", "JJ4410", "GL7607", "AL0029", "VV3390", "VV3392", "GF4681",
        "GF4690", "AZ1020", "JJ4435", "VG3010", "LF0920", "AZ1065", "LF0978", "RL7867", "TT4502",
        "GL7645", "LF0932", "JJ4434", "TG1510", "TT1020", "AZ1098", "BA2312", "VG3030", "BA2304",
        "KL5609", "KL5610", "KL5611"};
	int NVoos = 0, NAproximacoes = 0, NDecolagens = 0, CombA = 0;

	gera_aleatorios(&NAproximacoes, &NDecolagens, &NVoos);
    aleatoriza_codigos_voos(codigos_voos);
    Voo *lista_voos_inicial = gera_voos_decolagens_aproximacoes(NDecolagens, NAproximacoes, codigos_voos);
    
    Fila *fila_aproximacoes = cria_fila();
    lista_voos_inicial = gera_lista_aproximacao(lista_voos_inicial, fila_aproximacoes);
    
    Fila *fila_decolagens = cria_fila();
    gera_lista_decolagem(lista_voos_inicial, fila_decolagens);
    
    int horas, minutos;
    set_hora_atual(&horas, &minutos);
    
    printf("---------------------------------------------------------------------------------\n");
    printf("Aeroporto Internacional de Brasília\n");
    printf("Hora Inicial: %d:%d\n", horas, minutos);
    printf("Fila de Pedidos: [código do voo – P/D – prioridade]\n");
    printf("NVoos: %d\n", NVoos);
    printf("Naproximações: %d\n", NAproximacoes);
    printf("NDecolagens: %d\n", NDecolagens);
    printf("---------------------------------------------------------------------------------\n\n\n");
    
    printf("Aviões em aproximação:\n\n");
    imprime_fila(fila_aproximacoes);
    printf("\n\nAviões em decolagem:\n\n");
    imprime_fila(fila_decolagens);
    
    printf("\n\n----------------------------------------------");
    printf("\nListagem de eventos:\n");
    printf("----------------------------------------------\n\n");
    
    int pista_1, pista_2, pista_3, unidade_tempo = 1;
    
    while (fila_aproximacoes->inicio != NULL || fila_decolagens->inicio != NULL ){
        
        derruba_avioes(fila_aproximacoes);
        
        int avioes_sem_combustivel = 0;
        if (pistas_disponiveis(pista_1, pista_2, pista_3)){
           avioes_sem_combustivel = verifica_avioes_sem_combustivel(fila_aproximacoes);
        }
        // PISTA 1
        aciona_pista_aproximacao(fila_aproximacoes, horas, minutos, &pista_1, 1);
        aciona_pista_decolagem(fila_decolagens, horas, minutos, &pista_1, 1);
        // PISTA 2
        aciona_pista_aproximacao(fila_aproximacoes, horas, minutos, &pista_2, 2);
        aciona_pista_decolagem(fila_decolagens, horas, minutos, &pista_2, 2);
        // PISTA 3
        if (avioes_sem_combustivel >= 3){
            aciona_pista_aproximacao(fila_aproximacoes, horas, minutos, &pista_3, 3);
        }
        aciona_pista_decolagem(fila_decolagens, horas, minutos, &pista_3, 3);
        
        verifica_pistas(&pista_1, &pista_2, &pista_3);
        verifica_combustivel(&unidade_tempo, fila_aproximacoes);
        set_emergencia(fila_aproximacoes);
        incrementa_relogio(&horas, &minutos);
        unidade_tempo ++;
    }
    libera_fila(fila_aproximacoes);
    libera_fila(fila_decolagens);

	return 0;
}

int pistas_disponiveis(int pista_1, int pista_2, int pista_3){
    if ((pista_1 == 0) || (pista_2 == 0) || (pista_3 == 0)){
        return 1;
    }else{
        return 0;
    }
}

void derruba_avioes(Fila *aprox){
    Voo *avioes_queda = aprox->inicio;
    while(avioes_queda != NULL) {
        if(avioes_queda->emergencia) {
            printf("----------------------------------------------\n");
            printf(" ** ALERTA CRÍTICO: Aeronave irá cair **\n\n");
            printf("Código do voo: %s - %c - %d\n", avioes_queda->codigo, avioes_queda->tipo_voo, avioes_queda->combustivel);
            printf("Status: [Aeronave Caiu]\n");
            printf("----------------------------------------------\n\n");
            remove_fila(aprox);
        }
        avioes_queda = avioes_queda->prox;
    }
}

void incrementa_relogio(int *hora, int *min){
    *min += 5;
    if(*min >= 60) {
        *min = *min - 60;
        *hora += 1;
        if(*hora >= 24) {
            *hora = 0;
        }
    }
}

void verifica_combustivel(int *unidade_tempo, Fila *aprox){
    if(*unidade_tempo == 10) {
        Voo *consome_combustivel = aprox->inicio;
        while(consome_combustivel != NULL) {
            consome_combustivel->combustivel = (consome_combustivel->combustivel) - 1;
            consome_combustivel = consome_combustivel->prox;
        }
        consome_combustivel = aprox->inicio;
        *unidade_tempo = 0;
    }
}

void verifica_pistas(int *pista_1, int *pista_2, int *pista_3){
    if (*pista_1 > 0){
        *pista_1 -= 1;
    }
    if (*pista_2 > 0){
        *pista_2 -= 1;
    }
    if (*pista_3 > 0){
        *pista_3 -= 1;
    }
}

void aciona_pista_aproximacao(Fila *aprox, int hora, int min, int *pista, int num_pista){
    if (*pista == 0){
        if (aprox->inicio != NULL){
            printf("----------------------------------------------\n");
            printf("Código do voo: %s - %c - %d\n", aprox->inicio->codigo, aprox->inicio->tipo_voo, aprox->inicio->combustivel);
            printf("Status: [Aeronave Pousou]\n");
            printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, min);
            printf("Número da pista: %d\n", num_pista);
            printf("----------------------------------------------\n\n");
            *pista = 4;
            remove_fila(aprox);
        }
    }
}

void aciona_pista_decolagem(Fila *decol, int hora, int min, int *pista, int num_pista){
    if (*pista == 0){
        if(decol->inicio != NULL){
            printf("----------------------------------------------\n");
            printf("Código do voo: %s - %c\n", decol->inicio->codigo, decol->inicio->tipo_voo);
            printf("Status: [Aeronave Decolou]\n");
            printf("Horário do ínicio do procedimento: %02d:%02d\n", hora, min);
            printf("Número da pista: %d\n", num_pista);
            printf("----------------------------------------------\n\n");
            *pista = 2;
            remove_fila(decol);
        }
    }
}

void set_emergencia(Fila *fila){
    Voo *confere_combustivel = fila->inicio;
    while(confere_combustivel != NULL) {
        if(confere_combustivel->combustivel == 0) {
            confere_combustivel->emergencia = 1;
        }
        confere_combustivel = confere_combustivel->prox;
    }
}


int verifica_avioes_sem_combustivel(Fila *fila){
    int aux = 0;
    Voo *confere_combustivel = fila->inicio;
    while(confere_combustivel != NULL) {
        if(confere_combustivel->combustivel == 0) {
            aux++;
        }
        confere_combustivel = confere_combustivel->prox;
    }
    if(aux >= 3) {
        printf("\n---------------------------------------");
        printf("\nALERTA GERAL DE DESVIO DE AERONAVE\n");
        printf("_________________________________________\n");
    }
    return aux;
}

void gera_aleatorios(int *aprox, int *decol, int *voos){
	srand(time(NULL));
	*aprox = 10 + (rand() % 22);
	srand(time(NULL)+2);
	*decol = 10 + (rand() % 22);
	*voos = *aprox + *decol;
}

void aleatoriza_codigos_voos(char *codigos[QTD_VOOS]){
    char *temp;
    for (int i = 0; i < QTD_VOOS; i++){
        srand(time(NULL)+3);
        int r = rand() % QTD_VOOS;
        temp = codigos[i];
        codigos[i] = codigos[r];
        codigos[r] = temp;
    }
}

Voo *gera_voos_decolagens_aproximacoes(int qtd_decolagens, int qtd_aproximacoes, char *codigos[QTD_VOOS]){
    Voo *lista_voos = NULL;
    // Gera voos para decolagens
    for (int i=0; i<qtd_decolagens; i++){
        Voo *novo_voo = cria_voo(codigos[i], 'D', -1);
        lista_voos = insere_voo(lista_voos, novo_voo);
    }
    // Gera voos para aproximaçoes
    for (int i=qtd_decolagens; i<(qtd_decolagens+qtd_aproximacoes); i++){
//        int combustivel = (rand() % MAX_NIVEL_COMBUSTIVEL);
        int combustivel = 0;
        Voo *novo_voo = cria_voo(codigos[i], 'A', combustivel);
        lista_voos = insere_voo(lista_voos, novo_voo);
    }
    return lista_voos;
}

Voo *cria_voo(char *codigo, char tipo, int combustivel) {
    // Aloca uma struct de voo
    Voo *novo_voo = (Voo *)malloc(sizeof(Voo));
    if (novo_voo == NULL){
        printf("Erro na alocação!\n");
        exit(1);
    }
    // Atribui os valores para a struc
    strcpy(novo_voo->codigo, codigo);
    novo_voo->tipo_voo = tipo;
    novo_voo->combustivel = combustivel;
    novo_voo->emergencia = 0;
    novo_voo->prox = NULL;
    return novo_voo;
}

Voo *insere_voo(Voo *lista, Voo *novo_voo) {
    if(lista != NULL) {
        novo_voo->prox = lista;
    }
    return novo_voo;
}

Fila *cria_fila(){
    Fila *fila = (Fila *)malloc(sizeof(Fila));
    if (fila != NULL) {
        fila->inicio = NULL;
        fila->fim = NULL;
    }else{
        printf("Erro na alocação!\n");
        exit(1);
    }
    return fila;
}

void insere_fila(Fila *fila, Voo *voo) {
    voo->prox = NULL;
    if (fila->fim == NULL) {
        fila->inicio = voo;
    } else {
        fila->fim->prox = voo;
    }
    fila->fim = voo;
}

Voo *gera_lista_aproximacao(Voo *lista_inicial, Fila *fila){
    Voo *lista = lista_inicial;
    for (int i = 0; i < 13; i++) {
        Voo *elemento_atual = lista;
        Voo *elemento_anterior = NULL;
        while (elemento_atual != NULL) {
            
            if (elemento_atual->combustivel == i) {
                if (elemento_atual == lista) {
                    lista = lista->prox;
                }else {
                    elemento_anterior->prox = elemento_atual->prox;
                }
                Voo *aux = elemento_atual->prox;
                insere_fila(fila, elemento_atual);
                elemento_atual = aux;
            }else {
                elemento_anterior = elemento_atual;
                elemento_atual = elemento_atual->prox;
            }
        }
    }
    return lista;
}

void gera_lista_decolagem(Voo *lista_inicial, Fila *fila){
    Voo *elemento_atual = lista_inicial;
    Voo *elemento_proximo = NULL;
    
    while(elemento_atual != NULL) {
        elemento_proximo = elemento_atual->prox;
        insere_fila(fila, elemento_atual);
        elemento_atual = elemento_proximo;
    }
}

void imprime_fila(Fila *fila){
    Voo *voo = fila->inicio;
    while (voo != NULL) {
        printf("[%s-%c-%d]\n", voo->codigo, voo->tipo_voo, voo->combustivel);
        voo = voo->prox;
    }
}

void set_hora_atual(int *horas, int *min){
    char hora_atual[9] = __TIME__;
    char h[3], m[3];
    for (int i=0; i<9; i++){
        if (i == 0 || i == 1){
            h[i] = hora_atual[i];
            if (i == 2){
                h[i] = '\0';
            }
        }else if(i == 3 || i == 4){
            m[i-3] = hora_atual[i];
            if (i == 5){
                h[i-3] = '\0';
            }
        }
    }
    *horas = atoi(h);
    *min = atoi(m);
}

void remove_fila(Fila *fila) {
    Voo *voo = fila->inicio;
    fila->inicio = fila->inicio->prox;
    if (fila->inicio == NULL) {
        fila->fim = NULL;
    }
    free(voo);
}

void libera_fila(Fila *fila) {
    if (fila != NULL) {
        Voo *voo;
        while (fila->inicio != NULL) {
            voo = fila->inicio;
            fila->inicio = fila->inicio->prox;
            free(voo);
        }
        free(fila);
    }
}
