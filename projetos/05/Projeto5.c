#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct no{
  int numero;
  struct no *esquerda;
  struct no *direita;
}No;

No **loadTreeFromFile(char *url);
int getHeight(No **raiz);
int insere_no(No **raiz, int valor);
void doMenu();
void acessaMenu();

int main(int argc, char const *argv[]) {

  No **arvore_binaria = loadTreeFromFile("resources/BSTs/bst2.txt");
  printf("\n\nAltura da árvore: %d\n", getHeight(arvore_binaria));
  acessaMenu();

  return 0;
}

No **loadTreeFromFile(char *url){
  int numero;
  FILE *arq;
  No **raiz = (No **)malloc(sizeof(No *));
  if (raiz != NULL){
    *raiz = NULL;
  }
  arq = fopen(url, "r");
  if (arq == NULL){
    printf("Não foi possível abrir o arquivo!\n" );
    exit(1);
  }else{
    while(!feof(arq)) {
      fscanf(arq, "%d", &numero);
      if (insere_no(raiz, numero)){
        printf("Inserção de nó concluída! Número inserido: %d\n", numero );
      }
    }
  }
  fclose(arq);
  return raiz;
}

int getHeight(No **raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int altura_esquerda = getHeight(&((*raiz)->esquerda));
  int altura_direita = getHeight(&((*raiz)->direita));
  if (altura_esquerda > altura_direita)
    return altura_esquerda + 1;
  else
    return altura_direita + 1;
}

int insere_no(No **raiz, int valor){
  if (raiz == NULL)
    return 0;
  No* novo;
  novo = (No *)malloc(sizeof(No));
  if (novo == NULL){
    return 0;
  }
  novo->numero = valor;
  novo->direita = NULL;
  novo->esquerda = NULL;
  if (*raiz == NULL)
    *raiz = novo;
  else{
    No* atual = *raiz;
    No* anterior = NULL;
    while (atual != NULL){
      anterior = atual;
      if (valor == atual->numero){
        free(novo); // Elemento ja existe
        return 0;
      }
      if (valor > atual->numero)
        atual = atual->direita;
      else
        atual = atual->esquerda;
    }
    if (valor > anterior->numero)
      anterior->direita = novo;
    else
      anterior->esquerda = novo;
  }
  return 1;
}

void doMenu(){
  printf("----------------------------------------------------------------------\n" );
  printf("\t\tBinary Tree\n" );
  printf("----------------------------------------------------------------------\n\n" );
  printf("Menu de opções\n" );
  printf("0 - LoadTreeFromFile \n" );
  printf("1 - ShowTree \n" );
  printf("2 - IsFull \n" );
  printf("3 - GetHeight \n" );
  printf("4 - RemoveValue \n" );
  printf("5 - PrintInOrder \n" );
  printf("6 - PrintPreOrder \n" );
  printf("7 - PrintPostOrder \n" );
  printf("8 - BalanceTree \n" );
  printf("9 - Sair do Programa\n" );
  printf("Escolha uma ação e digite seu número correspondente: " );
}

void acessaMenu(){
  char item_selecionado = 'I';
  doMenu();
  while (item_selecionado != '9'){
    scanf(" %c", &item_selecionado);
    switch (item_selecionado) {
      case '0':
        // LoadTreeFromFile
        doMenu();
        break;
      case '1':
      	// ShowTree
        doMenu();
        break;
      case '2':
      	// IsFull
        doMenu();
        break;
      case '3':
        // GetHeight
        doMenu();
        break;
      case '4':
      	// RemoveValue
        doMenu();
        break;
      case '5':
          // PrintInOrder
        doMenu();
        break;
      case '6':
        	// PrintPreOrder
        doMenu();
        break;
      case '7':
        	// PrintPostOrder
        doMenu();
        break;
      case '8':
          // BalanceTree
        doMenu();
        break;
      case '9':
        	// Sair do Programa
        break;
      default:
        printf("\nEntrada inválida! Digite novamente: ");
    }
  }
}
