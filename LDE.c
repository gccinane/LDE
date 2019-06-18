// Aluno : José Gabriel

/*
 Sintese
   Objetivo: lde
 
   Entrada : 

   Saida   :  

*/

#include <stdio.h>
#include <conio.c>
#include <string.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

typedef struct{
	int reg;
	float valor;
	char nome[50];
}Produto;

typedef struct tNo{
	Produto dado;
	struct tNo *prox;
	struct tNo *ant;
}No;

typedef struct{
	No *primeiro;
	int qtd;
	No *ultimo;
}Descritor;




char leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas);
void inicializarLista(Descritor *lista);
void menu(char *opcao);
void limpaTela();
No* alocaNo();
void entradaProduto(No *novo);
void insereNo(Descritor *lista, No *novo);
void insereListaVazia(Descritor **lista, No *novo);
void insereListaUltimo(Descritor **lista, No *novo);
void insereListaInicio(Descritor **lista, No *novo);
void insereListaMeio(Descritor **lista, No *novo);
void listar(Descritor *lista);
void apresentaNo(No *aux);
void destruirLista(Descritor *lista);
void alterar(Descritor *lista);
No* buscar(Descritor *lista, int reg);
void consultar(Descritor *lista);
void excluir(Descritor *lista);
void gravar(Descritor *lista);
void recuperar(Descritor *lista);

int main(void)
{
// Declaracoes
	Descritor lista;
	No *novo;
	char opcao;

// Instrucoes
	setlocale(LC_ALL, "Portuguese");
	inicializarLista(&lista);
	do{
		printf("-----MENU-----\n\n");
		opcao = leValidaOpcao("1.Inserir\n2.Listar\n3.Alterar\n4.Excluir\n5.Consultar\n6.Gravar\n7.Restaurar\n0.Sair", "Tecla invalida!", "01234567");
		
		switch(opcao){
			case '1':
				novo = alocaNo();
				entradaProduto(novo);
				insereNo(&lista, novo);
				break;
				
			case '2':
				listar(&lista);
			
				break;
				
			case '3':
				alterar(&lista);
				break;
				
			case '4':
				excluir(&lista);
				break;
				
			case '5':
				consultar(&lista);
				break;
				
			case '6':
				gravar(&lista);
				break;
				
			case '7':
				recuperar(&lista);
				break;
			
			case '0':
				
				break;																			
		}
	}while(strchr("1234567", opcao));
	destruirLista(&lista);
  getch();
  return 0;
}

void excluir(Descritor *lista){
	No *noExclusao;
	No *aux = lista->primeiro->prox;
	int reg;
	char opcao;
	
	printf("-----EXCLUSÃO-----\n\n");
		if(lista->qtd == 0){
			limpaTela();
			printf("\nLista Vazia! ");
		}else{
			printf("Digite o registro do produto a ser excluído: ");
			scanf("%d", &reg);
			noExclusao = buscar(lista, reg);
			limpaTela();
			if(noExclusao != NULL){
				printf("Produto encontrado!\n\n");
				apresentaNo(noExclusao);
				opcao = leValidaOpcao("\nDeseja realmente excluir este produto?(S/N)", "Tecla invalida", "SN");
				if(opcao == 'S'){
					
					if(lista->qtd == 1){
						lista->primeiro = lista->primeiro->prox;//unico  ou inicializar a lista
					}else{
						if(lista->primeiro == noExclusao){//primeiro
							lista->primeiro->ant = NULL;
							lista->primeiro = lista->primeiro->prox;
							
						}else{
							
							if(lista->ultimo == noExclusao){//ultimo
								lista->ultimo = lista->ultimo->ant;
								lista->ultimo->prox = NULL;
							}else{
								
								while(aux != noExclusao){
									aux = aux->prox;
								}
								// não é necessário utilizar o aux, só substituir o aux das linhas abaixo pelo noexclusao, mas iss eh trampo pra vc jose do futuro ;)))))))
								(aux->prox)->ant = aux->ant;//meio
								(aux->ant)->prox = aux->prox; 
							} 
						}
					}
					lista->qtd--;
					free(noExclusao);	
				}
				
				
			
			}else{
				printf("Produto não encontrado! ");
			}
		}

	
	
	
}

void gravar(Descritor *lista){
	No *aux = lista->primeiro;
	FILE *arq;
	
	if(arq = fopen("pilha.txt", "ab")){
		while(aux != NULL){
			fwrite(aux, sizeof(No), 1, arq);
			aux = aux->prox;
		}
		
		printf("\nLista gravada com sucesso!");
		limpaTela();
	}else{
		printf("Falha ao abrir arquivo!");
	}
	
}

void recuperar(Descritor *lista){

			FILE *arq;
	No *aux = alocaNo();
	int i;
	int cont = 0;

			if(arq = fopen("pilha.txt", "rb")){
			fseek(arq, 0, SEEK_END);
			i = ftell(arq);
			i = i/sizeof(No);
			rewind(arq);
			printf("%d", i);
			
			while(cont < i){
				fread(aux, sizeof(No), 1, arq);
				fflush(stdin);
				insereNo(lista, aux);
				aux = aux->prox;
				aux = (No*) realloc(aux, sizeof(No));
				cont++;
			
			}
			
			
		}
	
}

void consultar(Descritor *lista){
	int regBusca;
	No *noBusca;
	printf("-----CONSULTA-----\n\n");
		printf("Digite o registro do produto a ser consultado: ");
		scanf("%d", &regBusca);
		limpaTela();
		noBusca = buscar(lista, regBusca);
		apresentaNo(noBusca);
		limpaTela();
}

void apresentaNo(No *aux){
	printf("Nome: %s\nValor: %f\nRegistro: %d\n\n", aux->dado.nome, aux->dado.valor, aux->dado.reg);
}


void alterar(Descritor *lista){
	No *novo;
	int reg;
	char opcao;
	printf("-----ALTERACAO-----\n\n");
	printf("Digite o registro do produto a ser alterado: ");
	scanf("%d", &reg);
	novo = buscar(lista, reg);
	limpaTela();
	if(novo != NULL){
		printf("Produto encontrado!\n\n");
		apresentaNo(novo);
		opcao = leValidaOpcao("Deseja realmente alterar este produto?(S/N)", "Tecla invalida", "SN");
		if(opcao == 'S'){
			entradaProduto(novo);
		}
		
	}else{
		printf("Produto não encontrado! ");
	}
	
		
}

No* buscar(Descritor *lista, int reg){
	No *aux = (*lista).primeiro;

	while(aux != NULL){
		if(aux->dado.reg == reg){
			return aux;
		}
		aux = aux->prox;
	}
	
	return NULL;
}


void listar(Descritor *lista){
	No *aux = (*lista).primeiro;
	
	
	if((*lista).primeiro != NULL){	
		while(aux != NULL){
			apresentaNo(aux);
			aux = aux->prox;
		}
	}else{
		printf("Lista vazia!");
	}
	
	limpaTela();
}

void destruirLista(Descritor *lista){
	No *aux = (*lista).primeiro;
	No *p;
	
	while(aux != NULL){
		p = aux;
		aux = aux->prox;
		free(p);
	}
	inicializarLista(lista);
}

void insereNo(Descritor *lista, No *novo){
	if((*lista).qtd == 0){
		insereListaVazia(&lista, novo);
	
	}else{
	
		if(((*lista).ultimo->dado.reg) < novo->dado.reg){
	
			insereListaUltimo(&lista, novo);
			
			
		}else{
			
			if((*lista).primeiro->dado.reg > novo->dado.reg){
		
				insereListaInicio(&lista, novo);
			
				
			}else{
			
				insereListaMeio(&lista, novo);
				
			}
		}
	}
	
	lista->qtd++;

}


void insereListaMeio(Descritor **lista, No *novo){
	No *aux = (*lista)->primeiro;
	while(aux->dado.reg < novo->dado.reg){
		aux = aux->prox;	
	}
	if(aux->dado.reg = novo->dado.reg){
		novo = NULL;

	}
	(aux->ant)->prox = novo;
	aux->ant = novo;
	novo->prox = aux;
	novo->ant = aux->ant;
	
 
}

void insereListaInicio(Descritor **lista, No *novo){
	novo->prox = (*lista)->primeiro;
	novo->ant = NULL;
	(*lista)->primeiro->ant = novo;
	(*lista)->primeiro = novo;
}

void insereListaUltimo(Descritor **lista, No *novo){
	novo->prox = NULL;
	novo->ant = (*lista)->ultimo;
	(*lista)->ultimo->prox = novo;
	(*lista)->ultimo = novo;
	

}
void insereListaVazia(Descritor **lista, No *novo){
	(*lista)->primeiro = novo;
	(*lista)->ultimo = novo;
	(*lista)->primeiro->prox = NULL;
	(*lista)->primeiro->ant = NULL;
	
}

void entradaProduto(No *novo){
	printf("-----PRODUTO-----\n\n");
	printf("Registro: ");
	scanf("%d", &(novo->dado.reg));
	printf("\nValor: ");
	scanf("%f", &(novo->dado.valor));
	printf("\nNome: ");
	fflush(stdin);
	gets(novo->dado.nome);
	limpaTela();
}

No* alocaNo(){
	return (No*) malloc(sizeof(No));
}

void limpaTela(){
	getch();
	system("cls");
}

char leValidaOpcao(char *msn, char *msnErro, char *opcoesValidas)
{
	char opcao;
    do
	{
		printf(msn);
		fflush(stdin);
	    opcao = toupper(getch());
		fflush(stdin);
		system("cls");

		if(strchr(opcoesValidas,opcao)==NULL)
		{
			printf(msnErro);
			getch();
			system("cls");
		}
		
	}while(strchr(opcoesValidas,opcao)==NULL);    
	return opcao;
}

//inicializar a lista
void inicializarLista(Descritor *lista){
	(*lista).primeiro = (*lista).ultimo = NULL;
	(*lista).qtd = 0;
}
