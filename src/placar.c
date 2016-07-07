#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>
#include "placar.h"

/**
 * Instancia placar pontuacao, le arquivo e popula o vetor de pontuacao.
 *  @return void
 */
void cria_placar(){
  int i;
  FILE *fp;
  if (!(fp = fopen(ARQUIVO_PONTUACAO, "r+"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(0);
  }

  //PONTUACAO* aloca memoria do array pontuacao definido em placar.h
  pontuacao = malloc(5 * sizeof *pontuacao);

  // Inicializa a pilha com valores neutro
  for (i = 0; i < 5; i++){
      strncpy(pontuacao[i].player, "-", 20);
      pontuacao[i].pontos = 0;
      pontuacao[i].tempo = 0;
  }

  if(fp == NULL)
    printf("Arquivo placar.txt vazio!\n");

  i = 0;
  while ((fscanf(fp, "%s %i %i\n", pontuacao[i].player, &pontuacao[i].pontos, &pontuacao[i].tempo)) != EOF)
    i++;
};

/**
 * Ordena placar por ordem de maior pontuacao para a menor.
 *  @param *player um char
 *  @param pontos um int
 *  @param tempo um int
 *  @return void
 */
void atualiza_placar(char *player, int pontos, int tempo){
  char *player_aux;
  int pontos_aux, tempo_aux, i, y;

  // Insere pontuacao no ranking caso ela seja maior do que a menor pontuacao
  if (pontos >= pontuacao[4].pontos){
    strncpy(pontuacao[4].player, player, 20);
    pontuacao[4].pontos = pontos;
    pontuacao[4].tempo = tempo;
  }

  // Ordena o ranking em orgem de maior pontuacao
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

/**
 * Ordena placar por ordem de maior pontuacao para a menor.
 *  @param *player um char
 *  @param pontos um int
 *  @param tempo um int
 *  @return void
 */
void mostra_placar(){
  int i;
  for (i=0; i < 5; i++){
    //mvprintw(i+15,20,"%s", pontuacao[i].player);
    //mvprintw(i+15,40,"%i", pontuacao[i].pontos);
    //mvprintw(i+15,55,"%i", pontuacao[i].tempo);
  }
}

/**
 * Escreve o placar atualizado no arquivo.
 *  @return void
 */
void escreve_placar(){
  int i;
  FILE *fp;
  if (!(fp = fopen(ARQUIVO_PONTUACAO, "w"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(0);
  }

  // Percorre array escrevendo pontuacao no arquivo
  for (i = 0; i < 5; i++)
    fprintf(fp, "%s %i %i\n", pontuacao[i].player, pontuacao[i].pontos, pontuacao[i].tempo);
  fflush(fp);
  fclose(fp);
}
