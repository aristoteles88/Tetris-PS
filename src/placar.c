#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
//#include <time.h>
#include "placar.h"

// Abrindo e lendo arquivo e alocando espaco de memoria para o array de pontuacao
void cria_placar(){
  FILE *fp;
  if (!(fp = fopen(ARQUIVO_PONTUACAO, "r+"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(1);
  }

  //PONTUACAO* aloca memoria do array pontuacao definido em placar.h
  pontuacao = malloc(5 * sizeof *pontuacao);

  // Inicializa a pilha com valores neutros
  int i = 0;
  for (i = 0; i < 5; i++){
      strncpy(pontuacao[i].player, "-", 20);
      pontuacao[i].pontos = 0;
      pontuacao[i].tempo = 0;
  }

  if(fp == NULL)
    printf("Erro ao abrir o arquivo!\n");

  i = 0;
  while ((fscanf(fp, "%s %i %i\n", pontuacao[i].player, &pontuacao[i].pontos, &pontuacao[i].tempo)) != EOF)
    i++;
};

// Recebe nova pontuacao e reordena o array por ordem de maior pontuacao
void atualiza_placar(char *player, int pontos, int tempo){
  char *player_aux;
  int pontos_aux, tempo_aux;

  // Insere pontuacao no ranking caso ela seja maior do que a menor pontuacao
  if (pontos >= pontuacao[4].pontos){
    strncpy(pontuacao[4].player, player, 20);
    pontuacao[4].pontos = pontos;
    pontuacao[4].tempo = tempo;
  }

  // Ordena o ranking em orgem de maior pontuacao
  int i, y;
  for (i = 0; i < 5; i++){
    for (y = i+1; y < 5; y++){
      if (pontuacao[i].pontos <= pontuacao[y].pontos){
        strncpy(player_aux, pontuacao[i].player, 20);
        pontos_aux = pontuacao[i].pontos;
        tempo_aux = pontuacao[i].tempo;

        strncpy(pontuacao[i].player, pontuacao[y].player, 20);
        pontuacao[i].pontos = pontuacao[y].pontos;
        pontuacao[i].tempo = pontuacao[y].tempo;

        strncpy(pontuacao[y].player, player_aux, 20);
        pontuacao[y].pontos = pontos_aux;
        pontuacao[y].tempo = tempo_aux;
      }
    }
  }
}

// Percorre array pontuacao e imprime
void mostra_placar(){
  int i;
  for (i=0; i < 5; i++){
    mvprintw(i+15,20,"%s", pontuacao[i].player);
    mvprintw(i+15,40,"%i", pontuacao[i].pontos);
    mvprintw(i+15,55,"%i", pontuacao[i].tempo);
  }
}

void escreve_placar(){
  FILE *fp;
  if (!(fp = fopen(ARQUIVO_PONTUACAO, "w"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(1);
  }

  // Percorre array escrevendo pontuacao no arquivo
  int i;
  for (i = 0; i < 5; i++)
    fprintf(fp, "%s %i %i\n", pontuacao[i].player, pontuacao[i].pontos, pontuacao[i].tempo);
  fflush(fp);
  fclose(fp);
}
/*
int main(){
  initscr();
  start_color();

  init_pair(1,COLOR_WHITE,COLOR_BLUE); //Texto(Branco) | Fundo(Azul)
  init_pair(2,COLOR_BLUE,COLOR_WHITE); //Texto(Azul) | Fundo(Branco)
  init_pair(3,COLOR_RED,COLOR_WHITE);  //Texto(Vermelho) | Fundo(Branco)
  cria_placar();
  atualiza_placar("Player2", 200, 10);
  escreve_placar();
  mostra_placar();
  //cria_placar();
  //atualiza_placar("Player", 100, 10);
  //mostra_placar();
  //escreve_placar();
  int input = getch();
  erase();
  endwin();
}*/
