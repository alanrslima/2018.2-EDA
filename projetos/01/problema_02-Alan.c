#include <stdio.h>
#include <stdlib.h>

float *recebe_notas(float *, int num_elementos);
int *conta_notas(float *, int num_elementos);

struct situacao_alunos
{
	int num_aprovados;
	int num_reprovados;
};

int main(int argc, char const *argv[])
{
	
	return 0;
}

float *recebe_notas(float *vet_notas, int num_elementos){
	float *vet_apr[num_elementos];
	int i = 0;
	for (i = 0; i < num_elementos; i++){
		if (*(vet_notas+i) >= 6){
			*(vet_apr+i) = 1;
		}else{
			*(vet_apr+i) = 0;
		}
	}
	return vet_apr;
}

int *conta_notas(float *vet_apr, int num_elementos){
	int i = 0, num_aprovados = 0, num_reprovados = 0;
	int *situacao[2];
	for (i = 0; i < num_elementos; i++){
		if (*(vet_apr+i) == 0){
			num_reprovados++;
		}else if (*(vet_apr+i) == 1){
			num_aprovados++;
		}
	}
	*situacao = num_aprovados;
	*situacao+1 = num_reprovados;
	return situacao;
}

