#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
//#include <time.h>

#define ARQUIVO_PONTUACAO "placar.txt"

typedef struct{
    char player[20];
    int pontos;
    int tempo;
}PONTUACAO;

PONTUACAO* pontuacao;

void cria_placar();
void atualiza_placar(char *player, int pontos, int tempo);
void mostra_placar();
void escreve_placar();
