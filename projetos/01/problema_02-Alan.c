#include <stdio.h>
#include <stdlib.h>
#define MAX_NOTAS 10

struct situacao_alunos
{
	int num_aprovados;
	int num_reprovados;
};

struct percentagem_alunos
{
	float percent_aprovados;
	float percent_reprovados;
};

int *recebe_notas(float *, int num_elementos);
struct situacao_alunos *conta_notas(int *, int num_elementos);
struct percentagem_alunos *percent_aprov(int aprovados, int reprovados);


int main(int argc, char const *argv[])
{
	int *vetor_apr, i = 0;
	float vetor_notas[MAX_NOTAS];
	struct situacao_alunos *situacao;
	struct percentagem_alunos *percentagem;

	for (int i = 0; i < MAX_NOTAS; i++){
		printf("Digite a %dº nota: ", i+1 );
		scanf("\n%f", &vetor_notas[i]);
	}
	vetor_apr = recebe_notas(vetor_notas, MAX_NOTAS);
	situacao = conta_notas(vetor_apr, MAX_NOTAS);
	percentagem = percent_aprov(situacao->num_aprovados, situacao->num_reprovados);
	printf("Quantidade de aprovados: %d\n", situacao->num_aprovados);
	printf("Quantidade de reprovados: %d\n", situacao->num_reprovados);
	printf("Percentual de aprovados: %2.f%%\n", percentagem->percent_aprovados);
	printf("Percentual de reprovados: %2.f%%\n", percentagem->percent_reprovados);
	if (situacao->num_aprovados > MAX_NOTAS/2){
		printf("Mais da metade da turma foi aprovada\n");
	}else{
		printf("Menos da metade da turma foi aprovada\n");
	}
	return 0;
}

int *recebe_notas(float *vet_notas, int num_elementos){
	int *vet_apr;
	int i = 0;
	vet_apr = (int *)malloc(num_elementos * sizeof(int));
	for (i = 0; i < num_elementos; i++){
		if (*(vet_notas+i) >= 6){
			*(vet_apr+i) = 1;
		}else{
			*(vet_apr+i) = 0;
		}
	}
	return vet_apr;
}

struct situacao_alunos *conta_notas(int *vet_apr, int num_elementos){
	int i = 0;
	struct situacao_alunos *situacao;
	situacao = (struct situacao_alunos *)malloc(sizeof(struct situacao_alunos));
	situacao->num_reprovados = 0;
	situacao->num_aprovados = 0;
	for (i = 0; i < num_elementos; i++){
		if (*(vet_apr+i) == 0){
			situacao->num_reprovados++;
		}else if (*(vet_apr+i) == 1){
			situacao->num_aprovados++;
		}
	}
	return situacao;
}

struct percentagem_alunos *percent_aprov(int aprovados, int reprovados){
	int total_alunos;
	struct percentagem_alunos *alunos;
	alunos = (struct percentagem_alunos *)malloc(sizeof(struct percentagem_alunos));
	alunos->percent_aprovados = (aprovados * 100) / total_alunos;
	alunos->percent_reprovados = (reprovados * 100) / total_alunos;
	return alunos;
}


