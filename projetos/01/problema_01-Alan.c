#include <stdio.h>
#include <stdlib.h>
#define ENTRADAS 10
#define PESOS 10

int *fneuronio(float *,float *,float liminar,int max_entradas);

int main(int argc, char const *argv[])
{
	int contador = 0;
	float vetor_entrada[ENTRADAS], vetor_peso[PESOS], liminarT;
	int *p;

	for (contador = 0; contador < ENTRADAS; contador++)
	{
		printf("Digite o %dº valor de entrada: ",contador+1);
		scanf("\n%f", &vetor_entrada[contador]);
	}
	for (contador = 0; contador < ENTRADAS; contador++)
	{
		printf("Digite o %dº valor de peso: ",contador+1);
		scanf("\n%f", &vetor_peso[contador]);
	}
	printf("Digite o valor da liminar T: ");
	scanf("\n%f", &liminarT);
	p = fneuronio(vetor_entrada, vetor_peso, liminarT, ENTRADAS);
	if (*p){
		printf("Neurônio ativado!\n");
	}else{
		printf("Neurônio inibido!\n");
	}
	free(p);
	return 0;
}

int *fneuronio(float *vet_entrada,float *vet_peso,float liminar,int max_entradas ){
	int somaP = 0, aux = 0;
	int *response;
	for (aux = 0; aux < max_entradas; aux++){
		somaP = somaP + (*(vet_entrada + aux) * (*(vet_peso + aux)));
	}
	response = (int *)malloc(sizeof(int));
	if (response != 0){
		if (somaP > liminar){
			*response = 1;
		}else{
			*response = 0;
		}
	}
	return response;
}
