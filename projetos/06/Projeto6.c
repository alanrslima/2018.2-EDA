#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

typedef struct neuronio{
    double p[536]; //Entrada
    double w[536]; //Núcleo
    double b;
    double s; //Saida
    struct neuronio *proxima;
}Neuronio;

double calculoSaida(Neuronio **neuronio, double *p, double *w,double *b);
double randomGen(double valor);

int main(){

return 0;
}

double calculoSaida(Neuronio **neuronio, double *p, double *w, double *b){
    double somatorio = 0;
    double n, s;

    for(int i = 0; i <= 537; i++){ //Calculo do N
        somatorio += p[i] * w[i];
    }

    n = somatorio + *b;

    s = 1 / (1 + exp(-n));

return s;
}

double randomGen(double valor){
    double aux;
    
    srand(time(NULL));
    
    aux = (rand() % 31999) - 16000;

return aux;
}