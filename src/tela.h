#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

typedef struct{
    WINDOW *janela_jogo, *janela_pontuacao;
    int cont_pontuacao;
    int Game_over;
    int peca_encaixada;
    int cor;
}Tela;
void tela_inicio();
Tela *cria_tela();
void tela_fim(Tela *tela);
void mostra_tela(Tela* tela);
void verifica_linhas(Tela* tela);
