#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

/*

Escreva todas as alocações dinamicas aqui para nao esquecer
de dar um free ao final do programa --------

FILE *fileAsphalt;
int **matrizFile

*/

void GeraAleatorios(int *, int tamVet, int limite);
bool Existe(int *, int tamVet, int valor);
FILE *getAsphaltImage(FILE *,int random);
void getQtdLinhasColunas(FILE *, int *linhas, int *colunas);

int main(){
  // FILE *asphalt_images[25], *grass	_images[25];
  int grass[25], asphalt[25];
	int lin, col;
	char nameFileAsphalt[25];;
	int **matrizFile;

  GeraAleatorios(asphalt, 25, 50);

  printf("Ordem do vetor de asfalto: \n");
  for(int i=0; i<25; i++){
    printf("%d ", asphalt[i]);
  }
  printf("\n-----------------------\n");

  for(int i=0; i<25; i++){
    printf("Arquivo número %d\n", i);
    FILE *fileAsphalt;

		// Realiza a leitura de um arquivo
		fileAsphalt	= getAsphaltImage(fileAsphalt, asphalt[i]);
		// Verifica a quantidade de linhas e colunas do arquivo
		getQtdLinhasColunas(fileAsphalt, &lin, &col);
		// Volta para o inicio do arquivo
		rewind(fileAsphalt);

		// Aloca a matriz do arquivo de forma DINAMICA
    matrizFile = (int**)malloc(lin*sizeof(int *));
    for (i = 0; i < lin; i++) {
      *(matrizFile+i) = (int*)malloc(col*sizeof(int));
    }

		// Aloca dinamicamente o vetor ILBP de 512 elementos tudo preenchido com 0.
    ilbp = (int *) calloc(512, sizeof (int));

    // Aloca dinamicamente o vetor metricas de 24 elementos tudo preenchido com 0.
    metricas = (float *) calloc(24, sizeof (float));

    // Aloca dinamicamente o vetor ilbp+glcm de 536 elementos tudo preenchido com 0.
    ilbp_glcm = (float *) calloc(536, sizeof (float));

    // Aloca dinamicamente o vetor ilbp+glcm normalizado de 536 elementos tudo preenchido com 0.
    ilbp_glcm_normalizado = (float *) calloc(536, sizeof (float));

  }


  return 0;
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

bool Existe(int *vet, int tamVet, int valor)
{
  for(int i=0; i<tamVet; i++){
    if(vet[i]==valor || vet[i]==0)
      return true;
  }
  return false;
}

void GeraAleatorios(int *vet, int tamVet, int limite)
{
  // srand(time(NULL));
  int random;
  for(int i=0; i<tamVet; i++){
    random = rand() % limite;
    while (Existe(vet, i, random)) {
      random = rand() % limite;
    }
    vet[i] = random;
  }
}
