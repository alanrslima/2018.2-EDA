#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define TAM_CODIGO 7
#define QTD_VOOS 64

typedef struct voo{
    char codigo[TAM_CODIGO];
    char tipo_voo;
    int combustivel;
//    int prioridade;
    struct voo* prox;
} Voo;

typedef struct fila{
    Voo *inicio;
    Voo *fim;
} Fila;


void gera_aleatorios(int *aprox, int *decol, int *voos);
void aleatoriza_codigos_voos(char *codigos[QTD_VOOS]);

Voo *gera_voos_decolagens_aproximacoes(int qtd_decolagens, int qtd_aproximacoes, char *codigos[QTD_VOOS]);
Voo *cria_voo(char *codigo, char tipo, int combustivel);
Voo *insere_voo(Voo *lista, Voo *novo_voo);

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
    Voo *lista = gera_voos_decolagens_aproximacoes(NDecolagens, NAproximacoes, codigos_voos);

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
    Voo *lista = NULL;
    // Gera voos para decolagens
    for (int i=0; i<qtd_decolagens; i++){
        Voo *novo_voo = cria_voo(codigos[i], 'D', -1);
        lista = insere_voo(lista, novo_voo);
    }
    // Gera voos para aproximaçoes
    for (int i=qtd_decolagens; i<(qtd_decolagens+qtd_aproximacoes); i++){
        int combustivel = (rand() % 13);
        Voo *novo_voo = cria_voo(codigos[i], 'A', combustivel);
        lista = insere_voo(lista, novo_voo);
    }
    return lista;
}

Voo *cria_voo(char *codigo, char tipo, int combustivel) {
    // Aloca uma struct de voo
    Voo *novo_voo = (Voo *)malloc(sizeof(Voo));
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
