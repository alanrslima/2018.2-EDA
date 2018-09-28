#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>


void doRandom(int *, int limite);
// void GeraAleatorios(int *, int tamVet, int limite);
// bool Invalido(int *, int tamVet, int valor);
FILE *getAsphaltImage(FILE *,int random);
FILE *getGrassImage(FILE *fp ,int id);

void getQtdLinhasColunas(FILE *, int *linhas, int *colunas);
void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col);

int main(){
  int grass[50], asphalt[50];
  int lin, col, menor, decimal[9];
	char nameFileAsphalt[25];
	int **matrizFile;
  char vetorBinario[9];

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

    // Cria vetor ILBP
    // for (i = 1; i < lin - 1 ; i++) {
    //   for (j = 1; j < col - 1 ; j++) {
    //     monta_vetor_binario(matrizFile, i, j, vetorBinario);
    //     menor = converte_binario_calcula_menor_decimal(vetorBinario, decimal);
    //     ilbp[menor]++;
    //   }
    // }


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


void monta_vetor_binario(int **matrizFile, int lin, int col, char *vetorbin) {
  float soma = 0, media;
  int i, j, x = 0, y = 0;
  char **bin;

  bin = (char**)malloc(3*sizeof(char *));
  for (i = 0; i < 3; i++) {
    *(bin + i) = (char*)malloc(3*sizeof(char));
  }

  for (i = lin - 1; i <= lin + 1; i++) {
    for (j = col - 1; j <= col + 1; j++) {
      soma += *(*(matrizFile+i)+j);
    }
  }

  media = soma / 9.0;

  for (i = lin - 1; i <= lin + 1; i++) {
    for (j = col - 1; j <= col + 1; j++) {
      if (*(*(matrizFile+i)+j) < media) {
        *(*(bin+x)+y) = '0';
      } else if (*(*(matrizFile+i)+j) >= media) {
        *(*(bin+x)+y) = '1';
      }
      y++;
    }
    y = 0;
    x++;
  }
  // Passa os elementos da matriz criada para o vetorbin na ordem solicitada pelo ILBP.
  vetorbin[0] = *(*(bin+0)+0);
  vetorbin[1] = *(*(bin+0)+1);
  vetorbin[2] = *(*(bin+0)+2);
  vetorbin[3] = *(*(bin+1)+2);
  vetorbin[4] = *(*(bin+2)+2);
  vetorbin[5] = *(*(bin+2)+1);
  vetorbin[6] = *(*(bin+2)+0);
  vetorbin[7] = *(*(bin+1)+0);
  vetorbin[8] = *(*(bin+1)+1);

  // Libera a memória alocada dinamicamente para a matriz de binários.
  for (i = 0; i < 3; i++) {
    free(*(bin+i));
  }
  free(bin);
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
  char grass[25];
  if(id < 10)
    sprintf(grass, "grass/grass_0%d.txt",id);
  else
    sprintf(grass, "grass/grass_%d.txt",id);

  printf("Arquivo: %s\n", grass);
  fp = fopen(grass ,"r");

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
