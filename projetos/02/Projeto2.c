#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

void GeraAleatorios(int numeros[], int quantNumeros, int Limite);
bool Existe(int valores[], int tam, int valor);
FILE* get_asphalt_images(int random);

int main(){
	FILE *asphalt_images[25], *grass_images[25];
	int aleatorios[25];

	GeraAleatorios(aleatorios, 25, 50);

	for(int i=0; i<25; i++)
    get_asphalt_images(aleatorios[i]);

	return 0;
}

FILE* get_asphalt_images(int random){

	FILE *fp;
	char asphalt[25];

	if(random < 11)
		sprintf(asphalt, "/home/marco/Documentos/2018.2-EDA/projetos/02/asphalt/asphalt_0%d.txt",random);
	else
		sprintf(asphalt, "/home/marco/Documentos/2018.2-EDA/projetos/02/asphalt/asphalt_%d.txt",random);

	printf("Arquivo: %s\n", asphalt);

	fp = fopen(asphalt ,"r");

	if(fp==NULL){
		printf("Falha.\n");
		exit(1);
	}

	return fp;
}

bool Existe(int valores[], int tam, int valor)
{
  for(int i=0; i<tam; i++){
    if(valores[i]==valor)
      return true;
  }

  return false;
}

void GeraAleatorios(int aleatorios[], int quantNumeros, int Limite)
{
  srand(time(NULL));

  int v;
  for(int i=0; i<quantNumeros; i++){
    v = rand() % Limite;
    while (Existe(aleatorios, i, v)) {
      v = rand() % Limite;
    }
    aleatorios[i] = v;
  }

}
