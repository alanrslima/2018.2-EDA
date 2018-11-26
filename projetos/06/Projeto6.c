#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct neuronio{
    // double p[536]; //Entrada
    // double w[536]; //Núcleo
    // double b;
    double s; //Saida
    struct neuronio *proxima;
}Neuronio;

int get_parametro_linha_comando(int argc, char *argv[], int *param);
int load_features(double **feature, char *url);
void get_qtd_linhas_colunas(FILE *fp, int *linhas, int *colunas);
void set_matriz_feature(FILE *arq, double **matriz_feature, int lin, int col);
Neuronio *do_neuronio(double *p, double b);
double calculo_saida_neuronio(double *p, double *w, double b);
void do_random(double *vetor, int semente);


int main(int argc, char *argv[]) {
  int qtd_neuronios_ocultos;

  if (!get_parametro_linha_comando(argc, argv, &qtd_neuronios_ocultos)){
    printf("A quantidade de neurônios na camada oculta deve ser definida via linha de comando\n" );
    printf("Exemplo: $ ./nomedoexecutavel 10\n");
    exit(1);
  }

  double **feature_grama, **feature_asfalto;

  feature_asfalto = (double **)malloc(50*sizeof(double *));
  for (int i=0; i<50; i++){
    *(feature_asfalto+i) = (double *)malloc(536*sizeof(double));
  }
  feature_grama = (double **)malloc(50*sizeof(double *));
  for (int i=0; i<50; i++){
    *(feature_grama+i) = (double *)malloc(536*sizeof(double));
  }

  if (load_features(feature_asfalto, "asfalto.txt")){
    Neuronio **camada_entrada = (Neuronio **)malloc(536*sizeof(Neuronio *));
    double b[536];
    
    for (int i=0; i<536; i++){
      *(camada_entrada+i) = (Neuronio *)malloc(sizeof(Neuronio));
    }

    do_random(b,5);
    for (int i=0; i<536; i++){
      *(camada_entrada+i) = do_neuronio(feature_asfalto[0], b[i]);
    }

    for (int i=0; i<536; i++){
      free(*(camada_entrada+i));
    }
    free(camada_entrada);
  }

  //Liberacao de memória
  for (int i=0; i<50; i++){
    free(*(feature_grama+i));
  }
  for (int i=0; i<50; i++){
    free(*(feature_asfalto+i));
  }
  free(feature_asfalto);
  free(feature_grama);

  return 0;
}

void do_random(double *vetor, int semente){
  srand(time(NULL)+semente);
  for (int i=0; i<536; i++){
    *(vetor+i) = (rand() % 31999) - 16000;
  }
}

Neuronio *do_neuronio(double *p, double b){
  Neuronio *novo_neuronio = (Neuronio *)malloc(sizeof(Neuronio));

  if (novo_neuronio == NULL){
      printf("Erro na alocação!\n");
      exit(1);
  }
  double w[536];
  do_random(w, 2);

  printf("%lf \n", calculo_saida_neuronio(p, w, b));

  novo_neuronio->s = 2;
  novo_neuronio->proxima = NULL;
  return novo_neuronio;

}

double calculo_saida_neuronio(double *p, double *w, double b){
  double somatorio = 0;
  double n, s;

  for(int i=0; i<536; i++){
    somatorio += (*(w+i)) * (*(p+i));
  }
  n = somatorio + b;
  s = 1 / (1 + exp(-n));

  return s;
}

int load_features(double **feature, char *url){
  int linhas, colunas;
  FILE *arq;

  arq = fopen(url, "r");
  if (arq == NULL){
    printf("Não foi possível abrir o arquivo!\n" );
    return 0;
  }else{
    get_qtd_linhas_colunas(arq, &linhas, &colunas);
    set_matriz_feature(arq ,feature, linhas, colunas);
    return 1;
  }
  fclose(arq);
}

void set_matriz_feature(FILE *arq, double **matriz_feature, int lin, int col){
  char pv;
  rewind(arq);
  for (int i = 0; i < lin; i++) {
    for (int j = 0; j < col; j++) {
      if (!feof(arq)) {
        fscanf(arq, "%lf%c", *(matriz_feature+i)+j, &pv);
      }
    }
  }
}

void get_qtd_linhas_colunas(FILE *fp, int *linhas, int *colunas){
	char marcador;
	*linhas = 0, *colunas = 1;
	while ((marcador = fgetc(fp)) != EOF) {
		if (marcador == '\n') {
			*linhas = *linhas + 1;
		}
		else if (*linhas == 0 && marcador == ' ') {
			*colunas = *colunas + 1;
		}
	}
	printf("Quantidade de linhas: %d, Quantidade de colunas: %d\n\n", *linhas, *colunas);
}

int get_parametro_linha_comando(int argc, char *argv[], int *param){
  if (argc == 1){
    return 0;
  }else{
    *param = atoi(argv[1]);
    return 1;
  }
}
