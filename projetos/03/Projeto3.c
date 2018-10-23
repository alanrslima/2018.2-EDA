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

/* Seta uma lista com NULL */
Lista *criaListaVazia();
/* Abre um arquivo contatos.txt na pasta resources, caso não exista ele é criado. O arquivo 
é lido e os contatos são salvas numa lista */ 
Lista *abreArquivo();
/* Aloca dinamicamente um contato */
Lista *alocaContato();
/* Insere um contato no inicio da lista */
Lista *insereInicioLista(Lista *lista, Lista *contato);
/* Cria um novo contato e o insere na lista */
Lista *novoContato(Lista *lista);
/* Remove um contato com base em um nome dado pelo usuario */
Lista *removeContato(Lista *lista);
/* Ordena a lista de contatos usando insertion sort */
Lista *ordenaContatos(Lista *lista);

/* Imprimi um ou mais contatos com base em um nome dado pelo usuario */
void imprimirContato(Lista *lista);
/* Imprimi todos os contatos da lista */
void imprimirContatos(Lista *lista);

/* Cria o menu de navegação */
void criaMenu();
/* Acessa o menu de navegação */
void acessaMenu(Lista *lista);

/* Valida o nome e o endereço do contato para que não passem de 100 caracteres */
void validaNomeEndereco(char *nome_endereco);
/* Valida o número de celular para o formato (xxxxx-xxxx) */
void validaCelular(char *celular);
/* Valida da data de nascimento no formato (dd/mm/yyyy) */
void validaDataNascimento(char *data);

/* Libera da memoria a lista de contatos */
void liberaListaContatos(Lista *lista);
/* Transforma em maiusculo uma string */
void stringCapsLock(char *str);

/* Escreve em um arquivo contatos.txt todos os contatos presentes na lista */
void escreveArquivo(Lista *lista);

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
    lista = ordenaContatos(lista);
  }
	fclose(arq);
  return lista;
}

void escreveArquivo(Lista *lista) {
  FILE *arq;
  arq = fopen("resources/contatos.txt", "w");
  if (arq == NULL) {
    printf("Falha ao abrir arquivo! \n");
    exit(1);
  }

  while (lista != NULL) {
    fprintf(arq, "%s\n", lista->Contato.nome);
    fprintf(arq, "%s\n", lista->Contato.celular);
    fprintf(arq, "%s\n", lista->Contato.endereco);
    fprintf(arq, "%d\n", lista->Contato.cep);
    fprintf(arq, "%s\n$\n", lista->Contato.dataNascimento);
    lista = lista->proximo;
  }
  fclose(arq);
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

	Lista *index = lista;
  if (index == NULL) {
    printf("\n\nNÃO HÁ NENHUM CONTATO NA LISTA!\n");
  }else{
	  char nomeParam[101];
	  printf("\n----------------------------------------------------------\n");
	  printf("	Listagem de contato(s)");
	  printf("\n----------------------------------------------------------\n");
	  printf("Digite o nome: ");
	  validaNomeEndereco(nomeParam);
	  stringCapsLock(nomeParam);
  	int existe = 0;
  	while (index != NULL) {
	  	char temp[101];
	    strcpy(temp, index->Contato.nome);
	    stringCapsLock(temp);
	    if (strstr(temp, nomeParam) != NULL) {
	    	existe = 1;
	    	printf("\n-------------------------------------------------------\n");
	    	printf("Nome: %s\n", index->Contato.nome);
	      printf("Telefone: %s\n", index->Contato.celular);
	      printf("Endereço: %s\n", index->Contato.endereco);
	      printf("CEP: %d\n", index->Contato.cep);
	      printf("Data de nascimento: %s\n", index->Contato.dataNascimento);
	      printf("-------------------------------------------------------\n");
	      index = index->proximo;
	    } else {
	      index = index->proximo;
	    }
  	}
  	if (!existe){
  		printf("\nNÃO EXISTE NENHUM CONTATO COM ESTE NOME\n");
  	}
  }
}

void imprimirContatos(Lista *lista) {

  Lista *index = lista;
  if (index == NULL) {
    printf("\n\nNÃO HÁ NENHUM CONTATO NA LISTA!\n");
  }else{
  	printf("\n  ** CONTATOS: **\n");
	  while (index != NULL) {
	  	printf("\n-------------------------------------------------------\n");
	    printf("Nome: %s\n", index->Contato.nome);
	    printf("Telefone: %s\n", index->Contato.celular);
	    printf("Endereço: %s\n", index->Contato.endereco);
	    printf("CEP: %d\n", index->Contato.cep);
	    printf("Data de nascimento: %s\n", index->Contato.dataNascimento);
	    printf("---------------------------------------------------------\n");
	    index = index->proximo;
	  }
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
      	escreveArquivo(lista);
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
  lista = ordenaContatos(lista);
  return lista;
}

void stringCapsLock(char *str){
	int tamanho = strlen(str);

  for (int i=0; i < tamanho; i++){
    str[i] = toupper(str[i]);
  }
}

Lista *removeContato(Lista *lista) {

	Lista *index = lista;
	if (index == NULL) {
  	printf("\n\nNÃO HÁ NENHUM CONTATO NA LISTA!\n");
  }else{
  	char nomeParam[101];
	  printf("\n----------------------------------------------------------\n");
	  printf("	Exclusão de contato");
	  printf("\n----------------------------------------------------------\n");
	  printf("Digite o nome: ");
	  validaNomeEndereco(nomeParam);
	  stringCapsLock(nomeParam);
	  int existe = 0;
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
	      existe = 1;
	      listaAux = index;
	      index = index->proximo;
	      free(listaAux);
	      printf("%s Removido(a) com sucesso! \n", temp);
	    } else {
	      index = index->proximo;
	    }
	  }
	  if (!existe){
  		printf("\nNÃO EXISTE NENHUM CONTATO COM ESTE NOME\n");	  	
	  }
  }
  return lista;
}

Lista *ordenaContatos(Lista *lista) {
  if(lista == NULL || (lista->proximo == NULL && lista->anterior == NULL)) {
    return lista;
  }
  Lista * cabecario = NULL;
  while(lista != NULL) {
    Lista *indexAtual = lista;
    lista = lista->proximo;
    if(cabecario == NULL || strcmp(indexAtual->Contato.nome, cabecario->Contato.nome) <= 0) {
      indexAtual->anterior = NULL;
      indexAtual->proximo = cabecario;
      if(cabecario != NULL) {
        cabecario->anterior = indexAtual;
      }
      cabecario = indexAtual;
    } else {
      Lista *temp = cabecario;
      while(temp != NULL) {
        if(temp->proximo == NULL || strcmp(indexAtual->Contato.nome, temp->proximo->Contato.nome) <= 0) {
          indexAtual->proximo = temp->proximo;
          if(temp->proximo != NULL) {
            temp->proximo->anterior = indexAtual;
          }
          indexAtual->anterior = temp;
          temp->proximo = indexAtual;
          break; 
        }
        temp = temp->proximo;
      }
    }
  }
  return cabecario;
}



