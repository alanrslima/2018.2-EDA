#include <stdio.h>
#include <stdlib.h>
//#include <stdbool.h>
#include <time.h>
//#include <math.h>

/* Pega o parametro passado via linha de comando */
int get_parametro_linha_comando(int argc, char *argv[], int *param);

int load_features(double **feature, char *url);

void get_qtd_linhas_colunas(FILE *fp, int *linhas, int *colunas);

void set_matriz_feature(FILE *arq, double **matriz_feature, int lin, int col);

int main(int argc, char *argv[]) {
  int qtd_neuronios_ocultos;
  if (get_parametro_linha_comando(argc, argv, &qtd_neuronios_ocultos)){
    double **feature_grama, **feature_asfalto;

    feature_asfalto = (double **)malloc(50*sizeof(double *));
    for (int i=0; i<50; i++){
      *(feature_asfalto+i) = (double *)malloc(536*sizeof(double));
    }

    feature_grama = (double **)malloc(50*sizeof(double *));
    for (int i=0; i<50; i++){
      *(feature_grama+i) = (double *)malloc(536*sizeof(double));
    }

    load_features(feature_asfalto, "asfalto.txt");
    load_features(feature_asfalto, "grama.txt");

    // for (int i = 0; i < 50; i++) {
    //   for (int j = 0; j < 536; j++) {
    //     printf("%lf, ",  feature_asfalto[i][j]);
    //   }
    //   printf("\n\n\n" );
    // }

    //Liberacao de memória
    for (int i=0; i<50; i++){
      free(*(feature_grama+i));
    }
    for (int i=0; i<50; i++){
      free(*(feature_asfalto+i));
    }
    free(feature_asfalto);
    free(feature_grama);

  }else{
    printf("A quantidade de neurônios na camada oculta deve ser definida via linha de comando\n" );
    printf("Exemplo: $ ./nomedoexecutavel 10\n");
    exit(1);
  }
  return 0;
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
