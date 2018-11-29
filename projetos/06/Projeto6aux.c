#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRAMA 'G'
#define ASFALTO 'A'

typedef struct neuronio{
    double s;
    struct neuronio **proxima;
}Neuronio;

typedef struct imagem{
  char identificador;
  double feature[536];
}Imagem;

int get_parametro_linha_comando(int argc, char *argv[]);
void load_features(Imagem **imagens_teste, Imagem **images_treinamento);
void set_matriz_feature(FILE *arq, double **matriz_feature);


int main(int argc, char *argv[]) {

  int qtd_neuronios_ocultos = get_parametro_linha_comando(argc, argv);
  Imagem **features_teste, **features_treinamento;

  features_teste = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_teste+i) = (Imagem *)malloc(sizeof(Imagem));
  }
  features_treinamento = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_treinamento+i) = (Imagem *)malloc(sizeof(Imagem));
  }

  load_features(features_teste, features_treinamento);

  // Liberação de memoria
  for (int i=0; i<50; i++){
    free(*(features_teste+i));
  }
  for (int i=0; i<50; i++){
    free(*(features_treinamento+i));
  }
  free(features_teste);
  free(features_treinamento);

  return 0;
}

int get_parametro_linha_comando(int argc, char *argv[]){
  if (argc == 1){
    printf("A quantidade de neurônios na camada oculta deve ser definida via linha de comando\n" );
    printf("Exemplo: $ ./nomedoexecutavel 10\n");
    exit(1);
  }else{
    return atoi(argv[1]);
  }
}

void load_features(Imagem **imagens_teste, Imagem **imagens_treinamento){
  int linhas, colunas;
  FILE *arq;
  double **features_asfalto, **features_grama;

  features_grama = (double **)malloc(50*sizeof(double *));
  for (int i=0; i<50; i++){
    *(features_grama+i) = (double *)malloc(536*sizeof(double));
  }
  features_asfalto = (double **)malloc(50*sizeof(double *));
  for (int i=0; i<50; i++){
    *(features_asfalto+i) = (double *)malloc(536*sizeof(double));
  }

  arq = fopen("asfalto.txt", "r");
  if (arq == NULL){
    printf("Não foi possível abrir o arquivo!\n" );
    exit(1);
  }else{
    set_matriz_feature(arq ,features_asfalto);
  }
  fclose(arq);

  arq = fopen("grama.txt", "r");
  if (arq == NULL){
    printf("Não foi possível abrir o arquivo!\n" );
    exit(1);
  }else{
    set_matriz_feature(arq ,features_grama);
  }
  fclose(arq);

  // Cria 25 imagens de grama para a feature de teste
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_grama+i)+j));
    }
    nova_imagem->identificador = GRAMA;
    *(imagens_teste+i) = nova_imagem;
  }

  // Cria 25 imagens de asfalto para a feature de teste
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_asfalto+i)+j));
    }
    nova_imagem->identificador = ASFALTO;
    *(imagens_teste+i+25) = nova_imagem;
  }

  // Cria 25 imagens de grama para a feature de treinamento
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_grama+i+25)+j));
    }
    nova_imagem->identificador = GRAMA;
    *(imagens_treinamento+i) = nova_imagem;
  }

  // Cria 25 imagens de asfalto para a feature de treinamento
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_asfalto+i+25)+j));
    }
    nova_imagem->identificador = ASFALTO;
    *(imagens_treinamento+i+25) = nova_imagem;
  }

  for (int i=0; i<50; i++){
    free(*(features_grama+i));
  }
  for (int i=0; i<50; i++){
    free(*(features_asfalto+i));
  }
  free(features_grama);
  free(features_asfalto);
}

void set_matriz_feature(FILE *arq, double **matriz_feature){
  char pv;
  rewind(arq);
  for (int i = 0; i < 50; i++) {
    for (int j = 0; j < 536; j++) {
      if (!feof(arq)) {
        fscanf(arq, "%lf%c", *(matriz_feature+i)+j, &pv);
      }
    }
  }
}
