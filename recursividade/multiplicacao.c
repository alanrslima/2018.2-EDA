#include <stdio.h>

int multiplicacao(int a, int b);

int main(){
	int a, b;
	int resultado;

	printf("Digite o primeiro número: ");
	scanf("%d", &a);
	printf("Digite o segundo número: ");
	scanf("%d", &b);
	// resultado = multiplicação(a, b);
	printf("Resultado da multiplicação: %d\n", multiplicacao(a,b) );
	return 0;
}

int multiplicacao(int a, int b){
	if (b == 1){
		return a;
	}else{
		return multiplicacao(a, b-1) + a;
	}
}