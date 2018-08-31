#include <stdio.h>
#include <stdlib.h>

// int main (int argc, char *argv[]) {
// 	int x;
// 	x = 15;
// 	printf("CONTEUDO de X = %d \n", x);    // 15
// 	printf("ENDERECO de X = %p \n", &x);   // 0x7ffeee977a3c 
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	int *p, x, q;
// 	x = 15;
// 	p = &x;
// 	q = *p;
// 	printf("%p \n", p);    // 0x7ffeeeac4a34 
// 	printf("%d \n", *p);   // 15
// 	printf("%d \n", q);    // 15
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
//  int *p1, *p2, x, y, z;
//      x = 10;
//      p1 = &x;
//      p2 = p1;
//  	printf("x: %d \n", x);      // 10
//  	printf("&x: %d \n", &x);    // -519325140 
//  	printf("p1: %d \n", p1);	  // -519325140 
//  	printf("&p1: %d \n", &p1);  // -519325128
//  	printf("p2: %d \n", p2);    // -519325140 
//  	printf("&p2: %d \n", &p2);  // -519325136 
//  	y = *p1;
//  	printf("y: %d \n", y);      // 10
//  	z = *p2;
//  	printf("z: %d \n", z);      // 10
//  	return 0; 
//  }


// int main (int argc, char *argv[]) {
// 	int *p1, x = 10;
// 	p1 = &x;
// 	printf("p1: %d \n", p1);  // -348624332 
// 	printf("&x: %d \n", &x);  // -348624332 
// 	printf("x: %d \n", x);    // 10
// 	p1++;
// 	printf("p1: %d \n", p1);  // -348624328 
// 	printf("&x: %d \n", &x);  // -348624332 
// 	printf("x: %d \n", x);    // 10
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	char *p1, x = 'a';
// 	p1 = &x;
// 	printf("p1: %d \n", p1);   // -468198857
// 	printf("&x: %d \n", &x);   // -468198857
// 	printf("x: %c \n", x);     // a
// 	p1++;              
// 	printf("p1: %d \n", p1);   // -468198856
// 	printf("&x: %d \n", &x);   // -468198857
// 	printf("x: %c \n", x);     // a
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	double x = 1.23212345, *p1;
// 	p1 = &x;
// 	printf("p1: %d \n", p1);    // -485635528
// 	printf("&x: %d \n", &x);    // -485635528
// 	printf("x: %lf \n", x);     // 1.232123
// 	p1 = p1 + 2;
// 	printf("p1: %d \n", p1);    // -485635512
// 	printf("&x: %d \n", &x);    // -485635528
// 	printf("x: %lf \n", x);     // 1.232123
// 	return 0; 
// }


// SEGMENTATION FAULT
// int main (int argc, char *argv[]) {
// 	int x[2] = {1, 10}, *p, end;
// 	p = x;
// 	end = (int)p; 
// 	end++;
// 	p = (int *)end; 
// 	printf("p = %d \n", *p);
// return 0; }


// int main (int argc, char *argv[]) {              //  Endereço      Conteudo
// 	int i, x[4] = {0,1,2,3};                       // -325662160        0
// 	printf("Endereco\t Conteudo\t \n");            // -325662156        1
// 	for (i = 0; i<4; i++)                          // -325662152        2
// 		printf("%d\t\t %d\t \n", &x[i], x[i]);       // -325662148        3
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	int *p, x[4] = {0,1,2,3};
// 	printf("Endereco\t Conteudo\t \n"); 
// 	printf("Notacao de vetor \n"); 
// 	printf("%d\t\t %d\t \n", &x[0], x[0]);    // -535700944     0
// 	printf("Notacao de ponteiro \n"); 
// 	p = x;
// 	p++;
// 	printf("%d\t\t %d\t \n", p, *p);					// -535700944     0
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	int x[4] = {0,1,2,3}, *p1;
// 	p1 = x;
// 	printf("Endereco\t Conteudo\t \n"); 
// 	printf("Notacao de vetor \n"); 
// 	printf("%d\t\t %d\t \n", &x[0], x[0]); 
// 	printf("Notacao de ponteiro \n"); 
// 	printf("%d\t\t %d\t \n", p1, *p1);
// 	return 0; 
// }


// int main (int argc, char *argv[]){
// 	int *x[2], var1, var2; 
// 	var1 = 3;
// 	var2 = 4;
//   x[0] = &var1;
//   x[1] = &var2;
// 	printf("&var1: %d \n", &var1);    // -288445908 
// 	printf("&var2: %d \n", &var2);    // -288445912 
// 	printf("var1: %d\n", var1);       // 3
// 	printf("var2: % d\n", var2);      // 4
// 	printf("x[0]: %d \n", x[0]);      // -288445908 
// 	printf("x[1]: %d \n", x[1]);      // -288445912 
// 	printf("*x[0]: %d\n", *x[0]);     // 3
// 	printf("*x[1]: % d\n", *x[1]);    // 4
// 	return 0; 
// }


// int main(int argc, char *argv[]) {
// 	int *x[2], y0[2] = {0,1}, y1[2] = {2,3} ; 
// 	x[0] = y0;
// 	x[1] = y1;
// 	printf("Conteudo de x[0] = y0: %d \n", x[0]);                       // -350569928 
// 	printf("Conteudo de x[1] = y1: %d \n", x[1]);                       // -350569936
// 	printf("Endereço do primeiro elemento do vetor x: %d \n", &x[0]);   // -350569920 
// 	printf("Endereço do segundo elemento do vetor x: %d \n", &x[1]);    // -350569912 
// 	printf("Conteudo de y0[0]: %d \n", *(x[0] + 0));                    // 0
// 	printf("Conteudo de y0[1]: %d \n", *(x[0] + 1));                    // 1
// 	printf("Endereço de y0[0]: %d \n", (x[0] + 0));                     // -350569928 
// 	printf("Endereço de y0[1]: %d \n", (x[0] + 1));                     // -350569924 
// 	printf("Conteudo de y1[0]: %d \n", *(x[1] + 0));                    // 2
// 	printf("Conteudo de y1[1]: %d \n", *(x[1] + 1));                    // 3
// 	printf("Endereço de y1[0]: %d \n", (x[1] + 0));                     // -350569936
// 	printf("Endereço de y1[1]: %d \n", (x[1] + 1));                     // -350569932
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	char *p = "Segunda-feira"; 
// 	printf("%s \n", p);                   // Segunda-feira
// 	printf("Endereço de p: %d\n", p);     // 179302258
// 	printf("Valor de p: %c\n", *(p+1));   // e
// 	return 0; 
// }


// int main (int argc, char *argv[]) {
// 	char *x[5] = {"Segunda-feira", 
// 								"Terca-feira",
// 								"Quarta-feira", 
// 								"Quinta-feira", 
// 								"Sexta-feira"};
// 	printf("%s \n", x[2]);
// 	return 0;
// }


// void divpordois (float *);

// int main (int argc, char *argv[]) {
// 	float y = 5.0;
// 	printf("y = %.2f \n", y); 
// 	divpordois(&y); 
// 	printf("y = %.2f \n", y);
// 	return 0; 
// }

// void divpordois (float *n){ 
// 	*n = *n/2;
// }

// #define MAX 10
// int retornavetor (float *, int);

// int main (int argc, char *argv[]) {
// 	float x[MAX] = {0,0,0,0,0,0,0,0,0,0}; 
// 	int i, sucesso;
// 	printf("Vetor antes de chamar a funcao\n"); 
// 	for (i = 0; i<MAX; i++)
// 		printf("%.2f \n", x[i]); sucesso = retornavetor(x, MAX);
// 	printf("Vetor depois de chamar a funcao\n"); 
// 	for (i = 0; i<MAX; i++)
// 		printf("%.2f \n", x[i]); return 0;
// }

// int retornavetor( float *vet, int N){
// 	int i;
// 	for (i = 0; i<N; i++)
// 		*(vet+i) = i;
// 	return 0; 
// }

