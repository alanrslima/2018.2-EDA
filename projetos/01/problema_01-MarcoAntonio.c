/*
==>caso a celula esteja excitada 1
==>caso esteja inibida 0
==>se SOMAP passar T --> excitada
==>se SOMAP nao passar T --> inibida
==>o neuronio é um vetor e tem X entradas
==>cada elemento do neuronio é multiplicado por um elemento de determinado peso, que esta contido no vetor peso
==>a soma dos neuronios multiplicados pelo peso é a SOMAP
*/
#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int fneuronio(double *p1, double *p2, double limiarT, int max);

int main(){
  double entradas[MAX], pesos[MAX], limiarT, *p1, *p2;
  int i;

  for(i = 0; i<MAX; i++)
  {
    printf("Digite o valor da entrada %d: ", i+1);
    scanf("%lf", &entradas[i]);
  }

  printf("\n");

  for(i = 0; i<MAX; i++)
  {
    printf("Digite o valor do peso %d: ", i+1);
    scanf("%lf", &pesos[i]);
  }

  p1 = entradas;
  p2 = pesos;

  printf("\n");
  printf("Digite o valor do limiar T: ");
  scanf("%lf", &limiarT);
  printf("\n");

  fneuronio(p1, p2, limiarT, MAX); //chamando 2 vezes a funçao 

  if(fneuronio(p1, p2, limiarT, MAX) == 1) //chamando 2 vezes a funçao
    printf("Neurônio ativado!\n");
  else
    printf("Neurôno inibido!\n");

  return 0;
}

int fneuronio(double *p1, double *p2, double limiarT, int max)
{
  double vetor[max], SOMAP = 0;
  int i, excitada = 1, inibida = 0, *p3, *p4;

  for(i = 0; i<max; i++)
    vetor[i] = (p1[i])*(p2[i]);

  for(i = 0; i<max; i++)
    SOMAP += vetor[i];

  p3 = &excitada;
  p4 = &inibida;

  if(SOMAP > limiarT)
    return *p3;
  else
    return *p4;
}