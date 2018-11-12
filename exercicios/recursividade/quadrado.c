#include <stdio.h>

int quadrado(int n);

int main(){
	int n;
	printf("Digite um número: ");
	scanf("%d", &n);
	printf("O quadrado deste número é: %d\n",quadrado(n) );
	return 0;
}

int quadrado(int n){
	if (n == 1){
		return n;
	}else{
		return (2*n-1) + (quadrado(n-1));
	}
}

