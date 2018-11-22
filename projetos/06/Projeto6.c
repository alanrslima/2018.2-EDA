#include <stdio.h>
#include <stdlib.h>

int get_parametro_linha_comando(int argc, char *argv[], int *param);

int main(int argc, char *argv[]) {
  int param;

  if (get_parametro_linha_comando(argc, argv, &param)){
    printf("Parametro de entrada = %d\n", param );
  }
  return 0;
}

int get_parametro_linha_comando(int argc, char *argv[], int *param){
  if (argc == 1){
    printf("Programa %s sem parametros\n", argv[0] );
    return 0;
  }else{
    *param = atoi(argv[1]);
    return 1;
  }
}
