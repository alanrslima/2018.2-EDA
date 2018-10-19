#include <stdio.h>
#include <stdlib.h>

struct contato {
    char nome[101];
    char celular[11];
    char endereco[101];
    unsigned int cep;
    char data_nascimento[11];
    struct contato *prox;
    struct contato *ant;
}

typedef struct contato Contato;

int main(int argc, char const *argv[]) {

  return 0;
}
