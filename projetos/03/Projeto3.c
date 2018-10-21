#include <stdio.h>
#include <stdlib.h>
#include <curses.h>

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
void imprimirContatos(Contato *lista);
void criaMenu();
void acessaMenu(Contato *lista);


int main(int argc, char const *argv[]) {

  Contato *listaContatos;

  listaContatos = criaListaVazia();
  listaContatos = abreArquivo(listaContatos);
  criaMenu();
  acessaMenu(listaContatos);

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

void imprimirContatos(Contato *lista) {

  Contato *index = lista;
  if (index == NULL) {
    printf("Lista de contatos vazia!\n");
  }

  printf("\n Lista de contatos: \n");
  while (index != NULL) {
    printf("\nNome: %s\n", index->nome);
    printf("Telefone: %s\n", index->celular);
    printf("Endereço: %s\n", index->endereco);
    printf("CEP: %d\n", index->cep);
    printf("Aniversário: %s\n", index->dataNascimento);
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

void criaMenu(){
  printf("\n\n\n----------------------------------------------------------\n");
  printf(">>>>>>>>>>>>>>>>>>> LISTA DE CONTATOS <<<<<<<<<<<<<<<<<<<<\n");
  printf("----------------------------------------------------------\n\n");
  printf("\t Menu de opções, selecione a desejeda: \n\n");
  printf("  (1) Inserir novo contato \n");
  printf("  (2) Remover contatos com base no nome \n");
  printf("  (3) Visualizar contato com base no nome \n");
  printf("  (4) Visualizar todos os contatos em ordem alfabetica \n");
  printf("  (5) Sair \n\n");
  printf("----------------------------------------------------------\n");
  printf("Digite aqui: ");
}

void acessaMenu(Contato *lista){
  char itemSelecionado = '0';

  while (itemSelecionado != '5'){
    scanf(" %c", &itemSelecionado);
    switch (itemSelecionado) {
      case '1':
        printf("\n\nInserir novo contato\n");
        criaMenu();
        break;
      case '2':
        printf("\n\nRemover contato com base no nome\n");
        criaMenu();
        break;
      case '3':
        printf("\n\nVisualizar contato com base no nome\n");
        criaMenu();
        break;
      case '4':
        imprimirContatos(lista);
        criaMenu();
        break;
      case '5':
        printf("\n\nSair do programa \n (Escrever arquivo e limpar lista da memoria)\n\n");
        break;
      default:
        printf("Entrada inválida! Digite novamente: ");
    }
  }
}
