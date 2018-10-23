#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct CONTATO {
  char nome[101];
  char celular[11];
  char endereco[101];
  unsigned int cep;
  char dataNascimento[11];
};

struct LISTA
{
	struct CONTATO Contato;
	struct LISTA* anterior;
	struct LISTA* proximo;
};

typedef struct LISTA Lista;

Lista *criaListaVazia();
Lista *abreArquivo();
Lista *alocaContato();
Lista *insereInicioLista(Lista *lista, Lista *contato);
Lista *novoContato(Lista *lista);
Lista *removeContato(Lista *lista);

void imprimirContato(Lista *lista);
void imprimirContatos(Lista *lista);
void criaMenu();
void acessaMenu(Lista *lista);

void validaNomeEndereco(char *nome_endereco);
void validaCelular(char *celular);
void validaDataNascimento(char *data);

void liberaListaContatos(Lista *lista);
void stringCapsLock(char *str);

int main(int argc, char const *argv[]) {

  Lista *listaContatos;

  listaContatos = criaListaVazia();
  listaContatos = abreArquivo(listaContatos);
  criaMenu();
  acessaMenu(listaContatos);

  return 0;
}

Lista *criaListaVazia(){
 	return NULL;
}

Lista *abreArquivo(){
  FILE *arq;
  char ch;

  Lista *lista = criaListaVazia();

  arq = fopen("resources/contatos.txt", "r");
  if (arq == NULL){
     arq = fopen("resources/contatos.txt", "w");
  }

  while (ch != EOF){

    Lista *contato = alocaContato();

    fscanf(arq, " %[^\n]", contato->Contato.nome);
    fscanf(arq, " %[^\n]", contato->Contato.celular);
    fscanf(arq, " %[^\n]", contato->Contato.endereco);
    fscanf(arq, " %ud", &contato->Contato.cep);
    fscanf(arq, " %[^\n]", contato->Contato.dataNascimento);
    contato->proximo = NULL;
    contato->anterior = NULL;

    ch = fgetc(arq);
    ch = fgetc(arq);

    if (ch == EOF){
      break;
    }
    lista = insereInicioLista(lista, contato);
    // listaContatos = ordena_lista(listaContatos);
  }
	fclose(arq);
  return lista;
}

Lista *alocaContato(){
	Lista *contato;
	contato = (Lista *)malloc(sizeof(Lista));
	if (contato==NULL){
		printf("Falha ao alocar contato\n" );
    exit(-1);
	}
	return contato;
}

void imprimirContato(Lista *lista) {

  char nomeParam[101];
  printf("\n----------------------------------------------------------\n");
  printf("	Listagem de contato(s)");
  printf("\n----------------------------------------------------------\n");
  printf("Digite o nome: ");
  validaNomeEndereco(nomeParam);
  stringCapsLock(nomeParam);

  Lista *index = lista;
  if (index == NULL) {
    printf("Não há nenhum contato na lista!\n");
  }

  while (index != NULL) {
  	char temp[101];
    strcpy(temp, index->Contato.nome);
    stringCapsLock(temp);
    if (strstr(temp, nomeParam) != NULL) {
    	printf("\nNome: %s\n", index->Contato.nome);
      printf("Telefone: %s\n", index->Contato.celular);
      printf("Endereço: %s\n", index->Contato.endereco);
      printf("CEP: %d\n", index->Contato.cep);
      printf("Aniversário: %s\n", index->Contato.dataNascimento);
      index = index->proximo;
    } else {
      index = index->proximo;
    }
  }
}

void imprimirContatos(Lista *lista) {

  Lista *index = lista;
  if (index == NULL) {
    printf("Lista de contatos vazia!\n");
  }

  printf("\n Lista de contatos: \n");
  while (index != NULL) {
    printf("\nNome: %s\n", index->Contato.nome);
    printf("Telefone: %s\n", index->Contato.celular);
    printf("Endereço: %s\n", index->Contato.endereco);
    printf("CEP: %d\n", index->Contato.cep);
    printf("Aniversário: %s\n", index->Contato.dataNascimento);
    index = index->proximo;
  }
}

Lista *insereInicioLista(Lista *lista, Lista *contato) {
  if (lista != NULL) {
    contato->proximo = lista;
    lista->anterior = contato;
  }
  return contato;
}

void criaMenu(){
  printf("\n\n\n----------------------------------------------------------\n");
  printf(">>>>>>>>>>>>>>>>>>> LISTA DE CONTATOS <<<<<<<<<<<<<<<<<<<<\n");
  printf("----------------------------------------------------------\n\n");
  printf("\t Menu de opções, selecione a desejeda: \n\n");
  printf("  (1) Inserir novo contato \n");
  printf("  (2) Remover contatos com base no nome \n");
  printf("  (3) Visualizar contato com base no nome \n");
  printf("  (4) Visualizar todos os contatos em ordem alfabetica \n");
  printf("  (5) Sair \n\n");
  printf("----------------------------------------------------------\n");
  printf("Digite aqui: ");
}

void acessaMenu(Lista *lista){
  char itemSelecionado = '0';

  while (itemSelecionado != '5'){
  	scanf(" %c", &itemSelecionado);
    switch (itemSelecionado) {
      case '1':
        lista = novoContato(lista);
        criaMenu();
        break;
      case '2':
      	lista = removeContato(lista);
        criaMenu();
        break;
      case '3':
      	imprimirContato(lista);
        criaMenu();
        break;
      case '4':
        imprimirContatos(lista);
        criaMenu();
        break;
      case '5':
        printf("\n\nSair do programa \n (Escrever arquivo e limpar lista da memoria)\n\n");
        liberaListaContatos(lista);
        break;
      default:
        printf("\nEntrada inválida! Digite novamente: ");
    }
  }
}

void validaNomeEndereco(char *nome_endereco){
	scanf(" %[^\n]", nome_endereco);
	while (strlen(nome_endereco) > 100){
		printf("\nInválido! Deve possuir menor de 100 caracteres: ");
		scanf(" %[^\n]", nome_endereco);
	}
}

void validaCelular(char *celular){
	scanf(" %[^\n]", celular);
	while (strlen(celular) > 10 || !isdigit(celular[0]) || !isdigit(celular[1]) || !isdigit(celular[2]) || !isdigit(celular[3]) || !isdigit(celular[4]) || celular[5] != '-' || !isdigit(celular[6]) || !isdigit(celular[7]) || !isdigit(celular[8]) || !isdigit(celular[9])) {
    printf("\nNúmero de celular inválido! Digite novamente (xxxxx-xxxx): ");
    scanf(" %[^\n]", celular);
  }
}

void validaDataNascimento(char *data){
	scanf(" %[^\n]", data);
	while (strlen(data) > 10 || !isdigit(data[0]) || !isdigit(data[1]) || data[2] != '/' || !isdigit(data[3]) || !isdigit(data[4]) || data[5] != '/' || !isdigit(data[6]) || !isdigit(data[7]) || !isdigit(data[8]) || !isdigit(data[9])) {
    printf("\nData inválida! Digite novamente (dd/mm/yyyy): ");
    scanf(" %[^\n]", data);
  }	
}

void liberaListaContatos(Lista *lista) {
	Lista *index;
	for (index = lista; index != NULL; index = index->proximo){
		free(index);
	}
}


Lista *novoContato(Lista *lista) {
  Lista *contato = alocaContato();
  printf("\n-----------------------------------------------\n");
  printf("	Inserção de novo contato");
  printf("\n-----------------------------------------------\n");
  printf("\nNome: ");
  validaNomeEndereco(contato->Contato.nome);
  printf("\nCelular (xxxxx-xxxx): ");
  validaCelular(contato->Contato.celular);
  printf("\nEndereco: ");
  validaNomeEndereco(contato->Contato.endereco);
  printf("\nCEP: ");
  scanf(" %ud", &contato->Contato.cep);
  printf("\nData de nascimento (dd/mm/yyyy): ");
  validaDataNascimento(contato->Contato.dataNascimento);

  printf("%s\n", contato->Contato.nome);
  printf("%s\n", contato->Contato.celular);
  printf("%s\n", contato->Contato.endereco);
  printf("%d\n", contato->Contato.cep);
  printf("%s\n", contato->Contato.dataNascimento);

  lista = insereInicioLista(lista, contato);
  // listaContatos = ordena_lista(listaContatos);
  return lista;
}

void stringCapsLock(char *str){
	int tamanho = strlen(str);

  for (int i=0; i < tamanho; i++){
    str[i] = toupper(str[i]);
  }
}

Lista *removeContato(Lista *lista) {

  char nomeParam[101];
  printf("\n----------------------------------------------------------\n");
  printf("	Exclusão de contato");
  printf("\n----------------------------------------------------------\n");
  printf("Digite o nome: ");
  validaNomeEndereco(nomeParam);
  stringCapsLock(nomeParam);

  Lista *index = lista;

  if (index == NULL) {
  	printf("Não há nenhum contato na lista!\n");
  }

  while (index != NULL) {
  	char temp[101];
    strcpy(temp, index->Contato.nome);
    stringCapsLock(temp);
    if (strstr(temp, nomeParam) != NULL) {
    	Lista *listaAux;
    	if(index->proximo != NULL) {
        index->proximo->anterior = index->anterior;
      }
      if(index->anterior != NULL) {
        index->anterior->proximo = index->proximo;
      }
      if (index->anterior == NULL) {
        lista = index->proximo;
      }
      listaAux = index;
      index = index->proximo;
      free(listaAux);
      printf("%s Removido(a) com sucesso! \n", temp);
    } else {
      index = index->proximo;
    }
  }
  return lista;
}


