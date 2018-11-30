#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRAMA 'G'
#define ASFALTO 'A'
#define TAXA_APRENDIZAGEM 1

typedef struct neuronio{
    double saida;
    double *w;
    double gradiente;
    double b;
}Neuronio;

typedef struct camada{
  Neuronio *neuronios;
  int qtd_neuronios;
}Camada;

typedef struct rede{
  Camada *camadas;
  int qtd_camadas;
}Rede;

typedef struct imagem{
  int identificador;
  double *feature;
}Imagem;

// Funcoes de busca das features
int get_parametro_linha_comando(int argc, char *argv[]);
void load_features(Imagem **imagens_teste, Imagem **images_treinamento);
void set_matriz_feature(FILE *arq, double **matriz_feature);

// Funcoes de criacao
Rede *do_rede_neural(int qtd_neuronios_ocultos);
Neuronio *do_neuronio(double *p, double b, double *w);

double calculo_saida_neuronio(double *p, double *w, double b);


// Funcoes de aleatorizacao
void do_features_random(Imagem **features_teste, Imagem **features_treinamento);
void do_random(double *var, int semente);
void do_vetor_random(double *vetor, int semente, int tam);
void do_matriz_random(double **matriz, int semente, int linhas, int colunas);

int main(int argc, char *argv[]) {
  // Busca a quantidade de neuronios ocultos passados pela linha de comando pelo usuario
  int qtd_neuronios_ocultos = get_parametro_linha_comando(argc, argv);

  Imagem **features_teste, **features_treinamento;
  // Cria matrizes de imagens de teste e de treinamento
  features_teste = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_teste+i) = (Imagem *)malloc(sizeof(Imagem));
  }
  features_treinamento = (Imagem **)malloc(50*sizeof(Imagem *));
  for (int i=0; i<50; i++){
    *(features_treinamento+i) = (Imagem *)malloc(sizeof(Imagem));
  }
  // Carrega as matrizes com as features das imagens de teste e de treinamento
  load_features(features_teste, features_treinamento);
  // Aleatoriza as matrizes de features de teste e de treinamento
  do_features_random(features_teste, features_treinamento);

  Rede *rede_neural = do_rede_neural(qtd_neuronios_ocultos);

  // Liberacao de memoria
  for (int i=0; i<50; i++){
    free((*(features_teste+i))->feature);
    free(*(features_teste+i));
  }
  free(features_teste);
  for (int i=0; i<50; i++){
    free((*(features_treinamento+i))->feature);
    free(*(features_treinamento+i));
  }
  free(features_treinamento);

  return 0;
}


Rede *do_rede_neural(int qtd_neuronios_ocultos){
  // Cria a rede neural
  Rede *nova_rede = (Rede *)malloc(sizeof(Rede));
  nova_rede->qtd_camadas = 3;
  // Cria as camadas da rede neural
  Camada *camadas = (Camada *)malloc(3*sizeof(Camada));
  for (int i=0; i<3; i++){
    if (i==0){
      // Cria os neuronios da camada de entrada
      Neuronio *neuronios_entrada = (Neuronio *)malloc(536*sizeof(Neuronio));
      double *w = (double *)malloc(536*sizeof(double));
      double b[536];
      do_vetor_random(b, 1, 536);
      do_vetor_random(w, 2, 536);
      for (int j=0; j<536; j++){
        (neuronios_entrada+j)->w = w;
        (neuronios_entrada+j)->b = b[j];
      }
      (camadas+i)->neuronios = neuronios_entrada;
      (camadas+i)->qtd_neuronios = 536;
    }else if (i==1){
      // Cria os neuronios da camada oculta
      Neuronio *neuronios_oculta = (Neuronio *)malloc(qtd_neuronios_ocultos*sizeof(Neuronio));
      double b[qtd_neuronios_ocultos];
      do_vetor_random(b, 3, qtd_neuronios_ocultos);
      for (int j=0; j<qtd_neuronios_ocultos; j++){
        (neuronios_oculta+j)->w = NULL;
        (neuronios_oculta+j)->b = b[j];
      }
      (camadas+i)->neuronios = neuronios_oculta;
      (camadas+i)->qtd_neuronios = qtd_neuronios_ocultos;
    }else if (i==2){
      // Cria os neuronios da camada de saida
      Neuronio *neuronios_saida = (Neuronio *)malloc(sizeof(Neuronio));
      double b;
      do_random(&b, 4);
      for (int j=0; j<1; j++){
        (neuronios_saida+j)->b = NULL;
        (neuronios_saida+j)->b = b;
      }
      (camadas+i)->neuronios = neuronios_saida;
      (camadas+i)->qtd_neuronios = 1;
    }
  }
  nova_rede->camadas = camadas;

  return nova_rede;
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
    nova_imagem->feature = (double *)malloc(536*sizeof(double));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_grama+i)+j));
    }
    nova_imagem->identificador = GRAMA;
    *(imagens_teste+i) = nova_imagem;
  }
  // Cria 25 imagens de asfalto para a feature de teste
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    nova_imagem->feature = (double *)malloc(536*sizeof(double));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_asfalto+i)+j));
    }
    nova_imagem->identificador = ASFALTO;
    *(imagens_teste+i+25) = nova_imagem;
  }
  // Cria 25 imagens de grama para a feature de treinamento
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    nova_imagem->feature = (double *)malloc(536*sizeof(double));
    for(int j=0; j<536; j++){
      *(nova_imagem->feature+j) = (*(*(features_grama+i+25)+j));
    }
    nova_imagem->identificador = GRAMA;
    *(imagens_treinamento+i) = nova_imagem;
  }
  // Cria 25 imagens de asfalto para a feature de treinamento
  for (int i=0; i<25; i++) {
    Imagem *nova_imagem = (Imagem *)malloc(sizeof(Imagem));
    nova_imagem->feature = (double *)malloc(536*sizeof(double));
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


Neuronio *do_neuronio(double *p, double b, double *w){
  Neuronio *novo_neuronio = (Neuronio *)malloc(sizeof(Neuronio));
  if (novo_neuronio == NULL){
      printf("Erro na alocação!\n");
      exit(1);
  }
  double s = calculo_saida_neuronio(p, w, b);
  novo_neuronio->saida = s;
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
