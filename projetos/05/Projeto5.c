#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define espaco 5

typedef struct no{
  int numero;
  int altura;
  struct no *esquerda;
  struct no *direita;
}No;

// Funções obrigatorias
No **loadTreeFromFile(char *url);
int getHeight(No **raiz);
void printPreOrder(No **raiz);
void printInOrder(No **raiz);
void printPosOrder(No **raiz);
int removeValue(No **raiz, int valor);
int isFull(No **raiz);
void showTree(No **raiz);

// Funções auxiliares
No *removeAtual(No *atual);
void printTree(No **raiz, char *prefix);
int totalNos(No **raiz);
int insereNo(No **raiz, int valor);
int arvoreNula(No **raiz);
void liberaArvore(No **raiz);
void liberaNo(No *no);
int saveTree(No **root, int is_left, int offset, int depth, char **s);

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
  if (arvoreNula(raiz))
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

int isFull(No **raiz){
  if (arvoreNula(raiz))
    return 0;
  // Caso tenha apenas um elemento
	if (((*raiz)->esquerda == NULL) && ((*raiz)->direita == NULL))
		return 1;

	if (((*raiz)->esquerda) && ((*raiz)->direita))
		 if (isFull(&((*raiz)->esquerda)) && isFull(&((*raiz)->direita))) {
       return 1;
     }

  return 0;
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
  printf("\n\n\n\n----------------------------------------------------------------------\n" );
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
  printf("7 - PrintPosOrder \n" );
  printf("8 - BalanceTree \n" );
  printf("9 - Sair do Programa\n" );
  printf("----------------------------------------------------------------------\n" );
  printf("Escolha uma ação e digite seu número correspondente: " );
}

void acessaMenu(No **arvore_binaria){
  char item_selecionado = 'I';
  char url[40];
  int numero_removido;
  arvore_binaria = loadTreeFromFile("resources/BSTs/bst1.txt");
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
        showTree(arvore_binaria);
        doMenu();
        break;
      case '2':
      	if (isFull(arvore_binaria)){
          printf("A árvore é cheia!\n" );
        }else{
          printf("A árvore não é cheia!\n" );
        }
        doMenu();
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

void showTree(No **root) {
  int tam = ((getHeight(root) * 2) + 1);

  char **show = (char **)malloc( tam * sizeof(char *));
	for (int i = 0; i < tam; i++) {
		show[i] = (char *)malloc(255 * sizeof(char));
		sprintf(show[i], "%80s", " ");
	}
	saveTree(root, 0, 0, 0, show);

	for (int i = 0; i < tam; i++) {
    int tamStr = strlen(show[i]);
    for(int j = 0; j < tamStr; j++){
        printf("%c", show[i][j]);
    }
    printf("\n");
  }

    for (int i = 0; i < tam; i++)
        free(show[i]);
    free(show);
}

int saveTree(No **root, int is_left, int offset, int depth, char **s) {
    char b[20];
    int width = 5;

    if (!(*root))
      return 0;

    sprintf(b, " %3d ", (*root)->numero);

    int left  = saveTree(&((*root)->esquerda),  1, offset, depth + 1, s);
    int right = saveTree(&((*root)->direita), 0, offset + left + width, depth + 1, s);

    for (int i = 0; i < width; i++)
        s[2 * depth][offset + left + i] = b[i];

    if (depth && is_left) {

        for (int i = 0; i < width + right; i++)
            s[2 * depth - 1][offset + left + width/2 + i] = '*';

        s[2 * depth - 1][offset + left + width/2] = '/';
        s[2 * depth - 1][offset + left + width + right + width/2] = ':';

    } else if (depth && !is_left) {
        for (int i = 0; i < left + width; i++)
            s[2 * depth - 1][offset - width/2 + i] = '*';

        s[2 * depth - 1][offset + left + width/2] = 92;
        s[2 * depth - 1][offset - width/2 - 1] = ':';
    }
    return left + width + right;
}
