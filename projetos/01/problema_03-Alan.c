#include <stdio.h>
#include <stdlib.h>

int get_quantidade(int qtd);
void torre_hanoi(int origem, int destino, int aux, int qtd, int *contador);

int main(){
	int qtd_discos, *contador;
	contador = (int *)malloc(sizeof(int));
	qtd_discos = get_quantidade(qtd_discos);
	*contador = 0;
	torre_hanoi(0, 2, 1, qtd_discos, contador);
	printf("\nQuantidade de Discos: %d\n", qtd_discos);
  printf("Nº minimo de movimentos: %d\n", *contador);
	free(contador);
	return 0;
}

int get_quantidade(int qtd){
	printf("Digite a quantidade inicial de discos: ");
	scanf("\n%d", &qtd);
	while (qtd <= 0){
		printf("Quantidade de discos inválida! Digite um número maior que 0: ");
		scanf("\n%d", &qtd);
	}
	return qtd;
}

void torre_hanoi(int origem, int destino, int auxiliar, int quantidade, int *contador){
  if( quantidade == 1 ){
    printf("Move de %d para %d\n", origem, destino);
    *contador = *contador + 1;
  }else{
    torre_hanoi(origem, auxiliar, destino, quantidade-1, contador);
    torre_hanoi(origem, destino, auxiliar, 1, contador);
    torre_hanoi(auxiliar, destino, origem, quantidade-1, contador);
  }
}