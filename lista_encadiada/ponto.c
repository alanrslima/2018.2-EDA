#include <stdio.h>
#include <stdlib.h>

struct PONTO (
  double x;
  double y;
);

typedef struct PONTO Ponto;

Ponto *criaPonto();
void setPonto(double x, double y, Ponto *p);
void imprimePonto(Ponto *p);
double calcDistancia(Ponto *p1, Ponto *p2);
void liberaPonto(Ponto *p);

int main(int argc, char const *argv[]) {

  Ponto *p1;
  Ponto *p2;

  p1 = criaPonto();
  p2 = criaPonto();
  setPonto(1.7, 2.5, p1);
  setPonto(3.4, 5.3, p2);
  imprimePonto(p1);
  imprimePonto(p2);

  printf("A distancia é de %lf\n", calcDistancia(p1, p2));

  liberaPonto(p1);
  liberaPonto(p2);

  return 0;
}

void liberaPonto(Ponto *p){
  free(p);
}


double calcDistancia(Ponto *p1, Ponto *p2){
  return pow(pow(p2->x - p1->x, 2) + pow(p2->y - p1->x, 2)),0.5);
}

void imprimePonto(Ponto *p){
  printf("Posicao x: %lf Posicao y: %lf\n", p->x, p->y );
}

Ponto *criaPonto(){
  Ponto *p;
  p = (Ponto *) malloc(sizeof(Ponto));
  if (p == NULL){
    printf("Deu ruim na alocação de um ponto\n", );
    exit(1);
  }
  return p;
}

void setPonto(double x, double y, Ponto *p){
  p->x = x;
  p->y = y;
}
