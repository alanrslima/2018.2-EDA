#include <stdio.h>
#include <stdlib.h>

void torre_hanoi(int qtd_discos, char origem, char destino, char auxiliar, int *contador);
int valida_qtd_discos(int qtd);

int main(){
	int qtd_discos;
	int *contador;
	contador = (int *)malloc(sizeof(int));
	if (contador == NULL){
		exit(1);
	}
	printf("Digite a quantidade de discos: ");
	scanf("\n%d", &qtd_discos);
	qtd_discos = valida_qtd_discos(qtd_discos);
	*contador = 0;
	torre_hanoi(qtd_discos,'A', 'C', 'B', contador);
	printf("\nQuantidade de movimentos = %d\n\n\n", *contador);
	free(contador);
	return 0;
}

int valida_qtd_discos(int qtd){
	while (qtd <= 0){
		printf("Digite um número maior que 0: ");
		scanf("\n%d", &qtd);
	}
	return qtd;
}

void torre_hanoi(int qtd_discos, char origem, char destino, char auxiliar, int *contador){
	if (qtd_discos == 1){
		printf("Mover disco %d de %c para %c\n", qtd_discos, origem, destino);
		*contador = *contador + 1;
	}else{
		torre_hanoi(qtd_discos-1, origem, auxiliar, destino, contador);
		printf("Mover disco %d de %c para %c\n", qtd_discos, origem, destino);
		*contador = *contador + 1;
		torre_hanoi(qtd_discos-1, auxiliar, destino, origem, contador);
	}
}