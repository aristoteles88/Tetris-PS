#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#define ARQUIVO_PONTUACAO "placar.txt"

/**
 * Estrututa de dados usada para armazenar dados de placar lidos  do arquivo placar.txt.
 */
typedef struct{
    char player[20];
    int pontos;
    int tempo;
}PONTUACAO;

PONTUACAO* pontuacao;

/**
 * Instancia placar pontuacao, le arquivo e popula o vetor de pontuacao.
 *  @return void
 */
void cria_placar();

/**
 * Ordena placar por ordem de maior pontuacao para a menor.
 *  @param *player um char
 *  @param pontos um int
 *  @param tempo um int
 *  @return void
 */
void atualiza_placar(char *player, int pontos, int tempo);

/**
 * Imprime placar na tela usando ncurses.
 *  @return void
 */
void mostra_placar();

/**
 * Escreve o placar atualizado no arquivo.
 *  @return void
 */
void escreve_placar();
