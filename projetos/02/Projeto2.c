#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>


void doRandom(int *, int limite);
// void GeraAleatorios(int *, int tamVet, int limite);
// bool Invalido(int *, int tamVet, int valor);
FILE *getAsphaltImage(FILE *,int random);
FILE *getGrassImage(FILE *fp ,int id);

void getQtdLinhasColunas(FILE *, int *linhas, int *colunas);
void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col);

int main(){
  int grass[50], asphalt[50];
  int lin, col;
	char nameFileAsphalt[25];
	int **matrizFile;

  doRandom(asphalt, 50);
  // Percorre arquivos asphalt
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

    // Liberação de memória
    for (int j = 0; j < lin; j++) {
      free(*(matrizFile+j));
    }
    free(matrizFile);
    fclose(fileAsphalt);
  }

  doRandom(grass, 50);
  // Percorre arquivos grass
  for(int i=0; i<25; i++){
    printf("Arquivo número %d\n", i);
    FILE *fileGrass;
		// Realiza a leitura de um arquivo
		fileGrass = getGrassImage(fileGrass, grass[i]);
    // Verifica a quantidade de linhas e colunas do arquivo
		getQtdLinhasColunas(fileGrass, &lin, &col);
		// Aloca a matriz do arquivo de forma DINAMICA
    matrizFile = (int**)malloc(lin*sizeof(int *));
    for (int j = 0; j < lin; j++) {
      *(matrizFile+j) = (int*)malloc(col*sizeof(int));
    }
    // Preenche matriz file com os dados do arquivo
    setMatrizFile(fileGrass, matrizFile, lin, col);

    // Liberação de memória
    for (int j = 0; j < lin; j++) {
      free(*(matrizFile+j));
    }
    free(matrizFile);
    fclose(fileGrass);
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


FILE *getGrassImage(FILE *fp ,int id){
  char asphalt[25];
  if(id < 10)
    sprintf(asphalt, "grass/grass_0%d.txt",id);
  else
    sprintf(asphalt, "grass/grass_%d.txt",id);

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
  srand(time(NULL));
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

//normalizando dados
void dataNormalize(int *vet, int limite){
  int menor = vet[0];
  int maior = vet[0];
  int vetorNormalizado[limite];

  for (int i = 1; i < limite; i++) {
    //calculando menor elemento do vetor
    if(vet[i] < vet[i-1])
      menor = vet[i];
    //calculando maior elemento do vetor
    if(vet[i] > vet[i-1])
      maior = vet[i];
    }

  //criando vetor normalizado
  for (int i = 0; i < limite; i++)
    vetorNormalizado[i] = (vet[i] - menor) / (maior - menor);
}

void euclidianDistance(int *vetorNormalizado, int *vetorA, int *vetorB, int limite){
  float distanciaA, distanciaB;
  int somaA = 0, somaB = 0;

  for (int i = 0; i < limite; i++) {
    somaA += pow((vetorNormalizado[i] + vetorA[i]),2);
    somaB += pow((vetorNormalizado[i] + vetorB[i]),2);
  }

  distanciaA = pow(somaA, 0.5);
  distanciaB = pow(somaB, 0.5);
}
