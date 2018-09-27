#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void doRandom(int *, int limite);
// void GeraAleatorios(int *, int tamVet, int limite);
// bool Invalido(int *, int tamVet, int valor);
FILE *getAsphaltImage(FILE *,int random);
void getQtdLinhasColunas(FILE *, int *linhas, int *colunas);
void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col);

int main(){
  int grass[50], asphalt[50];
  char marcador;
  int lin, col;
	char nameFileAsphalt[25];
	int **matrizFile;

  doRandom(asphalt, 50);

  for(int i=0; i<25; i++){
    printf("Arquivo número %d\n", i);
    FILE *fileAsphalt;
		// Realiza a leitura de um arquivo
		 fileAsphalt = getAsphaltImage(fileAsphalt, asphalt[i]);
    // Verifica a quantidade de linhas e colunas do arquivo
		 getQtdLinhasColunas(fileAsphalt, &lin, &col);
		// Aloca a matriz do arquivo de forma DINAMICA
    matrizFile = (int**)malloc(lin*sizeof(int *));
    for (int j = 0; j < lin; j++) {
      *(matrizFile+j) = (int*)malloc(col*sizeof(int));
    }
    // Preenche matriz file com os dados do arquivo
    setMatrizFile(fileAsphalt, matrizFile, lin, col);

    for (int j = 0; j < lin; j++) {
      free(*(matrizFile+j));
    }
    free(matrizFile);
    fclose(fileAsphalt);
  }


  return 0;
}

void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col){
  char pv;
  rewind(fp);
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (!feof(fp)) {
        fscanf(fp, "%d%c", *(matrizFile+i)+j, &pv);
      }
    }
  }
}

void getQtdLinhasColunas(FILE *fp, int *linhas, int *colunas){
	char marcador;
	*linhas = 0, *colunas = 1;
	while ((marcador = fgetc(fp)) != EOF) {
		if (marcador == '\n') {
			*linhas = *linhas + 1;
		}
		else if (*linhas == 0 && marcador == ';') {
			*colunas = *colunas + 1;
		}
	}
	printf("Quantidade de linhas: %d, Quantidade de colunas: %d\n\n", *linhas, *colunas);
}

FILE *getAsphaltImage(FILE *fp ,int id){
  char asphalt[25];
  if(id < 10)
    sprintf(asphalt, "asphalt/asphalt_0%d.txt",id);
  else
    sprintf(asphalt, "asphalt/asphalt_%d.txt",id);

  printf("Arquivo: %s\n", asphalt);
  fp = fopen(asphalt ,"r");

  if(fp==NULL){
    printf("Falha.\n");
    exit(1);
  }
  return fp;
}

// bool Invalido(int *vet, int tamVet, int valor)
// {
//   if (valor == 0){
//     return true;
//   }
//   for(int i=0; i<tamVet; i++){
//     if(vet[i]==valor)
//       return true;
//   }
//   return false;
// }
//
// void GeraAleatorios(int *vet, int tamVet, int limite)
// {
//   // srand(time(NULL));
//   int random;
//   for(int i=0; i<tamVet; i++){
//     random = rand() % limite;
//     printf("%d  ", random);
//     while (Invalido(vet, i, random)) {
//       random = rand() % limite;
//     }
//     printf("%d  ", random);
//     vet[i] = random;
//   }
// }

void doRandom(int *vet, int limite){

  srand((unsigned)time(0)*100);
  for (int i = 1; i < limite+1; i++) {
      vet[i-1] = i;
  }

  for (int i = 0; i < limite; i++) {
    int aux = vet[i];
    int random = rand() % limite;
    if (random != 0) {
      vet[i] = vet[random];
      vet[random] = aux;
    }
  }
  printf("Ordem do vetor de asfalto: \n");
  for(int i=0; i<limite; i++){
    printf("%d ", vet[i]);
  }
  printf("\n-----------------------\n");
}
