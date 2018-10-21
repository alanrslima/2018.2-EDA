#include <stdio.h>
#include <stdlib.h>

struct contato {
  char nome[101];
  char celular[11];
  char endereco[101];
  unsigned int cep;
  char dataNascimento[11];
  struct contato *proximo;
  struct contato *anterior;
};

typedef struct contato Contato;

Contato *criaListaVazia();
void abreArquivo(Contato *lista);
Contato *insereInicioLista(Contato *lista, Contato *contato);


int main(int argc, char const *argv[]) {

  Contato *listaContatos;

  listaContatos = criaListaVazia();
  abreArquivo(listaContatos);

  return 0;
}

Contato *criaListaVazia()
{
    return NULL;
}

void abreArquivo(Contato *lista){
  FILE *arq;
  char ch;
  Contato *contato = (Contato *)malloc(sizeof(Contato));

  if (contato == NULL){
    printf("Falha ao alocar contato\n" );
    exit(-1);
  }

  arq = fopen("resources/contatos.txt", "r");
  if (arq == NULL){
     arq = fopen("resources/contatos.txt", "w");
  }

  while (ch != EOF){
    fscanf(arq, " %[^\n]", contato->nome);
    fscanf(arq, " %[^\n]", contato->celular);
    fscanf(arq, " %[^\n]", contato->endereco);
    fscanf(arq, " %ud", &contato->cep);
    fscanf(arq, " %[^\n]", contato->dataNascimento);
    contato->proximo = NULL;
    contato->anterior = NULL;

    ch = fgetc(arq);
    ch = fgetc(arq);

    if (ch == EOF){
      break;
    }
    lista = insereInicioLista(lista, contato);
  }
	fclose(arq);
}

Contato *insereInicioLista(Contato *lista, Contato *contato) {
  if (lista != NULL) {
    contato->proximo = lista;
    lista->anterior = contato;
  }
  return contato;
}
