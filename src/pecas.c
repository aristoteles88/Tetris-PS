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
								{{13,1},{13,2},{13,3},{14,1},{15,1},{0,0},{0,0}}}, 0},
		
		PecaGeralZ = {5, 5, 0, {{{12,1},{13,1},{13,2},{13,3},{14,3},{0,0},{0,0}},
								{{14,1},{14,2},{13,2},{12,2},{12,3},{0,0},{0,0}},
								{{12,1},{13,1},{13,2},{13,3},{14,3},{0,0},{0,0}},
								{{14,1},{14,2},{13,2},{12,2},{12,3},{0,0},{0,0}}}, 0},
		 
		PecaGeralT = {6, 7, 0, {{{11,1},{12,1},{13,1},{14,1},{15,1},{13,2},{13,3}},
								{{12,1},{12,2},{12,3},{12,4},{12,5},{13,3},{14,3}},
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
		  rotacionaPeca(NovaPeca, tela);
		  break;
	  case 2:
		  for(int i = 0; i < 2; i++){
			  rotacionaPeca(NovaPeca, tela);
		  }
		  break;
	  case 3:
		  for(int i = 0; i < 3; i++){
			  rotacionaPeca(NovaPeca, tela);
		  }
		  break;
	}
	
	NovaPeca->cor = (rand() % 5) + 3;
	
    escrevePeca(NovaPeca,tela);
	mvprintw(0,0,"Tipo: %i", NovaPeca->tipo);
	mvprintw(1,0,"Orientacao: %i", NovaPeca->orientacao);
	mvprintw(2,0,"Tamanho: %i", NovaPeca->tamanho);
}

void escrevePeca(peca* peca, Tela* tela){
    wattrset(tela->janela_jogo, COLOR_PAIR(peca->cor));
    for(int i = 0; i < peca->tamanho; i++){
		mvwaddch(tela->janela_jogo,peca->posicao[peca->orientacao][i][1],peca->posicao[peca->orientacao][i][0],'o');
    }
    for(int j = 0; j < peca->tamanho; j++){
		mvprintw(j+12,0,"Peca Atual: (%i,%i)", peca->posicao[peca->orientacao][j][0], peca->posicao[peca->orientacao][j][1]);
	}
    mostra_tela(tela);
}

void rotacionaPeca(peca* peca, Tela* tela){
	peca->orientacao = (peca->orientacao++) % 4;
}

void move_peca(peca* Peca, Tela *interfaceJogo, int movimento){
    char lugar_ocupado = ' ';
    peca *PecaTemporaria = Peca;
	
    if(movimento == KEY_LEFT){
		limpa_peca(Peca,interfaceJogo);
		move_peca_x(PecaTemporaria, interfaceJogo, -1);
		testaColisao(PecaTemporaria, Peca, interfaceJogo);
		escrevePeca(Peca, interfaceJogo);
	}
		
	if(movimento == KEY_RIGHT){
    	limpa_peca(Peca,interfaceJogo);
		move_peca_x(PecaTemporaria, interfaceJogo, 1);
		testaColisao(PecaTemporaria, Peca, interfaceJogo);
		escrevePeca(Peca, interfaceJogo);
	}
}

/*    if(movimento == KEY_DOWN){
		for(int i = 0; i < Peca->tamanho; i++){
			if(Peca->posicao[Peca->orientacao][i][1] < 13){
				if(Peca->orientacao == 1){
                lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,Peca->posicao_y_inicial+1,Peca->posicao_x_inicial);
                if(lugar_ocupado == 'o'){
                    lugar_ocupado = ' ';
                    posicao_invalida = 1;
                }
                if(posicao_invalida == 0){
                    move_peca_y(Peca, interfaceJogo, (Peca->posicao_y_inicial + 1));
                }
                else{
                    interfaceJogo->peca_encaixada = 1;
                    posicao_invalida = 0;
                }
            }
            if(Peca->orientacao == 0){
                for(int i=Peca->posicao_x_inicial; i < Peca->posicao_x_inicial + Peca->tamanho; i++){
                    lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,Peca->posicao_y_inicial+1,i);
                    if(lugar_ocupado == 'o'){
                        lugar_ocupado = ' ';
                        posicao_invalida = 1;
                    }
                }
                if(posicao_invalida == 0){
                    move_peca_y(Peca, interfaceJogo, Peca->posicao_y_inicial + 1);
                }
                else{
                    interfaceJogo->peca_encaixada = 1;
                    posicao_invalida = 0;
                }
            }
        }
        if(Peca->posicao_y_inicial == 13){
            interfaceJogo->peca_encaixada = 1;
        }
    }*/

void move_peca_x(peca* peca, Tela* tela, int x){    
	for(int i = 0; i < ORIENTACAO; i++){
		for(int j = 0; j < peca->tamanho; j++){
			peca->posicao[i][j][0] = peca->posicao[i][j][0] + x;
		}
	}
}

void move_peca_y(peca* peca, Tela* tela, int y){
    for(int i = 0; i < ORIENTACAO; i++){
		for(int j = 0; j < peca->tamanho; j++){
			peca->posicao[peca->orientacao][i][1] = y;
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
		if(peca->posicao[peca->orientacao][i][1] > 11 && tela->peca_encaixada){
            tela->Game_over = 1;
        }
    }
}

/*void recuaPecaY(peca* peca){
	int posicaomaisalta = 10;
	for(int i = 0; i < peca->tamanho; i++){
		if(peca->posicao[i][1] < posicaomaisalta){
			posicaomaisalta = peca->posicao[i][1];
		}
	}
	if(posicaomaisalta != 1){
		for(int i = 0; i < peca->tamanho; i++){
			peca->posicao[i][1] -= (posicaomaisalta - 1);
		}
	}
}*/

void testaColisao(peca* Peca, peca* PecaTemporaria, Tela* tela){
	int posicao_invalida = 0;
	for(int i = 0; i < ORIENTACAO; i++){
		for(int j = 0; j < PecaTemporaria->tamanho; j++){
			if(PecaTemporaria->posicao[i][j][0] < 2 || PecaTemporaria->posicao[i][j][0] > 22 || tela->PosicoesOcupadas[PecaTemporaria->posicao[i][j][0]][PecaTemporaria->posicao[i][j][1]] != 0){
				posicao_invalida = 1;
			}
		}
		if(posicao_invalida == 1){
			posicao_invalida = 0;
		}
		else{
			for(int k = 0; k < PecaTemporaria->tamanho; k++){
				Peca->posicao[i][k][0] = PecaTemporaria->posicao[i][k][0];
				mvprintw(20,0,"Peca Temporaria: (%i,%i)", PecaTemporaria->posicao[PecaTemporaria->orientacao][k][0], PecaTemporaria->posicao[PecaTemporaria->orientacao][k][1]);
				mvprintw(21,0,"Peca: (%i,%i)", PecaTemporaria->posicao[Peca->orientacao][k][0], Peca->posicao[Peca->orientacao][k][1]);
			}	
		}
	}
}