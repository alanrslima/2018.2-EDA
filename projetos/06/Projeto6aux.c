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
void do_features_random(Imagem **features_teste, Imagem **features_treinamento);
double do_ciclo_neuronio(Imagem *imagem, int qtd_neuronios_ocultos, double **w_entrada, double *b_entrada);
Neuronio *do_neuronio(double *p, double b, double *w);
double calculo_saida_neuronio(double *p, double *w, double b);

void do_random(double *var, int semente);
void do_vetor_random(double *vetor, int semente, int tam);
void do_matriz_random(double **matriz, int semente, int linhas, int colunas);


int main(int argc, char *argv[]) {

  // Busca a quantidade de neuronios ocultos passados pela linha de comando pelo usuario
  int qtd_neuronios_ocultos = get_parametro_linha_comando(argc, argv);

  Imagem **features_teste, **features_treinamento;
  // Cria vetores de imagens de teste e de treinamento
  features_teste = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_teste+i) = (Imagem *)malloc(sizeof(Imagem));
  }
  features_treinamento = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_treinamento+i) = (Imagem *)malloc(sizeof(Imagem));
  }
  // Carrega todas as imagens(features) de teste e de treinamento
  load_features(features_teste, features_treinamento);
  // Aleatoriza todas as imagens(features) de teste e de treinamento
  do_features_random(features_teste, features_treinamento);

  // Cria matriz w de entrada no ciclo
  double **w_entrada = (double **)malloc(536*sizeof(double *));
  for (int i=0; i<536; i++){
    *(w_entrada+i) = (double *)malloc(536*sizeof(double));
  }
  // Cria vetor b de entrada no ciclo
  double *b_entrada = (double *)malloc(536*sizeof(double));

  do_matriz_random(w_entrada, 2, 536, 536);
  do_vetor_random(b_entrada, 3, 536);

  for (int count=0; count<1; count++){
    do_ciclo_neuronio(*(features_teste+count), qtd_neuronios_ocultos, w_entrada, b_entrada);
  }

  // Liberação de memoria
  free(b_entrada);
  for (int i=0; i<536; i++){
    free(*(w_entrada+i));
  }
  free(w_entrada);
  for (int i=0; i<50; i++){
    free(*(features_teste+i));
  }
  free(features_teste);
  for (int i=0; i<50; i++){
    free(*(features_treinamento+i));
  }
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


void do_features_random(Imagem **features_teste, Imagem **features_treinamento){
  srand(time(NULL));
  // Aleatoriza as imagens de teste
  for (int i = 0; i < 50; i++) {
    Imagem *aux = *(features_teste+i);
    int random = rand() % 50;
    *(features_teste+i) = *(features_teste+random);
    *(features_teste+random) = aux;
  }
  // Aleatoriza as imagens de treinamento
  for (int i = 0; i < 50; i++) {
    Imagem *aux = *(features_treinamento+i);
    int random = rand() % 50;
    *(features_treinamento+i) = *(features_treinamento+random);
    *(features_treinamento+random) = aux;
  }

  printf("\nOrdem do vetor de testes: \n");
  for(int i=0; i<50; i++){
    printf("%c ", (*(features_teste+i))->identificador);
  }
  printf("\n-----------------------\n\n");
  printf("Ordem do vetor de treinamento: \n");
  for(int i=0; i<50; i++){
    printf("%c ", (*(features_treinamento+i))->identificador);
  }
  printf("\n-----------------------\n");
}


double do_ciclo_neuronio(Imagem *imagem, int qtd_neuronios_ocultos, double **w_entrada, double *b_entrada){
  Neuronio **camada_entrada, **camada_oculta, **camada_saida;
  double *p_camada_entrada = imagem->feature;

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

  // Cria todos os neuronios da camada de entrada
  for (int i=0; i<536; i++){
    *(camada_entrada+i) = do_neuronio(p_camada_entrada, *(b_entrada+i), *(w_entrada+i));
  }

  // Seta valores do vetor de entrada da camada oculta com base nas saidas
  // dos neuronios da camada de entrada
  double *p_camada_oculta = (double *)malloc(536*sizeof(double));
  for (int i=0; i<536; i++){
    *(p_camada_oculta+i) = (*(camada_entrada+i))->s;
  }
  // Cria matriz de valores w para a camada oculta
  double **w_camada_oculta = (double **)malloc(qtd_neuronios_ocultos*sizeof(double *));
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    *(w_camada_oculta+i) = (double *)malloc(qtd_neuronios_ocultos*sizeof(double));
  }
  do_matriz_random(w_camada_oculta, 1, qtd_neuronios_ocultos, qtd_neuronios_ocultos);
  // Cria vetor de valores b para a camada oculta
  double *b_oculta = (double *)malloc(qtd_neuronios_ocultos*sizeof(double));
  do_vetor_random(b_oculta, 4, qtd_neuronios_ocultos);
  // Cria todos os neuronios da camada oculta
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    *(camada_oculta+i) = do_neuronio(p_camada_oculta, *(b_oculta+i), *(w_camada_oculta+i));
  }

  // Seta valores do vetor de entrada da camada de saida com base nas saidas
  // dos neuronios da camada oculta
  double *p_camada_saida = (double *)malloc(536*sizeof(double));
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    *(p_camada_saida+i) = (*(camada_oculta+i))->s;
  }
  double *w_camada_saida = (double *)malloc(qtd_neuronios_ocultos*sizeof(double));

  double b_saida;
  do_random(&b_saida, 3);
  // Cria todos os neuronios da camada de saida
  for (int i=0; i<1; i++){
    *(camada_saida+i) = do_neuronio(p_camada_saida, b_saida, w_camada_saida);
  }

  // Aponta cada neuronio da camada de entrada para a camada oculta
  // set_proxima_camada(camada_entrada, 536, camada_oculta);
  // Aponta cada neuronio da camada oculta para a camada de saida
  // set_proxima_camada(camada_oculta, qtd_neuronios_ocultos, camada_saida);

  double saida = (*(camada_saida))->s;

  //Liberacao de memória
  free(b_oculta);
  free(p_camada_oculta);
  free(p_camada_saida);
  free(w_camada_saida);

  for (int i=0; i<qtd_neuronios_ocultos; i++){
    free(*(w_camada_oculta+i));
  }
  free(w_camada_oculta);
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
  return saida;
}


Neuronio *do_neuronio(double *p, double b, double *w){
  Neuronio *novo_neuronio = (Neuronio *)malloc(sizeof(Neuronio));

  if (novo_neuronio == NULL){
      printf("Erro na alocação!\n");
      exit(1);
  }
  double s = calculo_saida_neuronio(p, w, b);
  novo_neuronio->s = s;
  novo_neuronio->proxima = NULL;
  return novo_neuronio;
}


void do_random(double *var, int semente){
  srand(time(NULL)+semente);
  *var = (rand() % 31999) - 16000;
}


void do_vetor_random(double *vetor, int semente, int tam){
  srand(time(NULL)+semente);
  for (int i=0; i<tam; i++){
    *(vetor+i) = (rand() % 31999) - 16000;
  }
}


void do_matriz_random(double **matriz, int semente, int linhas, int colunas){
  srand(time(NULL)+semente);
  for(int i=0; i<linhas; i++){
    for(int j=0; j<colunas; j++){
      *(*(matriz+i)+j) = (rand() % 31999) - 16000;
    }
  }
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
