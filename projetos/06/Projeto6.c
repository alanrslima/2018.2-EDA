#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

typedef struct neuronio{
    // double p[536]; //Entrada
    // double w[536]; //Núcleo
    // double b;
    double s; //Saida
    struct neuronio **proxima;
}Neuronio;

int get_parametro_linha_comando(int argc, char *argv[], int *param);
int load_features(double **feature, char *url);
void get_qtd_linhas_colunas(FILE *fp, int *linhas, int *colunas);
void set_matriz_feature(FILE *arq, double **matriz_feature, int lin, int col);
Neuronio *do_neuronio(double *p, double b);
double calculo_saida_neuronio(double *p, double *w, double b);
void do_vetor_random(double *vetor, int semente);
double do_random(int semente);
void set_proxima_camada(Neuronio **camada,int tam_camada, Neuronio **proxima_camada);

int main(int argc, char *argv[]) {
  int qtd_neuronios_ocultos;

  if (!get_parametro_linha_comando(argc, argv, &qtd_neuronios_ocultos)){
    printf("A quantidade de neurônios na camada oculta deve ser definida via linha de comando\n" );
    printf("Exemplo: $ ./nomedoexecutavel 10\n");
    exit(1);
  }
  double **feature_asfalto, **feature_grama;

  // feature_grama = (double **)malloc(50*sizeof(double *));
  // for (int i=0; i<50; i++){
  //   *(feature_grama+i) = (double *)malloc(536*sizeof(double));
  // }

  feature_asfalto = (double **)malloc(50*sizeof(double *));
  for (int i=0; i<50; i++){
    *(feature_asfalto+i) = (double *)malloc(536*sizeof(double));
  }

  if (load_features(feature_asfalto, "asfalto.txt")){
    double *saidas = (double *)malloc(50*sizeof(double));
    for (int count=0; count<50; count++){
      Neuronio **camada_entrada, **camada_oculta, **camada_saida;

      // Aloca dinamicamente uma matriz de neuronios, que será a camada de entrada
      camada_entrada = (Neuronio **)malloc(536*sizeof(Neuronio *));
      for (int i=0; i<536; i++){
        *(camada_entrada+i) = (Neuronio *)malloc(sizeof(Neuronio));
      }
      // Aloca dinamicamente uma matriz de neuronios, que será a camada oculta
      camada_oculta = (Neuronio **)malloc(qtd_neuronios_ocultos*sizeof(Neuronio *));
      for (int i=0; i<qtd_neuronios_ocultos; i++){
        *(camada_oculta+i) = (Neuronio *)malloc(sizeof(Neuronio));
      }
      // Aloca dinamicamente uma matriz de neuronios, que será a camada de saida
      camada_saida = (Neuronio **)malloc(sizeof(Neuronio *));
      for (int i=0; i<1; i++){
        *(camada_saida+i) = (Neuronio *)malloc(sizeof(Neuronio));
      }

      double *b = (double *)malloc(536*sizeof(double));
      do_vetor_random(b, 1);
      // Cria todos os neuronios da camada de entrada
      for (int i=0; i<536; i++){
        *(camada_entrada+i) = do_neuronio(feature_asfalto[count], *(b+i));
      }

      // Seta valores do vetor de entrada da camada oculta com base nas saidas
      // dos neuronios da camada de entrada
      double *p_camada_oculta = (double *)malloc(536*sizeof(double));
      for (int i=0; i<536; i++){
        *(p_camada_oculta+i) = (*(camada_entrada+i))->s;
      }
      do_vetor_random(b, 4);
      // Cria todos os neuronios da camada oculta
      for (int i=0; i<qtd_neuronios_ocultos; i++){
        *(camada_oculta+i) = do_neuronio(p_camada_oculta, *(b+i));
      }

      // Seta valores do vetor de entrada da camada de saida com base nas saidas
      // dos neuronios da camada oculta
      double *p_camada_saida = (double *)malloc(536*sizeof(double));
      for (int i=0; i<qtd_neuronios_ocultos; i++){
        *(p_camada_saida+i) = (*(camada_oculta+i))->s;
      }
      do_vetor_random(b, 3);
      // Cria todos os neuronios da camada de saida
      for (int i=0; i<1; i++){
        *(camada_saida+i) = do_neuronio(p_camada_saida, *(b+i));
      }

      // Aponta cada neuronio da camada de entrada para a camada oculta
      set_proxima_camada(camada_entrada, 536, camada_oculta);
      // Aponta cada neuronio da camada oculta para a camada de saida
      set_proxima_camada(camada_oculta, qtd_neuronios_ocultos, camada_saida);

      *(saidas+count) = (*(camada_saida))->s;

      //Liberacao de memória
      free(b);
      free(p_camada_oculta);
      free(p_camada_saida);
      for (int i=0; i<536; i++){
        free(*(camada_entrada+i));
      }
      free(camada_entrada);
      for (int i=0; i<qtd_neuronios_ocultos; i++){
        free(*(camada_oculta+i));
      }
      free(camada_oculta);
      for (int i=0; i<1; i++){
        free(*(camada_saida+i));
      }
      free(camada_saida);
    }
    for(int i=0; i<50; i++){
      printf("s = %lf\n", *(saidas+i));
    }
    free(saidas);
  }

  //Liberacao de memória
  // for (int i=0; i<50; i++){
  //   free(*(feature_grama+i));
  // }
  for (int i=0; i<50; i++){
    free(*(feature_asfalto+i));
  }
  free(feature_asfalto);
  // free(feature_grama);

  return 0;
}

void set_proxima_camada(Neuronio **camada,int tam_camada, Neuronio **proxima_camada){
  for (int i=0; i<tam_camada; i++){
    (*(camada+i))->proxima = proxima_camada;
  }
}

void do_vetor_random(double *vetor, int semente){
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
  double w[536], s;
  do_vetor_random(w, 2);

  s = calculo_saida_neuronio(p, w, b);
  novo_neuronio->s = s;
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
}

int get_parametro_linha_comando(int argc, char *argv[], int *param){
  if (argc == 1){
    return 0;
  }else{
    *param = atoi(argv[1]);
    return 1;
  }
}
