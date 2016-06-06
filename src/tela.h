#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include "engine.h"

#define QUANTIDADE_LINHAS 15
#define QUANTIDADE_COLUNAS 25

typedef struct{
    WINDOW *janela_jogo, *janela_pontuacao;
	int PosicoesOcupadas[QUANTIDADE_COLUNAS][QUANTIDADE_LINHAS]; //O valor das casas representa a cor da peça encaixada naquela posicao. Valor igual a 0 indica posição desocupada.
    int cont_pontuacao;
    int Game_over;
    int peca_encaixada;
    int cor;
}Tela;
void tela_inicio();
void mostraLinhaLimite(Tela *tela);
Tela *cria_tela();
void tela_fim(Tela *tela, int tempo);
void mostra_tela(Tela* tela);
void verifica_linhas(Tela* tela);
