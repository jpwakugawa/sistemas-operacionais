/*******************************************************************************/
/*
	Implementar paginação por demanda utilizando o algoritmo de substituição de páginas FIFO.

	As seguintes estruturas e funções estão disponíveis para uso:

		1 - Descobrir se a página j do processo i é válida: tabelas_de_pagina[i][j].valido;
		2 - Descobrir em qual quadro a página j do processo i está: tabelas_de_pagina[i][j].quadro;
		3 - Inserir um número inteiro na fila: insere_na_fila(número);
		4 - Remover o elemento que entrou primeiro na fila: int elemento = remove_da_fila();
		5 - Descobrir o valor p de um endereço lógico: descobre_p(tamanho de p, tamanho de q, endereço lógico);
		6 - Descobrir o valor q de um endereço lógico: descobre_q(tamanho de p, tamanho de q, endereço lógico);
*/
/*******************************************************************************/

#include <stdio.h>
#include <math.h>
#include <queue>

typedef struct {
	bool valido;
	int quadro;
	bool referencia;
	bool modificado;
} Linha_da_tabela_de_pagina;

std::queue<int> fila;

/**********************************/
/* Funções de manipulação da fila */
/**********************************/
void insere_na_fila(int elemento);
int remove_da_fila();
void remove_da_fila(int elemento);

/**********************************/
/* Funções referentes à paginação */
/**********************************/
unsigned int descobre_p(unsigned int tamanho_p, unsigned int tamanho_d, unsigned int endereco_logico);
unsigned int descobre_q(unsigned int tamanho_p, unsigned int tamanho_d, unsigned int endereco_logico);
void inicializa_quadros_livres(bool* quadros_livres, int quantidade_de_quadros);
void imprime_falha_de_pagina(int numero_do_processo, int endereco_logico);
void imprime_sem_falha_de_pagina(int numero_do_processo, int endereco_logico);
void imprime_falha_na_remocao(int numero_do_processo, int endereco_logico);
void imprime_sucesso_na_remocao(int numero_do_processo, int endereco_logico);
void inicializa_tabelas_de_pagina(Linha_da_tabela_de_pagina** tabelas_de_pagina, int quantidade_de_processos, int quantidade_de_paginas_por_processo);
void imprime_estatisticas_de_falhas_de_pagina(int numero_de_acessos_a_memoria, int quantidade_de_falhas_de_pagina);
void imprimir_tabelas_de_pagina(Linha_da_tabela_de_pagina** tabelas_de_pagina, int quantidade_de_processos, int quantidade_de_paginas_por_processo);

int main() {
	// Parâmetros do programa
	const int tamanho_endereco_logico = 5;
	const int tamanho_p = 3; // bits
	const int tamanho_d = 2;	//bits
 	const int quantidade_de_processos = 3;
	const int quantidade_de_quadros = 4;

	int quantidade_de_paginas_por_processo = pow(2,tamanho_p);
	int tamda_pagina = pow(2, tamanho_d);

	bool* quadros_livres = new bool[quantidade_de_quadros];
	inicializa_quadros_livres(quadros_livres, quantidade_de_quadros);

	Linha_da_tabela_de_pagina** tabelas_de_pagina = new Linha_da_tabela_de_pagina*[quantidade_de_processos];
	inicializa_tabelas_de_pagina(tabelas_de_pagina, quantidade_de_processos, quantidade_de_paginas_por_processo);

	/*Serão lidos do teclado*/
	unsigned int numeroprocesso, el;

	int n_acessos = 0;
	int n_falhas = 0;

	int opcao;
	do {

		printf("Escolha uma das opções abaixo:\n");
		printf("(1) Acessar um endereço lógico de processo\n");
		printf("(2) Remover da memória uma página de um processo\n");
		printf("(3) Imprimir tabelas de página\n");
		printf("(4) Imprimir estatísticas de falhas de página\n");
		printf("(0) Sair do programa\n");

		scanf("%d", &opcao);

		switch(opcao){

			/*************/
			/*Implementar*/
			/*************/
			case 1:
			{
				printf("Digite o número do processo\n");
				scanf("%d", &numeroprocesso);

				printf("Digite o endereco lógico que deseja acessar do processo %d\n", numeroprocesso);
				scanf("%d", &el);


				/**********************/
				/*Início do seu código*/
				/**********************/

				bool falha_de_pagina = false;
				int pagina = descobre_p(tamanho_p, tamanho_d, el);
				int quadro_livre = -1;
				n_acessos++;

				if(!tabelas_de_pagina[numeroprocesso][pagina].valido) {
					falha_de_pagina = true;
					n_falhas++;
					for(int i = 0 ; i < quantidade_de_quadros ; i++) {
						if(quadros_livres[i] == true) {
							quadro_livre = i;
							break;
						}
					}
				}

				/* Achei um quadro livre */
				if(quadro_livre != -1) {
					tabelas_de_pagina[numeroprocesso][pagina].valido = true;
					tabelas_de_pagina[numeroprocesso][pagina].referencia = true;
					tabelas_de_pagina[numeroprocesso][pagina].quadro = quadro_livre;
          insere_na_fila(quadro_livre);
					quadros_livres[quadro_livre] = false;
				}
				/* Não achei um quadro livre, preciso substituir
				alguém */
				else {
					bool acheiLivre = false;
					int livre = 0;

					while(!acheiLivre) {
						livre = remove_da_fila();
						for(int proc=0; proc<quantidade_de_processos && !acheiLivre; proc++) {
							for(int pAlvo=0; pAlvo<quantidade_de_paginas_por_processo && !acheiLivre; pAlvo++) {
								if(tabelas_de_pagina[proc][pAlvo].referencia) {
									tabelas_de_pagina[proc][pAlvo].referencia = false;
								}
								else {
									tabelas_de_pagina[proc][pAlvo].valido = false;

									tabelas_de_pagina[proc][pagina].valido = true;
									tabelas_de_pagina[proc][pagina].referencia = true;
									tabelas_de_pagina[proc][pagina].quadro = livre;

									acheiLivre = true;
								}
								insere_na_fila(livre);
								quadros_livres[livre] = false;
							}
						}
					}
				}




				/*******************/
				/*Fim do seu código*/
				/*******************/

				if(falha_de_pagina)
					imprime_falha_de_pagina(el, numeroprocesso);
				else
					imprime_sem_falha_de_pagina(el, numeroprocesso);

				break;
			}
			/*************/
			/*Implementar*/
			/*************/
			case 2:
				printf("Digite o número do processo\n");
				scanf("%d", &numeroprocesso);

				printf("Digite o endereco lógico que deseja acessar do processo %d\n", numeroprocesso);
				scanf("%d", &el);


				/**********************/
				/*Início do seu código*/
				/**********************/

				bool removido_com_sucesso;

				/*Seu código*/
				try {
					int pagina_retirada = descobre_p(tamanho_p, tamanho_d, el);
					int quadro_retirado = tabelas_de_pagina[numeroprocesso][pagina_retirada].quadro;

					tabelas_de_pagina[numeroprocesso][pagina_retirada].valido = false;
					tabelas_de_pagina[numeroprocesso][pagina_retirada].referencia = false;
					remove_da_fila(quadro_retirado);
					quadros_livres[quadro_retirado] = true;

					removido_com_sucesso = true;
				}
				catch (...) {
					removido_com_sucesso = false;
				}


				/*******************/
				/*Fim do seu código*/
				/*******************/


				if(!removido_com_sucesso)
					imprime_falha_na_remocao(numeroprocesso, el);
				else
					imprime_sucesso_na_remocao(numeroprocesso, el);

				break;

			/*******/
			/*Feito*/
			/*******/
			case 3:
				imprimir_tabelas_de_pagina(tabelas_de_pagina, quantidade_de_processos, quantidade_de_paginas_por_processo);

				break;

			/*************/
			/*Implementar*/
			/*************/
			case 4:
				/**********************/
				/*Início do seu código*/
				/**********************/

				/*
				* APENAS alterar parâmetros da função abaixo:
				* 		Primeiro parâmetro: quantidade total de acessos à memória
				*		  Segunda parâmetro: quantidade de falhas de página
				*/
				imprime_estatisticas_de_falhas_de_pagina(n_acessos,n_falhas);

				/*******************/
				/*Fim do seu código*/
				/*******************/

				break;

			/*******/
			/*Feito*/
			/*******/
			case 0:
				printf("Saindo...\n");
				break;

			default:
				printf("Opcao inválida!\n");
				break;
		}

	} while(opcao != 0);

	/*Liberando memória*/
	for(int i = 0 ; i < 3 ; i++) {
		delete tabelas_de_pagina[i];
	}
	delete tabelas_de_pagina;
	delete quadros_livres;

	return 0;
}

/**********************************/
/* Funções de manipulação da fila */
/**********************************/
void insere_na_fila(int valor) {
	fila.push(valor);
}

int remove_da_fila() {
	int valor = -1;
	if(!fila.empty()) {
		valor = fila.front();
		fila.pop();
	}
	return valor;
}

void remove_da_fila(int elemento) {
	if(!fila.empty()) {
		if(elemento == fila.front()) {
			fila.pop();
		}
		else {
			int primeiro = remove_da_fila();
			insere_na_fila(primeiro);
			while(fila.front() != primeiro) {
				if(fila.front() == elemento) {
					fila.pop();
				}
				else {
					insere_na_fila(remove_da_fila());
				}
			}
		}
	}
}

/**********************************/
/* Funções referentes à paginação */
/**********************************/
unsigned int descobre_p(unsigned int tamanho_p, unsigned int tamanho_d, unsigned int endereco_logico) {
	endereco_logico = endereco_logico >> tamanho_d;
	unsigned int operando = (pow(2,tamanho_p) - 1);
	return endereco_logico & operando;
}

unsigned int descobre_q(unsigned int tamanho_p, unsigned int tamanho_d, unsigned int endereco_logico) {
	unsigned int operando = (pow(2,tamanho_d) - 1);
	return endereco_logico & operando;
}

void inicializa_quadros_livres(bool* quadros_livres, int quantidade_de_quadros) {
	for(int i = 0 ; i < quantidade_de_quadros ; i++)
		quadros_livres[i] = true;
}

void imprime_falha_de_pagina(int numero_do_processo, int endereco_logico) {
	printf("*******************************************\n");
	printf("HOUVE falha acessando endereço lógico %d do processo %d \n", numero_do_processo, endereco_logico);
	printf("*******************************************\n");
}

void imprime_sem_falha_de_pagina(int numero_do_processo, int endereco_logico) {
	printf("*******************************************\n");
	printf("NÃO HOUVE falha de página acessando endereço lógico %d do processo %d\n", numero_do_processo, endereco_logico);
	printf("*******************************************\n");
}

void imprime_falha_na_remocao(int numero_do_processo, int endereco_logico) {
	printf("*******************************************\n");
	printf("A página %d do processo %d não \n", numero_do_processo, endereco_logico);
	printf("*******************************************\n");
}

void imprime_sucesso_na_remocao(int numero_do_processo, int endereco_logico) {
	printf("*******************************************\n");
	printf("Página trazida com sucesso: processo %d acessando endereço lógico %d\n", numero_do_processo, endereco_logico);
	printf("*******************************************\n");
}

void inicializa_tabelas_de_pagina(Linha_da_tabela_de_pagina** tabelas_de_pagina, int quantidade_de_processos, int quantidade_de_paginas_por_processo) {

	/* Inicializa todas as linhas da tabela de página com o bit de válido em false*/
	for( int i = 0 ; i < quantidade_de_processos ; i++) {
		tabelas_de_pagina[i] = new Linha_da_tabela_de_pagina[quantidade_de_paginas_por_processo];
		for(int j = 0 ; j < quantidade_de_paginas_por_processo ; j++) {
			tabelas_de_pagina[i][j].valido = false;
		}
	}
}

void imprime_estatisticas_de_falhas_de_pagina(int numero_de_acessos_a_memoria, int quantidade_de_falhas_de_pagina) {
	printf("*******************************************\n");
	printf("Sua taxa de falha de página é: %.1f por cento\n", (((float)quantidade_de_falhas_de_pagina)/numero_de_acessos_a_memoria)*100);
	printf("*******************************************\n");
}

void imprimir_tabelas_de_pagina(Linha_da_tabela_de_pagina** tabelas_de_pagina, int quantidade_de_processos, int quantidade_de_paginas_por_processo) {
	for(int i = 0 ; i < quantidade_de_processos ; i++) {
		printf("*******************************************\n");
		printf("Processo %d\n", i);
		for(int j = 0 ; j < quantidade_de_paginas_por_processo ; j++) {
			printf("Página %d => [%s,%d]\n", j, (tabelas_de_pagina[i][j].valido ? "V" : "I") , tabelas_de_pagina[i][j].quadro);
		}
		printf("*******************************************\n");
	}
}
