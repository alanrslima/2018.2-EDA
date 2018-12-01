#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define GRAMA 1
#define ASFALTO 0
#define TAXA_APRENDIZAGEM 1

typedef struct neuronio{
    double saida;
    double *w;
    double gradiente;
    double b;
}Neuronio;

typedef struct imagem{
  int identificador;
  double *feature;
}Imagem;

// Funcoes de busca das features
int get_parametro_linha_comando(int argc, char *argv[]);
void load_features(Imagem **imagens_teste, Imagem **images_treinamento);
void set_matriz_feature(FILE *arq, double **matriz_feature);

// Funcoes de criacao
void update_neuronio(Neuronio *neuronio, double *p);
void do_rede_neural(Neuronio **c_entrada, Neuronio **c_oculta, Neuronio **c_saida, int qtd_neuronios_ocultos);
Neuronio **do_camada(int tam_camada);
double do_ciclo_treinamento(Neuronio **c_entrada, Neuronio **c_oculta, Neuronio **c_saida, Imagem *imagem, int qtd_neuronios_ocultos);

double calcula_media_quadratica(double *vet, int tam);

// Funcoes de aleatorizacao
void do_features_random(Imagem **features_teste, Imagem **features_treinamento);
void do_random(double *var, int semente);
void do_vetor_random(double *vetor, int semente, int tam);
void do_matriz_random(double **matriz, int semente, int linhas, int colunas);

// Funcoes BP
double derivada_logistica(double s);
void gradiente_saida(Neuronio *neuronio, double erro);
void gradiente_neuronio(Neuronio *neuronio, Neuronio **camada, int i);
void ajuste_w(Neuronio *neuronio, double *w, double *p);
void ajuste_b(Neuronio *neuronio);


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

  Neuronio **camada_entrada = do_camada(536); // **
  Neuronio **camada_oculta = do_camada(qtd_neuronios_ocultos); // **
  Neuronio **camada_saida = do_camada(1); // **

  do_rede_neural(camada_entrada, camada_oculta, camada_saida, qtd_neuronios_ocultos);

  double *saidas = (double *)malloc(50*sizeof(double)); // **
  int count = 0;
  double media_quadratica = 0.5;
  do{
    for (int i=0; i<50; i++){
      *(saidas+i) = do_ciclo_treinamento(camada_entrada, camada_oculta, camada_saida, *(features_treinamento+i), qtd_neuronios_ocultos);
    }
    media_quadratica = calcula_media_quadratica(saidas, 50);
    count++;
  }while(count<10);

  // Liberacao de memoria
  for (int i=0; i<50; i++){
    free((*(features_teste+i))->feature);
    free(*(features_teste+i));
  }
  free(features_teste);
  features_teste = NULL;

  for (int i=0; i<50; i++){
    free((*(features_treinamento+i))->feature);
    free(*(features_treinamento+i));
  }
  free(features_treinamento);
  features_treinamento = NULL;

  for (int i=0; i<536; i++){
    free(*(camada_entrada+i));
  }
  free(camada_entrada);
  camada_entrada = NULL;

  for (int i=0; i<qtd_neuronios_ocultos; i++){
    free(*(camada_oculta+i));
  }
  free(camada_oculta);
  camada_oculta = NULL;

  for (int i=0; i<1; i++){
    free(*(camada_saida+i));
  }
  free(camada_saida);
  camada_saida = NULL;

  return 0;
}

double calcula_media_quadratica(double *vet, int tam){
  double s = 0;
  for(int i=0; i<tam; i++){
    s += (*(vet+i)) * (*(vet+i));
  }
  return s/tam;
}

Neuronio **do_camada(int tam_camada){
  Neuronio **nova_camada = (Neuronio **)malloc(tam_camada*sizeof(Neuronio *));
  for (int i=0; i<tam_camada; i++){
    *(nova_camada+i) = (Neuronio *)malloc(sizeof(Neuronio));
  }
  return nova_camada;
}


void do_rede_neural(Neuronio **c_entrada, Neuronio **c_oculta, Neuronio **c_saida, int qtd_neuronios_ocultos){

  double *w_entrada = (double *)malloc(536*sizeof(double));
  double b_entrada[536];
  do_vetor_random(b_entrada, 1, 536);
  do_vetor_random(w_entrada, 2, 536);
  for (int i=0; i<536; i++){
    (*(c_entrada+i))->w = w_entrada;
    (*(c_entrada+i))->b = b_entrada[i];
  }

  double *w_oculta = (double *)malloc(536*sizeof(double));
  double b_oculta[qtd_neuronios_ocultos];
  do_vetor_random(b_oculta, 1, qtd_neuronios_ocultos);
  do_vetor_random(w_oculta, 2, 536);
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    (*(c_oculta+i))->w = w_oculta;
    (*(c_oculta+i))->b = b_oculta[i];
  }

  double *w_saida = (double *)malloc(qtd_neuronios_ocultos*sizeof(double));
  double b_saida[qtd_neuronios_ocultos];
  do_vetor_random(b_saida, 1, 1);
  do_vetor_random(w_saida, 2, qtd_neuronios_ocultos);
  for (int i=0; i<1; i++){
    (*(c_saida+i))->w = w_saida;
    (*(c_saida+i))->b = b_saida[i];
  }
}

double do_ciclo_treinamento(Neuronio **c_entrada, Neuronio **c_oculta, Neuronio **c_saida, Imagem *imagem, int qtd_neuronios_ocultos){
  double *p_entrada = imagem->feature;

  // Calcula o s de todos os neuronios de entrada
  for (int i=0; i<536; i++){
    update_neuronio(*(c_entrada+i), p_entrada);
  }

  double p_oculta[536];
  for (int i=0; i<536; i++){
    p_oculta[i] = (*(c_entrada+i))->saida;
  }
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    update_neuronio(*(c_oculta+i), p_oculta);
  }

  double p_saida[qtd_neuronios_ocultos];
  for (int i=0; i<qtd_neuronios_ocultos; i++){
    p_saida[i] = (*(c_oculta+i))->saida;
  }
  for (int i=0; i<1; i++){
    update_neuronio(*(c_saida+i), p_saida);
  }

  double erro = imagem->identificador - (*(c_saida))->saida;

  // Inicio do BP
  gradiente_saida(*(c_saida), erro);

  for(int i = 0; i < qtd_neuronios_ocultos; i++){
    gradiente_neuronio(*(c_oculta+i), c_saida, i);
  }


  return erro;
}


void update_neuronio(Neuronio *neuronio, double *p){
  double n, somatorio = 0;

  for(int i=0; i<536; i++){
    somatorio += (*((neuronio->w)+i)) * (*(p+i));
  }
  n = somatorio + neuronio->b;
  neuronio->saida = 1 / (1 + exp(-n));
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
    printf("%d ", (*(features_teste+i))->identificador);
  }
  printf("\n-----------------------\n\n");
  printf("Ordem do vetor de treinamento: \n");
  for(int i=0; i<50; i++){
    printf("%d ", (*(features_treinamento+i))->identificador);
  }
  printf("\n-----------------------\n");
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

double derivada_logistica(double s){
  double derivada;

  derivada = -((exp(s)) / pow(exp(s) - 1, 2));

  return derivada;
}

void gradiente_saida(Neuronio *neuronio, double erro){
  double derivada = derivada_logistica(neuronio -> saida);
  neuronio -> gradiente = derivada * erro;
}

/*void gradiente_neuronio(Neuronio *neuronio, Neuronio **camada, int i){
  double derivada = derivada_logistica(neuronio -> saida);
  double somatorio = 0;

  for(){
    somatorio += ;
  }

  neuronio -> gradiente = somatorio * derivada;
}*/

//void ajuste_w(Neuronio *neuronio, double *w, double *p){
   // neuronio -> (w+i) = neuronio -> (w+i) + TAXA_APRENDIZAGEM * (*p+i)/*saida do vetor anterior*/ * neuronio -> gradiente;
//}

void ajuste_b(Neuronio *neuronio){
    neuronio -> b = neuronio -> b + TAXA_APRENDIZAGEM * neuronio -> gradiente;
}