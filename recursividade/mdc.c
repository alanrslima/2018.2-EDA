#include <stdio.h>

int mdc(int a, int b);

int main(){
	int a, b;
	printf("Digite o primeiro número: ");
	scanf("%d", &a);
	printf("Digite o segundo número: ");
	scanf("%d", &b);
	printf("O MDC é: %d\n", mdc(a,b) );
	return 0;
}

int mdc(int a, int b){
	int r, q;
	q = a / b;
	r = a % b;
	a = b;
	b = r;
	if (b == 0){
		return a;
	}else{
		return mdc(a, b);
	}
}