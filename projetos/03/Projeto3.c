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
Contato *abreArquivo();
Contato *insereInicioLista(Contato *lista, Contato *contato);
void imprimir_contatos(Contato *lista);


int main(int argc, char const *argv[]) {

  Contato *listaContatos;

  listaContatos = criaListaVazia();
  listaContatos = abreArquivo(listaContatos);
  imprimir_contatos(listaContatos);

  return 0;
}

Contato *criaListaVazia()
{
    return NULL;
}

Contato *abreArquivo(){
  FILE *arq;
  char ch;

  Contato *lista =criaListaVazia();

  arq = fopen("resources/contatos.txt", "r");
  if (arq == NULL){
     arq = fopen("resources/contatos.txt", "w");
  }

  while (ch != EOF){

    Contato *contato = (Contato *)malloc(sizeof(Contato));
    if (contato == NULL){
      printf("Falha ao alocar contato\n" );
      exit(-1);
    }

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
  return lista;
}

void imprimir_contatos(Contato *lista) {

  Contato *index = lista;
  if (index == NULL) {
    printf("Lista de contatos vazia!\n");
  }

  while (index != NULL) {
    printf("Nome: %s\n", index->nome);
    printf("Telefone: %s\n", index->celular);
    printf("Endereço: %s\n", index->endereco);
    printf("CEP: %d\n", index->cep);
    printf("Aniversário: %s\n\n", index->dataNascimento);
    index = index->proximo;
  }
}

Contato *insereInicioLista(Contato *lista, Contato *contato) {
  if (lista != NULL) {
    contato->proximo = lista;
    lista->anterior = contato;
  }
  return contato;
}
