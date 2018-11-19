#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

typedef struct no{
  int numero;
  struct no *esquerda;
  struct no *direita;
}No;

No **loadTreeFromFile(char *url);
int getHeight(No **raiz);
void printPreOrder(No **raiz);
void printInOrder(No **raiz);
void printPosOrder(No **raiz);
int removeValue(No **raiz, int valor);

No *removeAtual(No *atual);
void printTree(No **raiz, char *prefix);
int totalNos(No **raiz);
int insereNo(No **raiz, int valor);
int arvoreNula(No **raiz);
void liberaArvore(No **raiz);
void liberaNo(No *no);

// Funções criação de Menu
void doMenu();
void acessaMenu(No **arvore_binaria);

int main(int argc, char const *argv[]) {
  No **arvore_binaria;
  acessaMenu(arvore_binaria);
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
      if (insereNo(raiz, numero)){
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

int insereNo(No **raiz, int valor){
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

void printPreOrder(No **raiz){
  if (raiz == NULL)
    return;
  if (*raiz != NULL){
    printf("%d, ", (*raiz)->numero);
    printPreOrder(&((*raiz)->esquerda));
    printPreOrder(&((*raiz)->direita));
  }
}

void printPosOrder(No **raiz){
  if (raiz == NULL)
    return;
  if (*raiz != NULL){
    printPreOrder(&((*raiz)->esquerda));
    printPreOrder(&((*raiz)->direita));
    printf("%d, ", (*raiz)->numero);
  }
}

void printInOrder(No **raiz){
  if (raiz == NULL)
    return;
  if (*raiz != NULL){
    printInOrder(&((*raiz)->esquerda));
    printf("%d, ", (*raiz)->numero);
    printPreOrder(&((*raiz)->direita));
  }
}

int arvoreNula(No **raiz){
  if (raiz == NULL)
    return 1;
  if (*raiz == NULL)
    return 1;
  return 0;
}

void liberaNo(No *no){
  if (no == NULL)
    return;
  liberaNo(no->esquerda);
  liberaNo(no->direita);
  free(no);
  no = NULL;
}

void liberaArvore(No **raiz){
  if (raiz == NULL){
    return;
  liberaNo(*raiz);
  free(raiz);
  }
}

void printTree(No **raiz, char *prefix){
  if (arvoreNula(raiz)){
    printf("A árvore é NULA\n" );
    return;
  }else{
    if (strcmp(prefix, "Pos") == 0){
      printPosOrder(raiz);
    }else if (strcmp(prefix, "Pre") == 0){
      printPreOrder(raiz);
    }else if (strcmp(prefix, "In") == 0){
      printInOrder(raiz);
    }else{
      printf("Prefixo incorreto\n" );
    }
  }
}

int removeValue(No **raiz, int valor){
  if (raiz == NULL)
    return 0;
  No *anterior = NULL;
  No *atual = *raiz;
  while (atual != NULL){
    if (valor == atual->numero){
      if (atual == *raiz)
        *raiz = removeAtual(atual);
      else{
        if (anterior->direita == atual)
          anterior->direita = removeAtual(atual);
        else
          anterior->esquerda = removeAtual(atual);
      }
      return 1;
    }
    anterior = atual;
    if (valor > atual->numero)
      atual = atual->direita;
    else
      atual = atual->esquerda;
  }
  return 0;
}

No *removeAtual(No *atual){
  No *no1, *no2;
  // Trata o caso do no removido ser nó folha ou com um filho
  if (atual->esquerda == NULL){
    no2 = atual->direita;
    free(atual);
    return no2;
  }
  no1 = atual;
  no2 = atual->esquerda;
  // Procura filho mais a direita na sub-arvore da esquerda
  while (no2->direita != NULL){
    no1 = no2;
    no2 = no2->direita;
  }
  // Copia o filho mais da direita na sub-arvore da esquerda para o lugar do nó removido
  if (no1 != atual){
    no1->direita = no2->esquerda;
    no2->esquerda = atual->esquerda;
  }
  no2->direita = atual->direita;
  free(atual);
  return no2;
}

int totalNos(No **raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int altura_esquerda = totalNos(&((*raiz)->esquerda));
  int altura_direita = totalNos(&((*raiz)->direita));
  return (altura_esquerda + altura_direita + 1);
}

void doMenu(){
  printf("\n\n----------------------------------------------------------------------\n" );
  printf("\t\t\tBinary Tree\n" );
  printf("----------------------------------------------------------------------\n\n" );
  printf("\tMENU DE OPÇÕES\n\n" );
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
  printf("----------------------------------------------------------------------\n" );
  printf("Escolha uma ação e digite seu número correspondente: " );
}

void acessaMenu(No **arvore_binaria){
  char item_selecionado = 'I';
  char url[40];
  int numero_removido;
  doMenu();
  while (item_selecionado != '9'){
    scanf(" %c", &item_selecionado);
    switch (item_selecionado) {
      case '0':
        if (arvoreNula(arvore_binaria) == 0){
          printf("Apagando árvore atual...\n");
          liberaArvore(arvore_binaria);
        }
        printf("Digite o caminho do arquivo: ");
        scanf("%s", url);
        arvore_binaria = loadTreeFromFile(url);
        doMenu();
        break;
      case '1':
      	// ShowTree
        doMenu();
        break;
      case '2':
      	// IsFull
        break;
      case '3':
          printf("Altura da árvore = %d\n", getHeight(arvore_binaria));
        doMenu();
        break;
      case '4':
        printf("Digite o número a ser removido da árvore: ");
        scanf("%d", &numero_removido);
        if (removeValue(arvore_binaria, numero_removido)){
          printf("Nó removido com sucesso!\n" );
        }else{
          printf("Valor não está presente na árvore!\n" );
        }
        doMenu();
        break;
      case '5':
        printTree(arvore_binaria, "In");
        doMenu();
        break;
      case '6':
        printTree(arvore_binaria, "Pre");
        doMenu();
        break;
      case '7':
        printTree(arvore_binaria, "Pos");
        doMenu();
        break;
      case '8':
          // BalanceTree
        doMenu();
        break;
      case '9':
        	printf("\nSaindo do programa... Até a proxima!\n" );
        break;
      default:
        printf("\nEntrada inválida! Digite novamente: ");
    }
  }
}
