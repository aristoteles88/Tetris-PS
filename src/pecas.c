#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "pecas.h"


void nova_peca(peca* NovaPeca, Tela* tela){
    srand(time(NULL)); 
	
	peca PecaGeralI3 = {0, 3, 0, {{{13,1},{13,2},{13,3},{0,0},{0,0},{0,0},{0,0}},
								  {{12,1},{13,1},{14,1},{0,0},{0,0},{0,0},{0,0}},
								  {{13,1},{13,2},{13,3},{0,0},{0,0},{0,0},{0,0}},
								  {{12,1},{13,1},{14,1},{0,0},{0,0},{0,0},{0,0}}}, 0},
		 
		PecaGeralI4 = {1, 4, 0, {{{13,1},{13,2},{13,3},{13,4},{0,0},{0,0},{0,0}},
								 {{12,1},{13,1},{14,1},{15,1},{0,0},{0,0},{0,0}},
								 {{13,1},{13,2},{13,3},{13,4},{0,0},{0,0},{0,0}},
								 {{12,1},{13,1},{14,1},{15,1},{0,0},{0,0},{0,0}}}, 0},
		
		PecaGeralI5 = {2, 5, 0, {{{13,1},{13,2},{13,3},{13,4},{13,5},{0,0},{0,0}},
								 {{11,1},{12,1},{13,1},{14,1},{15,1},{0,0},{0,0}},
								 {{13,1},{13,2},{13,3},{13,4},{13,5},{0,0},{0,0}},
								 {{11,1},{12,1},{13,1},{14,1},{15,1},{0,0},{0,0}}}, 0},
		
		PecaGeralO = {3, 4, 0, {{{13,1},{13,2},{14,1},{14,2},{0,0},{0,0},{0,0}},
								{{13,1},{13,2},{14,1},{14,2},{0,0},{0,0},{0,0}},
								{{13,1},{13,2},{14,1},{14,2},{0,0},{0,0},{0,0}},
								{{13,1},{13,2},{14,1},{14,2},{0,0},{0,0},{0,0}}}, 0},
		
		PecaGeralL = {4, 5, 0, {{{13,1},{13,2},{13,3},{14,3},{15,3},{0,0},{0,0}},
								{{13,1},{13,2},{13,3},{12,3},{11,3},{0,0},{0,0}},
								{{11,1},{12,1},{13,1},{13,2},{13,3},{0,0},{0,0}},
								{{13,1},{14,1},{15,1},{13,2},{13,3},{0,0},{0,0}}}, 0},
		
		PecaGeralZ = {5, 5, 0, {{{12,1},{13,1},{13,2},{13,3},{14,3},{0,0},{0,0}},
								{{14,1},{14,2},{13,2},{12,2},{12,3},{0,0},{0,0}},
								{{12,1},{13,1},{13,2},{13,3},{14,3},{0,0},{0,0}},
								{{14,1},{14,2},{13,2},{12,2},{12,3},{0,0},{0,0}}}, 0},
		 
		PecaGeralT = {6, 7, 0, {{{11,1},{12,1},{13,1},{14,1},{15,1},{13,2},{13,3}},
								{{12,1},{12,2},{12,3},{13,3},{14,3},{12,4},{12,5}},
								{{13,1},{13,2},{11,3},{12,3},{13,3},{14,3},{15,3}},
								{{12,3},{13,3},{14,1},{14,2},{14,3},{14,4},{14,5}}}, 0};
		
    NovaPeca->tipo = (rand() % 7);
	switch (NovaPeca->tipo){
	  case 0:
			*NovaPeca = PecaGeralI3;
			break;
	  case 1:
			*NovaPeca = PecaGeralI4;
			break;
	  case 2:
			*NovaPeca = PecaGeralI5;
			break;
	  case 3:
			*NovaPeca = PecaGeralO;
			break;
	  case 4:
			*NovaPeca = PecaGeralL;
			break;
	  case 5:
			*NovaPeca = PecaGeralZ;
			break;
	  case 6:
			*NovaPeca = PecaGeralT;
			break;
	}
	
    NovaPeca->orientacao = (rand() % 4);
	
	switch (NovaPeca->orientacao){
	  case 0:
		  break;
	  case 1:
		  rotacionaPeca(NovaPeca);
		  break;
	  case 2:
		  for(int i = 0; i < 2; i++){
			  rotacionaPeca(NovaPeca);
		  }
		  break;
	  case 3:
		  for(int i = 0; i < 3; i++){
			  rotacionaPeca(NovaPeca);
		  }
		  break;
	}
	
	NovaPeca->cor = (rand() % 5) + 3;
	
    escrevePeca(NovaPeca,tela);
}

void escrevePeca(peca* peca, Tela* tela){
    wattrset(tela->janela_jogo, COLOR_PAIR(peca->cor));
    for(int i = 0; i < peca->tamanho; i++){
		mvwaddch(tela->janela_jogo,peca->posicao[peca->orientacao][i][1],peca->posicao[peca->orientacao][i][0],'o');
    }

    mostra_tela(tela);
}

void rotacionaPeca(peca* peca){
	peca->orientacao = (peca->orientacao + 1) % 4;
}

void move_peca(peca* Peca, Tela *interfaceJogo, int movimento){
    char lugar_ocupado = ' ';
    int ResultadotestaColisao = 0;
    	
    if(movimento == KEY_LEFT){
		move_peca_x(Peca, interfaceJogo, -1);
		for(int i = 0; i < ORIENTACAO; i++){
			ResultadotestaColisao = testaColisaox(Peca, interfaceJogo, i);
			if(ResultadotestaColisao){
				for(int j = 0; j < Peca->tamanho; j++){
					Peca->posicao[i][j][0] += 1;
				}
			}
		}
	}
		
	if(movimento == KEY_RIGHT){
    	move_peca_x(Peca, interfaceJogo, 1);
		for(int i = 0; i < ORIENTACAO; i++){
			ResultadotestaColisao = testaColisaox(Peca, interfaceJogo, i);
			if(ResultadotestaColisao){
				for(int j = 0; j < Peca->tamanho; j++){
					Peca->posicao[i][j][0] -= 1;
				}
			}
		}
	}
}

void move_peca_x(peca* peca, Tela* tela, int x){    
	for(int i = 0; i < ORIENTACAO; i++){
		for(int j = 0; j < peca->tamanho; j++){
			peca->posicao[i][j][0] += x;
		}
	}
}

void move_peca_y(peca* peca, Tela* tela, int y){
    int ResultadotestaColisao = 0;
    for(int i = 0; i < ORIENTACAO; i++){
		for(int j = 0; j < peca->tamanho; j++){
			peca->posicao[i][j][1] += y;
		}
		ResultadotestaColisao = testaColisaoy(peca, tela, i);
		if(ResultadotestaColisao){
			for(int j = 0; j < peca->tamanho; j++){
				peca->posicao[i][j][1] -= y;
			}
		}
	}
}

void limpa_peca(peca* peca, Tela* tela){
	for(int i = 0; i < peca->tamanho; i++){
		mvwaddch(tela->janela_jogo,peca->posicao[peca->orientacao][i][1],peca->posicao[peca->orientacao][i][0],' ');
    } 
}

void testa_limite(peca* peca, Tela* tela){
    for(int i = 0; i < peca->tamanho; i++){
		if(peca->posicao[peca->orientacao][i][1] < 5  && tela->peca_encaixada){
            tela->Game_over = 1;
        }
    }
}

int testaColisaox(peca* Peca, Tela* tela, int orientacao){
	int posicao_invalida = 0;
	for(int j = 0; j < Peca->tamanho; j++){
		if(Peca->posicao[orientacao][j][0] < 1 || Peca->posicao[orientacao][j][0] > 23 || tela->PosicoesOcupadas[Peca->posicao[orientacao][j][0]][Peca->posicao[orientacao][j][1]] != 0){
			posicao_invalida = 1;
		}
	}
	
	return posicao_invalida;
}

int testaColisaoy(peca* Peca, Tela* tela, int orientacao){
	int posicao_invalida = 0;
	for(int j = 0; j < Peca->tamanho; j++){
		mvprintw(31+j,0,"Posicao: (%i,%i)", Peca->posicao[orientacao][j][0],Peca->posicao[orientacao][j][1]);
		mvprintw(28,0,"Posicao seguinte: %i", tela->PosicoesOcupadas[Peca->posicao[orientacao][Peca->tamanho-1][0]][Peca->posicao[orientacao][Peca->tamanho-1][1]]);
		if(Peca->posicao[orientacao][j][1] == 14 || tela->PosicoesOcupadas[Peca->posicao[orientacao][j][0]][Peca->posicao[orientacao][j][1]] != 0){
			posicao_invalida = 1;
		}
	}
	
	return posicao_invalida;
}

void gravaPosicoesOcupadas(peca *peca, Tela* tela){
	for(int i = 0; i < peca->tamanho; i++){
		tela->PosicoesOcupadas[peca->posicao[peca->orientacao][i][0]][peca->posicao[peca->orientacao][i][1]] = peca->cor;
	}
}