#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "engine.h"
#include "placar.h"

char nome_jogador[20];

#define QUANTIDADE_LINHAS 15
#define QUANTIDADE_COLUNAS 25

/**
 * Estrutura de dados que armazena posicoes ocupadas da matriz tela.
 * Também armazena pontuacao, cores e indicativo de jogo em execucao.
 */
typedef struct{
    WINDOW *janela_jogo, *janela_pontuacao;
	int PosicoesOcupadas[QUANTIDADE_COLUNAS][QUANTIDADE_LINHAS]; //O valor das casas representa a cor da peça encaixada naquela posicao. Valor igual a 0 indica posição desocupada.
    int cont_pontuacao;
    int Game_over;
    int peca_encaixada;
    int cor;
}Tela;

/**
 * Imprime a tela de inicio, inicia o placar e recebe o nome do jogador.
 *  @return void
 */
void tela_inicio();

/**
 * Imprime linha que representa o limite ou as paredes do tetris.
 *  @param *tela tipo Tela
 *  @return void
 */
void mostraLinhaLimite(Tela *tela);

/**
 * inicializa variaveis usadas na formação da tela, incluindo a matriz de posicoes.
 *  @return Tela
 */
Tela *cria_tela();

/**
 * Imprime a tela de final (game over) e chama metodos de gravar pontuacao em arquivo, do modulo placar.
 *  @param *tela tipo Tela
 *  @param tempo um int
 *  @return void
 */
void tela_fim(Tela *tela, int tempo);

/**
 * Só mostra a tela mesmo.
 *  @param tela tipo Tela
 *  @return void
 */
void mostra_tela(Tela* tela);

/**
 * Verifica se linha foi completada e conta na pontuacao.
 *  @param tela tipo Tela
 *  @return void
 */
void verifica_linhas(Tela* tela);
