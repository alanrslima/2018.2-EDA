/*
  Obs: Utilize -lm no terminal para compilar o programa para reconhecer a biblioteca math.h
  ex: gcc <arquivo.c> -o <nomeDoBinario> -lm
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>

/* Pega o parametro passado via linha de comando */
int getParametroLinhaComando(int argc, char *argv[], int *param);

/* Seta valores randomicos dentro de um vetor com tamanho e maior número possivel estabelicidos pelo parametro limite*/
void doRandom(int *, int limite);

/* Retorna um ponteiro para uma imagem de asfalto com base em um numero de 1 a 50 ṕara identificação*/
FILE *getAsphaltImage(FILE *,int id);

/* Retorna um ponteiro para uma imagem de grama com base em um numero de 1 a 50 ṕara identificação*/
FILE *getGrassImage(FILE *fp ,int id);

/* Busca a quantidade de linhas e colunas de um arquivo .txt referentes as imagens */
void getQtdLinhasColunas(FILE *, int *linhas, int *colunas);

/* Preenche uma matriz auxiliar com os dados do arquivo de imagem */
void setMatrizFile(FILE *fp, int **matrizFile, int lin, int col);

/* Cria o vetor ILBP */
void ILBP(int **matrizFile, int lin, int col, int *ilbp);

/* Cria o vetor GLCM */
void GLCM(int **matrizFile, int lin, int col, float *metricas);

/* Calcula as metricas de cada posicao relativa do GLCM*/
void calculaMetricas(int **glcm, float *metricas, int initialPosition, int linhaColuna);

/* Calcula a metrica de contraste */
double calculaContraste(int **matriz, int linhaColuna);

/* Calcula a metrica de homogeneidade */
double calculaHomogeneidade(int **matriz, int linhaColuna);

/* Calcula a metrica de energia */
double calculaEnergia(int **matriz, int linhaColuna);

/* Cria o vetor de de binarios com base em uma matriz 3x3 extraida da matriz referente a imagem */
void setVetorBinario(int **matrizFile, int lin, int col, char *vetorbin);

/* Calcula o menor decimal possivel referente ao vetor de binarios provindos do */
int calculaMenorDecimal(char *bin);

/* Calcula a distancia euclidiana */
float euclidianDistance(float *medias, float **resultados, int indice);

/* Faz a normalizacao do vetor */
void dataNormalize(float *vet, float *vetNormalizado, int limite);

/* Concatena os vetores ilbp e glcm, formando um vetor unico de 536 posicoes*/
void concatenaIlbpGlcm(float *ilbpGlcm, int *ilbp, float *glcm);

/* Calcula a um vetor media de treinamento a partir da matriz de resulotados*/
void calculaMediaTreinamento(float **matTreinamento, float *vetMedia);

/* Preenche a matriz de resultado a partir de vetores normalizados */
void setResultado(float **matResultado, float *vetNormalizado, int contador);

/* Funcao para printar na tela os resultados das taxas analisadas */
void printaResultado(float aceitacao, float falsaRejeicao, float falsaAceitacao);

/* Responsavel por calculas as taxas de aceitacao, falsa aceitacao e falsa rejeicao levando em consideracao a distancia euclidiana */
void calculaTaxas(float *mediaGrama, float *mediaAsfalto, float **resultadoGrama, float **resultadoAsfalto);

/* Retorna uma matriz 50x536 com vetores ilbpGlc normalizados de cada imagem de asfalto */
void getFeaturesAsphalt(float **resultadoAsfalto);

/* Retorna uma matriz 50x536 com vetores ilbpGlc normalizados de cada imagem de grama */
void getFeaturesGrass(float **resultadoGrama);

int main(int argc, char *argv[]) {
  int param;
  if (getParametroLinhaComando(argc, argv, &param)){

    float **resultadoGrama, **resultadoAsfalto;

    resultadoAsfalto = (float **)malloc(50*sizeof(float *));
    for (int i=0; i<50; i++){
      *(resultadoAsfalto+i) = (float *)malloc(536*sizeof(float));
    }

    resultadoGrama = (float **)malloc(50*sizeof(float *));
    for (int i=0; i<50; i++){
      *(resultadoGrama+i) = (float *)malloc(536*sizeof(float));
    }

    getFeaturesAsphalt(resultadoAsfalto);
    getFeaturesGrass(resultadoGrama);

    //Liberacao de memória
    for (int i=0; i<50; i++){
      free(*(resultadoGrama+i));
    }
    for (int i=0; i<50; i++){
      free(*(resultadoAsfalto+i));
    }
    free(resultadoAsfalto);
    free(resultadoGrama);

  }else{
    printf("A quantidade de neurônios na camada oculta deve ser definida via linha de comando\n" );
    printf("Exemplo: $ ./nomedoexecutavel 10\n");
    exit(1);
  }
  return 0;
}

void getFeaturesGrass(float **resultadoGrama){
  int grass[50];
  int lin, col;
  int **matrizFile, *ilbp;
  float *glcm, *ilbpGlcm, *ilbpGlcmNormalizado;


  doRandom(grass, 50);
  // Percorre arquivos grass
  for(int i=0; i<50; i++){
    printf("Arquivo número %d (Grass)\n", i);
    FILE *fileGrass;
    fileGrass = getGrassImage(fileGrass, grass[i]);
    getQtdLinhasColunas(fileGrass, &lin, &col);
    // Alocacao dinamica da matriz que ira receber os dados da imagem
    matrizFile = (int**)malloc(lin*sizeof(int *));
    for (int j = 0; j < lin; j++) {
      *(matrizFile+j) = (int*)malloc(col*sizeof(int));
    }
    setMatrizFile(fileGrass, matrizFile, lin, col);

    // Alocacao dinamica para vetores de ilbp, glcm, ilbpGlcm e ilbpGlcmNormalizado
    ilbp = (int *)calloc(512, sizeof (int *));
    glcm = (float *) calloc(24, sizeof (float));
    ilbpGlcm = (float *) calloc(536, sizeof (float));
    ilbpGlcmNormalizado = (float *) calloc(536, sizeof (float));

    ILBP(matrizFile, lin, col, ilbp);
    GLCM(matrizFile, lin, col, glcm);
    concatenaIlbpGlcm(ilbpGlcm, ilbp, glcm);
    dataNormalize(ilbpGlcm, ilbpGlcmNormalizado, 536);
    setResultado(resultadoGrama, ilbpGlcm, i);

    // Liberação de memória
    free(ilbp);
    free(glcm);
    free(ilbpGlcm);
    free(ilbpGlcmNormalizado);
    for (int j = 0; j < lin; j++) {
      free(*(matrizFile+j));
    }
    free(matrizFile);
    fclose(fileGrass);
  }
}

void getFeaturesAsphalt(float **resultadoAsfalto){
  int asphalt[50];
  int lin, col;
  int **matrizFile, *ilbp;
  float *glcm, *ilbpGlcm, *ilbpGlcmNormalizado;

  doRandom(asphalt, 50);
  // Percorre arquivos asphalt
  for(int i=0; i<50; i++){
    printf("Arquivo número %d (Asphalt)\n", i);
    FILE *fileAsphalt;
    fileAsphalt = getAsphaltImage(fileAsphalt, asphalt[i]);
    getQtdLinhasColunas(fileAsphalt, &lin, &col);
    // Alocacao dinamica da matriz que ira receber os dados da imagem
    matrizFile = (int**)malloc(lin*sizeof(int *));
    for (int j = 0; j < lin; j++) {
      *(matrizFile+j) = (int*)malloc(col*sizeof(int));
    }
    setMatrizFile(fileAsphalt, matrizFile, lin, col);

    // Alocacao dinamica para vetores de ilbp, glcm, ilbpGlcm e ilbpGlcmNormalizado
    ilbp = (int *)calloc(512, sizeof (int *));
    glcm = (float *) calloc(24, sizeof (float));
    ilbpGlcm = (float *) calloc(536, sizeof (float));
    ilbpGlcmNormalizado = (float *) calloc(536, sizeof (float));

    ILBP(matrizFile, lin, col, ilbp);
    GLCM(matrizFile, lin, col, glcm);
    concatenaIlbpGlcm(ilbpGlcm, ilbp, glcm);
    dataNormalize(ilbpGlcm, ilbpGlcmNormalizado, 536);
    setResultado(resultadoAsfalto, ilbpGlcm, i);

    // Liberação de memória
    free(ilbp);
    free(glcm);
    free(ilbpGlcm);
    free(ilbpGlcmNormalizado);
    for (int j = 0; j < lin; j++) {
      free(*(matrizFile+j));
    }
    free(matrizFile);
    fclose(fileAsphalt);
  }

}

int getParametroLinhaComando(int argc, char *argv[], int *param){
  if (argc == 1){
    return 0;
  }else{
    *param = atoi(argv[1]);
    return 1;
  }
}


void setResultado(float **matResultado, float *vetNormalizado, int contador){
  for(int i=0; i < 536; i++){
    *(*(matResultado+contador)+i) = *(vetNormalizado+i);
  }
}


void concatenaIlbpGlcm(float *ilbpGlcm, int *ilbp, float *glcm){
  for (int j = 0; j < 512; j++) {
      *(ilbpGlcm + j) = *(ilbp + j);
  }
    for (int j = 512; j < 536; j++) {
      *(ilbpGlcm + j) = *(glcm + (j - 512));
  }
}


void ILBP(int **matrizFile, int lin, int col, int *ilbp){

  char vetorBinario[9];
  int menorDecimal;

  for (int i = 1; i < lin - 1 ; i++) {
    for (int j = 1; j < col - 1 ; j++) {
      setVetorBinario(matrizFile, i, j, vetorBinario);
      menorDecimal = calculaMenorDecimal(vetorBinario);
      ilbp[menorDecimal]++;
    }
  }
}


int calculaMenorDecimal(char *bin) {

  int decimal, m = 0, menorNumero = 512;
  char aux;
  int dec[9];

  for (int q = 9; q > 0; q--) {
    decimal = 0;
    int j = 0;
    for (int i = 8; i >= 0; i--) {
      if (*(bin + i) == '1') {
        decimal += pow(2, j);
      }
      j++;
    }
    // Shift de 1 bit do vetor bin
    aux = bin[8];
    for (int c = 8; c > 0; c--) {
      bin[c] = bin[c - 1];
    }
    bin[0] = aux;

    dec[m] = decimal;
    m++;
  }
  // Encontra o menor numero possivel
  for (int i = 0; i < 9; i++) {
    if (menorNumero > dec[i]) {
      menorNumero = dec[i];
    }
  }
  return menorNumero;
}


void setVetorBinario(int **matrizFile, int lin, int col, char *vetorbin) {
  float soma = 0, media;
  int x = 0, y = 0;
  char **bin;

  bin = (char**)malloc(3*sizeof(char *));
  for (int i = 0; i < 3; i++) {
    *(bin + i) = (char*)malloc(3*sizeof(char));
  }

  for (int i = lin - 1; i <= lin + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
      soma += *(*(matrizFile+i)+j);
    }
  }

  media = soma / 9.0;

  for (int i = lin - 1; i <= lin + 1; i++) {
    for (int j = col - 1; j <= col + 1; j++) {
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
  vetorbin[0] = *(*(bin+0)+0);
  vetorbin[1] = *(*(bin+0)+1);
  vetorbin[2] = *(*(bin+0)+2);
  vetorbin[3] = *(*(bin+1)+2);
  vetorbin[4] = *(*(bin+2)+2);
  vetorbin[5] = *(*(bin+2)+1);
  vetorbin[6] = *(*(bin+2)+0);
  vetorbin[7] = *(*(bin+1)+0);
  vetorbin[8] = *(*(bin+1)+1);

  for (int i = 0; i < 3; i++) {
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
    sprintf(asphalt, "DataSet/asphalt/asphalt_0%d.txt",id);
  else
    sprintf(asphalt, "DataSet/asphalt/asphalt_%d.txt",id);

  printf("Arquivo: %s\n", asphalt);
  fp = fopen(asphalt ,"r");

  if(fp==NULL){
    printf("Falha ao abrir arquivo de imagem.\n");
    exit(1);
  }
  return fp;
}


FILE *getGrassImage(FILE *fp ,int id){
  char grass[25];
  if(id < 10)
    sprintf(grass, "DataSet/grass/grass_0%d.txt",id);
  else
    sprintf(grass, "DataSet/grass/grass_%d.txt",id);

  printf("Arquivo: %s\n", grass);
  fp = fopen(grass ,"r");

  if(fp==NULL){
    printf("Falha.\n");
    exit(1);
  }
  return fp;
}


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
  printf("Ordem do vetor atual: \n");
  for(int i=0; i<limite; i++){
    printf("%d ", vet[i]);
  }
  printf("\n-----------------------\n");
}


void dataNormalize(float *vet, float *vetNormalizado, int limite){
  float menor = 9999999, maior = 0;

  for (int i = 0; i < limite; i++) {
    //calculando menor elemento do vetor
    if(vet[i] < menor)
      menor = vet[i];
    //calculando maior elemento do vetor
    if(vet[i] > maior)
      maior = vet[i];
  }
  //criando vetor normalizado
  for (int i = 0; i < limite; i++)
    vetNormalizado[i] = (vet[i] - menor) / (maior - menor);
}


float euclidianDistance(float *medias, float **resultados, int indice){
  float distancia, soma = 0;

  for (int i = 0; i < 536; i++) {
    soma += pow(*(medias+i) - *(*(resultados+indice)+i), 2);
  }
  return distancia = (pow(soma, 0.5));
}


void calculaMetricas(int **glcm, float *metricas, int initialPosition, int linhaColuna){
  *(metricas + initialPosition) = calculaContraste(glcm, linhaColuna);
  *(metricas + (initialPosition + 1)) = calculaEnergia(glcm, linhaColuna);
  *(metricas + (initialPosition + 2)) = calculaHomogeneidade(glcm, linhaColuna);
}


void GLCM(int **matrizFile, int lin, int col, float *metricas) {
	int **glcm, GLCM_LINHA_COLUNA = 512;
	for (int k = 0; k < 8; k++) {
	// Aloca uma matriz 512x512 para o glcm
    glcm = (int**)calloc(GLCM_LINHA_COLUNA, sizeof(int *));
  	  for (int i = 0; i < GLCM_LINHA_COLUNA; i++) {
  	    *(glcm+i) = (int*)calloc(GLCM_LINHA_COLUNA, sizeof(int));
  	  }
    if (k == 0) {
	   // Incrementa na posicao [indice][indice vizinho a direita] da matriz GLCM e calcula metricas.
      for (int i = 0; i < lin; i++) {
        for (int j = 0; j < col - 1; j++) {
          glcm[matrizFile[i][j]][matrizFile[i][j+1]]++;
		    }
	    }
	    calculaMetricas(glcm, metricas, 0, GLCM_LINHA_COLUNA);
    } else if (k == 1) {
	     // Incrementa na posicao [indice][indice vizinho a esquerda] da matriz GLCM e calcula metricas.
       for (int i = 0; i < lin; i++) {
	        for (int j = 1; j < col; j++) {
	           glcm[matrizFile[i][j]][matrizFile[i][j-1]]++;
	    	  }
	      }
	      calculaMetricas(glcm, metricas, 3, GLCM_LINHA_COLUNA);
	    } else if (k == 2) {
	     // Incrementa a posição [indice][indice vizinho de cima] da matriz GLCM e calcula metricas.
        for (int i = 1; i < lin; i++) {
          for (int j = 0; j < col; j++) {
		        glcm[matrizFile[i][j]][matrizFile[i-1][j]]++;
		      }
		    }
	      calculaMetricas(glcm, metricas, 6, GLCM_LINHA_COLUNA);
	    } else if (k == 3) {
	      // Incrementa a posição [indice][indice vizinho de baixo] da matriz GLCM e calcula metricas.
	    	for (int i = 0; i < lin - 1; i++) {
	        for (int j = 0; j < col; j++) {
	          glcm[matrizFile[i][j]][matrizFile[i+1][j]]++;
	        }
	    	}
	      calculaMetricas(glcm, metricas, 9, GLCM_LINHA_COLUNA);
	    } else if (k == 4) {
	      // Incrementa a posição [indice][indice vizinho da diagonal de cima da esquerda] da matriz GLCM e calcula metricas.
	    	for (int i = 1; i < lin; i++) {
	    		for (int j = 1; j < col; j++) {
	          glcm[matrizFile[i][j]][matrizFile[i-1][j-1]]++;
	       	}
	      }
	      calculaMetricas(glcm, metricas, 12, GLCM_LINHA_COLUNA);
	    } else if (k == 5) {
	      // Incrementa a posição [indice][indice vizinho da diagonal de cima da direita] da matriz GLCM e calcula metricas.
	      for (int i = 1; i < lin; i++) {
	        for (int j = 0; j < col - 1; j++) {
	          glcm[matrizFile[i][j]][matrizFile[i-1][j+1]]++;
	        }
	      }
	      calculaMetricas(glcm, metricas, 15, GLCM_LINHA_COLUNA);
	    } else if (k == 6) {
	      // Incrementa a posição [indice][indice vizinho da diagonal de baixo da esquerda] da matriz GLCM e calcula metricas.
	      for (int i = 0; i < lin - 1; i++) {
	        for (int j = 1; j < col; j++) {
	         	glcm[matrizFile[i][j]][matrizFile[i+1][j-1]]++;
	        }
	      }
	      calculaMetricas(glcm, metricas, 18, GLCM_LINHA_COLUNA);
	    } else if (k == 7) {
	      // Incrementa a posição [indice][indice vizinho da diagonal de baixo da direita] da matriz GLCM e calcula metricas.
	      for (int i = 0; i < lin - 1; i++) {
	        for (int j = 0; j < col - 1; j++) {
	          glcm[matrizFile[i][j]][matrizFile[i+1][j+1]]++;
	        }
	      }
	     	calculaMetricas(glcm, metricas, 21, GLCM_LINHA_COLUNA);
	    }
	    // Libera a memória utilizada pela matriz GLCM.
	    for (int i = 0; i < GLCM_LINHA_COLUNA; i++) {
	      	free(*(glcm+i));
	    }
	    free(glcm);
  	}
}


double calculaContraste(int **matriz, int linhaColuna){
  double total=0.0;
  for (int i = 0; i < linhaColuna; i++) {
    for (int j = 0; j < linhaColuna; j++) {
      total += matriz[i][j]*pow(i-j,2);
    }
  }
  return total;
}


double calculaHomogeneidade(int **matriz, int linhaColuna){
  double total=0.0;
  for (int i = 0; i < linhaColuna; i++) {
    for (int j = 0; j < linhaColuna; j++) {
      total += matriz[i][j]/(1+abs(i-j));
    }
  }
  return total;
}


double calculaEnergia(int **matriz, int linhaColuna){
  double total=0.0;
  for (int i = 0; i < linhaColuna; i++) {
    for (int j = 0; j < linhaColuna; j++) {
      total += pow(matriz[i][j],2);
    }
  }
  return total;
}
