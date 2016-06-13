#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

/**
 * inicia ncurses e inicializa a paleta de cores da tela.
 */
void inicia_ncurses();
/**
 * Apaga tela e finaliza ncurses.
 */
void finaliza_ncurses();
/**
 * Captura um char e o retorna um int. Usado para receber comando do tetris.
 *  @param input um int
 *  @return void
 */
int pega_input(int input);
