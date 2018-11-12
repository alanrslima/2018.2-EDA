#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct no{
  int numero;
  struct no *esquerda;
  struct no *direita;
} No;

void cria_arvore(No **raiz);
void insere_arvore(No **raiz, int num);
// No *MaiorDireita(No **no);
// No *MenorEsquerda(No **no);
// void remover(No **pRaiz, int numero);
void exibirEmOrdem(No *pRaiz);
void exibirPreOrdem(No *pRaiz);
void exibirPosOrdem(No *pRaiz);
int contarNos(No *pRaiz);
int contarFolhas(No *pRaiz);
int maior(int a, int b);
int altura(No *pRaiz);

int main(int argc, char const *argv[]) {

  No **arvore;
  cria_arvore(arvore);
  insere_arvore(arvore,2);
  insere_arvore(arvore,12);
  insere_arvore(arvore,5);
  insere_arvore(arvore,34);

  return 0;
}

void cria_arvore(No **raiz){
  *raiz = NULL;
}

void insere_arvore(No **raiz, int num){
  if (*raiz == NULL){
    *raiz = (No*)malloc(sizeof(No));
    (*raiz)->esquerda = NULL;
    (*raiz)->direita = NULL;
    (*raiz)->numero = num;
  }else{
    if (num < (*raiz)->numero){
      insere_arvore(&((*raiz)->esquerda), num);
    }else{
      insere_arvore(&((*raiz)->direita), num);
    }
  }
}

// No *MaiorDireita(No **no){
//   if((*no)->direita != NULL){
//      return MaiorDireita(&(*no)->direita);
//   }else{
//     No *aux = *no;
//     if((*no)->esquerda != NULL){ // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da esquerda!
//       *no = (*no)->esquerda;
//     }else{
//       *no = NULL;
//       return aux;
//     }
//   }
// }

// No *MenorEsquerda(No **no){
//   if((*no)->esquerda != NULL){
//     return MenorEsquerda(&(*no)->esquerda);
//   }else{
//     No *aux = *no;
//     if((*no)->direita != NULL){ // se nao houver essa verificacao, esse nó vai perder todos os seus filhos da direita!
//       *no = (*no)->direita;
//     }else{
//       *no = NULL;
//     }
//     return aux;
//   }
// }

// void remover(No **pRaiz, int numero){
//   if(*pRaiz == NULL){   // esta verificacao serve para caso o numero nao exista na arvore.
//     printf("Numero nao existe na arvore!");
//     // getch();
//     return;
//   }
//   if(numero < (*pRaiz)->numero)
//     remover(&(*pRaiz)->esquerda, numero);
//   else
//     if(numero > (*pRaiz)->numero)
//       remover(&(*pRaiz)->direita, numero);
//     else{    // se nao eh menor nem maior, logo, eh o numero que estou procurando! :)
//       No *pAux = *pRaiz;     // quem programar no Embarcadero vai ter que declarar o pAux no inicio do void! :[
//       if (((*pRaiz)->esquerda == NULL) && ((*pRaiz)->direita == NULL)){         // se nao houver filhos...
//         free(pAux);
//         (*pRaiz) = NULL;
//       }else{     // so tem o filho da direita
//         if ((*pRaiz)->esquerda == NULL){
//           (*pRaiz) = (*pRaiz)->direita;
//           pAux->direita = NULL;
//           free(pAux); pAux = NULL;
//         }
//       else{            //so tem filho da esquerda
//         if ((*pRaiz)->direita == NULL){
//           (*pRaiz) = (*pRaiz)->esquerda;
//           pAux->esquerda = NULL;
//           free(pAux); pAux = NULL;
//         }else{       //Escolhi fazer o maior filho direito da subarvore esquerda.
//           pAux = MaiorDireita(&(*pRaiz)->esquerda); //se vc quiser usar o Menor da esquerda, so o que mudaria seria isso:
//           pAux->esquerda = (*pRaiz)->esquerda;          //        pAux = MenorEsquerda(&(*pRaiz)->direita);
//           pAux->direita = (*pRaiz)->direita;
//           (*pRaiz)->esquerda = (*pRaiz)->direita = NULL;
//           free((*pRaiz));  *pRaiz = pAux;  pAux = NULL;
//         }
//       }
//     }
//   }
// }

void exibirEmOrdem(No *pRaiz){
  if(pRaiz != NULL){
    exibirEmOrdem(pRaiz->esquerda);
    printf("\n%i", pRaiz->numero);
    exibirEmOrdem(pRaiz->direita);
  }
}

void exibirPreOrdem(No *pRaiz){
  if(pRaiz != NULL){
    printf("\n%i", pRaiz->numero);
    exibirPreOrdem(pRaiz->esquerda);
    exibirPreOrdem(pRaiz->direita);
  }
}

void exibirPosOrdem(No *pRaiz){
  if(pRaiz != NULL){
    exibirPosOrdem(pRaiz->esquerda);
    exibirPosOrdem(pRaiz->direita);
    printf("\n%i", pRaiz->numero);
  }
}

int contarNos(No *pRaiz){
  if(pRaiz == NULL)
    return 0;
   else
    return 1 + contarNos(pRaiz->esquerda) + contarNos(pRaiz->direita);
}

int contarFolhas(No *pRaiz){
  if(pRaiz == NULL)
    return 0;
  if(pRaiz->esquerda == NULL && pRaiz->direita == NULL)
    return 1;
  return contarFolhas(pRaiz->esquerda) + contarFolhas(pRaiz->direita);
}

int maior(int a, int b){
  if(a > b)
    return a;
  else
    return b;
}//maior

int altura(No *pRaiz){
  if((pRaiz == NULL) || (pRaiz->esquerda == NULL && pRaiz->direita == NULL))
    return 0;
  else
    return 1 + maior(altura(pRaiz->esquerda), altura(pRaiz->direita));
}

// bool find(int element)
// {
//     // Procura o elemento na árvore
//     // O(log n)
//
//
//     Node* temp = root;
//     int parar=0;
//
//     if(root==NULL){
//       return false;
//     }else if(temp->left== NULL && temp->right==NULL){
//       if(temp->value == element){
//         return true;
//       }else{
//         return false;
//       }
//     }else if(temp->value==element){
//       return true;
//     }else{
//     while(parar==0){
//       if(temp->value < element){
//         if(temp->left == NULL){
//           parar++;
//           if (temp->value==element){
//             break;
//             return true;
//           }else{
//           return false;
//           }
//         }else{
//           temp=temp->left;
//           if (temp->value== element){
//             return true;
//             break;
//           }
//         }
//
//       }else if(temp->value > element){
//         if(temp->right== NULL){
//           parar++;
//           if (temp->value==element){
//             return true;
//             break;
//           }else{
//           return false;
//           }
//         }else{
//           temp=temp->right;
//           if (temp->value== element){
//             return true;
//             break;
//           }
//         }
//       }
//     }
//   }
// }
