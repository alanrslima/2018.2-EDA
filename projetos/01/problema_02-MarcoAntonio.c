#include <stdio.h>
#include <stdlib.h>
#define MAX 10

int *recebe_notas(float *p1, int max);
int *conta_notas(int *s1, int max);
int *percent_aprov(int num_aprovados, int num_reprovados);

int main(){
  float notas[MAX], *p1;
  int i, *s1, *s2;

  for(i = 0; i<MAX; i++)
  {
    printf("Digite a nota %d:", i+1);
    scanf("%f", &notas[i]);
  }
  
  p1 = notas;

  s1 = recebe_notas(p1, MAX); //s1 é o retorno de p2
  s2 = conta_notas(s1, MAX); //s2 é o retorno de p3
  percent_aprov(s2[0], s2[1]);

  return 0;
}

int *recebe_notas(float *p1, int max)
{
  int APR[max], i, *p2;

  for(i = 0; i<max; i++)
  {
	if(p1[i] >= 6.0)
		APR[i] = 1;
	else
		APR[i] = 0;
  }
  
  p2 = APR;

  return p2;
}

int *conta_notas(int *s1, int max)
{
  int i, aprovados = 0, reprovados = 0, *p3, alunos[2];

  for(i = 0; i<max; i++)
  {
    if(s1[i] == 0)
      reprovados++;
    else
      aprovados++;
  }

  alunos[0] = aprovados;
  alunos[1] = reprovados;
  p3 = alunos;

  return p3;
}

int *percent_aprov(int num_aprovados, int num_reprovados)
{
  float per_aprovados, per_reprovados, percentagem[2], *p4;

  per_aprovados = num_aprovados/MAX;
  per_reprovados = num_reprovados/MAX;

  percentagem[0] = per_aprovados;
  percentagem[1] = per_reprovados;
  p4 = percentagem;
  
  return p4;
}
