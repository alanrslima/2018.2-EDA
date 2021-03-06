#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct no{
  int numero;
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
int searchValue(No **raiz, int valor);

// Funções auxiliares
No *removeAtual(No *atual);
void printTree(No **raiz, char *prefix);
int insereNo(No **raiz, int valor);
int arvoreNula(No **raiz);
void liberaArvore(No **raiz);
void liberaNo(No *no);
char **criaMatrizShow(int altura);
void printaMatrizShow(char **show, int altura);
int salvaMatrizShow(No **raiz, char **show, int direcao_esquerda, int deslocamento, int nivel );
int arvoreBalanceada(No **raiz);


// Funções criação de Menu
void doMenu();
void acessaMenu(No **arvore_binaria);
void doMenuArquivos();
char *acessaMenuArquivos();


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
    printPosOrder(&((*raiz)->esquerda));
    printPosOrder(&((*raiz)->direita));
    printf("%d, ", (*raiz)->numero);
  }
}

void printInOrder(No **raiz){
  if (raiz == NULL)
    return;
  if (*raiz != NULL){
    printInOrder(&((*raiz)->esquerda));
    printf("%d, ", (*raiz)->numero);
    printInOrder(&((*raiz)->direita));
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
    printf("ATENÇÃO! A árvore está vazia!\n" );
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

int searchValue(No **raiz, int valor){
  if (arvoreNula(raiz))
    return 0;
  int nivel = 0;
  No *atual = *raiz;
  No *pai = NULL;
  while (atual != NULL){
    nivel++;
    if (valor == atual->numero){
      printf("Nível do nó = %d\n", nivel);
      if (pai == NULL){
        printf("O valor é raiz da árvore, portanto não tem pai e nem irmão\n");
      }else{
        printf("Valor do pai = %d\n", pai->numero);
        if (pai->esquerda){
          if (pai->esquerda->numero != atual->numero)
            printf("Seu irmão está a esquerda e seu valor é = %d\n", pai->esquerda->numero);
        }
        if (pai->direita){
          if (pai->direita->numero != atual->numero)
            printf("Seu irmão está a direita e seu valor é = %d\n", pai->direita->numero);
        }
        if (!pai->direita || !pai->esquerda)
          printf("Este nó não tem irmão!\n" );
      }
      return 1;
    }
    pai = atual;
    if (valor > atual->numero)
      atual = atual->direita;
    else
      atual = atual->esquerda;
  }
  return 0;
}

void doMenu(){
  printf("\n\n\n\n----------------------------------------------------------------------\n" );
  printf("\t\t\tBinary Tree\n" );
  printf("----------------------------------------------------------------------\n\n" );
  printf("\tMENU DE OPÇÕES\n\n" );
  printf("0 - LoadTreeFromFile \n" );
  printf("1 - ShowTree \n" );
  printf("2 - IsFull \n" );
  printf("3 - searchValue\n" );
  printf("4 - GetHeight \n" );
  printf("5 - RemoveValue \n" );
  printf("6 - PrintInOrder \n" );
  printf("7 - PrintPreOrder \n" );
  printf("8 - PrintPosOrder \n" );
  printf("9 - BalanceTree \n" );
  printf("E - Sair do Programa\n" );
  printf("----------------------------------------------------------------------\n" );
  printf("Escolha uma ação e digite seu número correspondente: " );
}

void doMenuArquivos(){
  printf("\n\n\n\n----------------------------------------------------------------------\n" );
  printf("\t\t\tArquivos BST\n" );
  printf("----------------------------------------------------------------------\n\n" );
  printf("\tARQUIVOS DISPONÍVEIS\n\n" );
  printf("1 - bst1.txt \n" );
  printf("2 - bst2.txt \n" );
  printf("3 - bst3.txt \n" );
  printf("4 - bst4.txt \n" );
  printf("5 - bst5.txt \n" );
  printf("6 - bst6.txt \n" );
  printf("----------------------------------------------------------------------\n" );
  printf("Escolha um arquivo e digite seu número correspondente: " );
}

char *acessaMenuArquivos(){
  char item_selecionado = '0';
  doMenuArquivos();
  scanf(" %c", &item_selecionado);
  switch (item_selecionado) {
    case '1':
      return "resources/BSTs/bst1.txt";
      break;
    case '2':
      return "resources/BSTs/bst2.txt";
      break;
    case '3':
      return "resources/BSTs/bst3.txt";
      break;
    case '4':
      return "resources/BSTs/bst4.txt";
      break;
    case '5':
      return "resources/BSTs/bst5.txt";
      break;
    case '6':
      return "resources/BSTs/bst6.txt";
      break;
    default:
      return "Abort";
  }
}

void acessaMenu(No **arvore_binaria){
  char item_selecionado = 'I';
  char *url;
  int numero_removido, numero_buscado;
  doMenu();
  while (item_selecionado != 'E'){
    scanf(" %c", &item_selecionado);
    switch (item_selecionado) {
      case '0':
        url = acessaMenuArquivos();
        if (strcmp(url, "Abort") == 0){
          printf("Arquivo inválido! \n");
        }else{
          if (arvoreNula(arvore_binaria) == 0){
            printf("Apagando árvore atual...\n");
            liberaArvore(arvore_binaria);
          }
          arvore_binaria = loadTreeFromFile(url);
        }
        doMenu();
        break;
      case '1':
        if (arvoreNula(arvore_binaria))
          printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
          showTree(arvore_binaria);
        }
        doMenu();
        break;
      case '2':
        if (arvoreNula(arvore_binaria))
          printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
          if (isFull(arvore_binaria))
            printf("A árvore é cheia!\n" );
          else
            printf("A árvore não é cheia!\n" );
        }
        doMenu();
        break;
      case '3':
        if (arvoreNula(arvore_binaria))
        printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
          printf("Digite o número a ser buscado na árvore: ");
          scanf("%d", &numero_buscado);
          if (!searchValue(arvore_binaria, numero_buscado)){
            printf("Este valor não esta presente na árvore!\n" );
          }
        }
        doMenu();
        break;
      case '4':
        if (arvoreNula(arvore_binaria))
          printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
          printf("Altura da árvore = %d\n", getHeight(arvore_binaria));
        }
        doMenu();
        break;
      case '5':
        if (arvoreNula(arvore_binaria))
          printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
          printf("Digite o número a ser removido da árvore: ");
          scanf("%d", &numero_removido);
          if (removeValue(arvore_binaria, numero_removido)){
            printf("Nó removido com sucesso!\n" );
          }else{
            printf("Valor não está presente na árvore!\n" );
          }
        }
        doMenu();
        break;
      case '6':
        printTree(arvore_binaria, "In");
        doMenu();
        break;
      case '7':
        printTree(arvore_binaria, "Pre");
        doMenu();
        break;
      case '8':
        printTree(arvore_binaria, "Pos");
        doMenu();
        break;
      case '9':
        if (arvoreNula(arvore_binaria))
          printf("ATENÇÃO! A árvore está vazia!\n" );
        else{
        if (arvoreBalanceada(arvore_binaria))
            printf("A árvore já está balanceada!\n" );
          else{
            printf("A árvore não está balanceada!\n" );
          }
        }
        doMenu();
        break;
      case 'E':
        if (!arvoreNula(arvore_binaria)){
          printf("Apagando árvore ...\n");
          liberaArvore(arvore_binaria);
        }
        printf("\nSaindo do programa... Até a proxima!\n" );
        break;
      default:
        printf("\nEntrada inválida! Digite novamente: ");
    }
  }
}

void showTree(No **raiz) {
  int altura = ((getHeight(raiz) * 2) + 1);
  char **matriz_show = criaMatrizShow(altura);
	salvaMatrizShow(raiz, matriz_show, 0, 0, 0);
  printaMatrizShow(matriz_show, altura);
  // Libera Matriz de show
  for (int i = 0; i < altura; i++)
    free(matriz_show[i]);
  free(matriz_show);
}

char **criaMatrizShow(int altura){
  char **show = (char **)malloc(altura*sizeof(char *));
  for (int i = 0; i < altura; i++) {
    show[i] = (char *)malloc(150 * sizeof(char));
    sprintf(show[i], "%100s", "");
  }
  return show;
}

void printaMatrizShow(char **show, int altura){
  for (int i = 0; i < altura; i++) {
    for(int j = 0; j < 100; j++){
        printf("%c", show[i][j]);
    }
    printf("\n");
  }
}

int salvaMatrizShow(No **raiz, char **show, int direcao_esquerda, int deslocamento, int nivel) {
  int largura = 5;
  char valores[10];

  if ((*raiz) == NULL)
    return 0;
  sprintf(valores, " %3d ", (*raiz)->numero);
  int esquerda  = salvaMatrizShow(&((*raiz)->esquerda), show, 1, deslocamento, nivel + 1);
  int direita = salvaMatrizShow(&((*raiz)->direita), show, 0, deslocamento + esquerda + largura, nivel + 1);

  for (int i = 0; i < largura; i++){
    show[2 * nivel][deslocamento + esquerda + i] = valores[i];
  }

  if (nivel && direcao_esquerda) {
    for (int i = 0; i < largura + direita; i++){
      show[2 * nivel - 1][deslocamento + esquerda + largura/2 + i] = '-';
    }
    show[2 * nivel - 1][deslocamento + esquerda + largura/2] = '/';
    show[2 * nivel - 1][deslocamento + esquerda + largura + direita + largura/2] = ':';
  }else if (nivel && !direcao_esquerda) {
    for (int i = 0; i < esquerda + largura; i++){
      show[2 * nivel - 1][deslocamento - largura/2 + i] = '-';
    }
    show[2 * nivel - 1][deslocamento + esquerda + largura/2] = 92;
    show[2 * nivel - 1][deslocamento - largura/2 - 1] = ':';
  }
  return esquerda + largura + direita;
}

int arvoreBalanceada(No **raiz){
  if(abs(getHeight(&(*raiz)->esquerda) - getHeight(&(*raiz)->direita)) > 1){
    return 0; // Não balanceada
  }else{
    return 1; // Balanceada
  }
}
