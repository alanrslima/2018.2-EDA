#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void GeraAleatorios(int *, int tamVet, int limite);
bool Existe(int *, int tamVet, int valor);
void getAsphaltImage(FILE *,int random);

int main(){
  FILE *asphalt_images[25], *grass_images[25];
  int grass[25], asphalt[25];

  GeraAleatorios(asphalt, 25, 50);

  printf("Ordem do vetor de asfalto: \n");
  for(int i=0; i<25; i++){
    printf("%d ", asphalt[i]);
  }
  printf("\n-----------------------\n");

  // for(int i=0; i<25; i++){
    // print("Arquivo número %d", i);

      FILE *fileAsphalt;
      getAsphaltImage(fileAsphalt, asphalt[0]);

  // }


  return 0;
}

void getAsphaltImage(FILE *fp ,int id){

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
  srand(time(NULL));
  int random;
  for(int i=0; i<tamVet; i++){
    random = rand() % limite;
    while (Existe(vet, i, random)) {
      random = rand() % limite;
    }
    vet[i] = random;
  }
}
