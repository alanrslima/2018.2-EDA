#include <stdio.h>
#include <stdlib.h>
#define ENTRADAS 3
#define PESOS 3

int *fneuronio(int *,int *,int liminar,int max_entradas);

int main(int argc, char const *argv[])
{
	int contador = 0;
	int vetor_entrada[ENTRADAS], vetor_peso[PESOS], liminarT, *p;

	for (contador = 0; contador < ENTRADAS; contador++)
	{
		printf("Digite o %dº valor de entrada: ",contador+1);
		scanf("\n%d", &vetor_entrada[contador]);
	}
	for (contador = 0; contador < ENTRADAS; contador++)
	{
		printf("Digite o %dº valor de peso: ",contador+1);
		scanf("\n%d", &vetor_peso[contador]);
	}
	printf("Digite o valor da liminar T: ");
	scanf("\n%d", &liminarT);
	p = fneuronio(vetor_entrada, vetor_peso, liminarT, ENTRADAS);
	if (*p){
		printf("Neurônio ativado!\n");
	}else{
		printf("Neurônio inibido!\n");
	}
	return 0;
}

int *fneuronio(int *vet_entrada,int *vet_peso,int liminar,int max_entradas ){
	int somaP = 0, aux = 0;
	int response, *p;
	for (aux = 0; aux < max_entradas; aux++){
		somaP = somaP + (*(vet_entrada + aux) * (*(vet_peso + aux)));
	}
	if (somaP > liminar){
		response = 1;
	}else{
		response = 0;
	}
	p = &response;
	return p;
}

