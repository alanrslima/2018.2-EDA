#include <stdio.h>
#include <stdlib.h>

typedef struct no{
  int numero;
  struct no *esquerda;
  struct no *direita;
} No;

No **cria_arvore();
void libera_arvore(No **raiz);
void libera_no(No *no);
int arvore_vazia(No **raiz);
int total_nos(No **raiz);
int insere_no(No **raiz, int valor);

int main(int argc, char const *argv[]) {

  No **arvore = cria_arvore();
  insere_no(arvore, 5);
  insere_no(arvore, 6);
  insere_no(arvore, 3);
  printf("Total de nós: %d", total_nos(arvore));
  return 0;
}

No **cria_arvore(){
  No **raiz = (No **)malloc(sizeof(No *));
  if (raiz != NULL){
    *raiz  = NULL;
  }
  return raiz;
}

void libera_no(No *no){
  if (no == NULL)
    return;
  libera_no(no->esquerda);
  libera_no(no->direita);
  free(no);
  no = NULL;
}

void libera_arvore(No **raiz){
  if (raiz == NULL){
    return;
  libera_no(*raiz);
  free(raiz);
  }
}

int arvore_vazia(No **raiz){
  if (raiz == NULL)
    return 1;
  if (*raiz == NULL)
    return 1;
  return 0;
}

int altura_arvore(No **raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int altura_esquerda = altura_arvore(&((*raiz)->esquerda));
  int altura_direita = altura_arvore(&((*raiz)->direita));
  if (altura_esquerda > altura_direita)
    return altura_esquerda + 1;
  else
    return altura_direita + 1;
}

int total_nos(No **raiz){
  if (raiz == NULL)
    return 0;
  if (*raiz == NULL)
    return 0;
  int altura_esquerda = altura_arvore(&((*raiz)->esquerda));
  int altura_direita = altura_arvore(&((*raiz)->direita));
  return (altura_esquerda + altura_direita + 1);
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
