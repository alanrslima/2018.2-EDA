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
    struct voo* prox;
} Voo;

typedef struct fila{
    Voo *inicio;
    Voo *fim;
} Fila;


void gera_aleatorios(int *aprox, int *decol, int *voos);
void aleatoriza_codigos_voos(char *codigos[QTD_VOOS]);
void insere_fila(Fila *fila, Voo *voo);
void gera_lista_decolagem(Voo *lista_inicial, Fila *fila);

Voo *gera_voos_decolagens_aproximacoes(int qtd_decolagens, int qtd_aproximacoes, char *codigos[QTD_VOOS]);
Voo *cria_voo(char *codigo, char tipo, int combustivel);
Voo *insere_voo(Voo *lista, Voo *novo_voo);
Voo *gera_lista_aproximacao(Voo *lista_inicial, Fila *fila);


Fila *cria_fila();


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
    
    
    
    
    
    
    printf("Aproximacoes:%d Decolagens:%d Voos:%d\n",NAproximacoes, NDecolagens, NVoos);
    Voo *atual = fila_aproximacoes->inicio;
    int i = 0;
    while (atual != NULL){
        printf("Código:%s  Combustivel:%d  Tipo:%c\n", atual->codigo, atual->combustivel, atual->tipo_voo);
        atual = atual->prox;
        i++;
    }
    printf("QUANTIDADE = %d\n\n\n", i);
    
    atual = fila_decolagens->inicio;
    i = 0;
    while (atual != NULL){
        printf("Código:%s  Combustivel:%d  Tipo:%c\n", atual->codigo, atual->combustivel, atual->tipo_voo);
        atual = atual->prox;
        i++;
    }
    printf("QUANTIDADE = %d", i);
    

	return 0;
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
        int combustivel = (rand() % MAX_NIVEL_COMBUSTIVEL);
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


