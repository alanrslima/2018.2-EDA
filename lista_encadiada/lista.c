#include <stdio.h>
#include <stdlib.h>
#include <math.h>
 // lista encadeada simples -> simples e unidirecional
// lista sem cabeça > primeiro elemento da lista é o primeiro elemento da lista
// lista com cabeça > tem uma referencia que ira apontar para o primeiro elemento da lista
 struct LISTA
{
    int dados;
    struct LISTA *prox;
};
 typedef struct LISTA Lista;
 Lista *criaListaVazia();
Lista *criaElemento(int);
Lista *insereInicio(Lista *, Lista *);
void printLista(Lista *);
void liberaLista(Lista *);
void insereLista(Lista *, Lista *, int);
Lista *buscaElemento(Lista *, int);
 int main()
{
    Lista *lista;
    Lista *temp;
     lista = criaListaVazia();
     lista = insereInicio(lista, criaElemento(1));
    lista = insereInicio(lista, criaElemento(2));
    lista = insereInicio(lista, criaElemento(3));
     insereLista(lista, criaElemento(15), 2);
     printLista(lista);
     temp = buscaElemento(lista, 15);
     if(temp != NULL)
    {
        printf("\nEndereço: %p\tElemento: %d\n", temp, temp->dados);
    }
    else
    {
        printf("\nElement not found!\n");
    }
     liberaLista(lista);
     return 0;
}
 Lista *criaListaVazia()
{
    return NULL;
}
 Lista *criaElemento(int d)
{
    Lista *l = (Lista *) malloc(sizeof(Lista));
     if (l == NULL)
    {
        printf("\nCannot allocate memory!\n");
        exit(-1);
    }
     l->dados = d;
    l->prox = NULL;
     return l;
}
 Lista *insereInicio(Lista *l, Lista *e)
{
    e->prox = l;
     return e;
}
 void printLista(Lista *l)
{
    Lista *e;
     for(e = l; e != NULL; e = e->prox)
    {
        printf("%d\t", e->dados);
    }
}
 void liberaLista(Lista *l)
{
    Lista *e;
     for (e = l; e != NULL; e = e->prox)
    {
        free(e->prox);
    }
}
 void insereLista(Lista *l, Lista *e, int idx)
{
    Lista *t;
    int i = 0;
    for (t = l; i != idx - 1; t = t->prox)
    {
        i++;
    }
     e->prox = t->prox;
    t->prox = e;
}
 Lista *buscaElemento(Lista *l, int d)
{
    Lista *e;
     for (e = l; e != NULL; e = e->prox)
    {
        if (e->dados == d)
        {
            break;
        }
    }
    return e;
} 
