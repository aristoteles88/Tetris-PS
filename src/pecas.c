#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "pecas.h"


void nova_peca(peca* NovaPeca, Tela* tela){
    srand(time(NULL)); 
    
    NovaPeca->tamanho = ((rand() % 3) + 3);
    NovaPeca->orientacao = (rand() % 2);       //orientacao: 0 = horizontal e 1 = vertical.

						    if(NovaPeca->orientacao == 1){
        NovaPeca->posicao_y_inicial = 0 + NovaPeca->tamanho;
        NovaPeca->posicao_x_inicial = 13;
    }
    else{
        NovaPeca->posicao_y_inicial = 1;
        if(NovaPeca->tamanho != 5){
            NovaPeca->posicao_x_inicial = 12;
        }
        if(NovaPeca->tamanho == 5){
            NovaPeca->posicao_x_inicial = 11;
        }
    }
    
    NovaPeca->cor = ((rand() % 5) + 3);
    escrevePeca(NovaPeca,tela);

}

void escrevePeca(peca* peca, Tela* tela){
    wattrset(tela->janela_jogo, COLOR_PAIR(peca->cor));
    if(peca->orientacao == 1){
        for(int i = peca->posicao_y_inicial; i > (peca->posicao_y_inicial - peca->tamanho); i--){
            mvwaddch(tela->janela_jogo,i,peca->posicao_x_inicial,'o');
        }
    }
    else{
        for(int i = peca->posicao_x_inicial; i < (peca->posicao_x_inicial + peca->tamanho); i++){
            mvwaddch(tela->janela_jogo,peca->posicao_y_inicial,i,'o');
        }
    }
    
    mostra_tela(tela);
}

void move_peca_x(peca* peca, Tela* tela, int x){
    
    limpa_peca(peca,tela);
    
    peca->posicao_x_inicial = x;
    escrevePeca(peca, tela);
}

void move_peca_y(peca* peca, Tela* tela, int y){
    limpa_peca(peca,tela);
    
    peca->posicao_y_inicial = y;
    escrevePeca(peca, tela);
}

void limpa_peca(peca* peca, Tela* tela){
    if(peca->orientacao == 1){
        for(int i = peca->posicao_y_inicial; i > (peca->posicao_y_inicial - peca->tamanho); i--){
            mvwaddch(tela->janela_jogo,i,peca->posicao_x_inicial,' ');
        }
    }
    
    if(peca->orientacao == 0){
        for(int i = peca->posicao_x_inicial; i < (peca->posicao_x_inicial + peca->tamanho); i++){
            mvwaddch(tela->janela_jogo,peca->posicao_y_inicial,i,' ');
        }
    }
}

void testa_limite(peca* peca, Tela* tela){
    if(peca->orientacao == 1){
        if(peca->posicao_y_inicial - peca->tamanho < 5 && tela->peca_encaixada == 1){
            tela->Game_over = 1;
        }
    }
    
    if(peca->orientacao == 0){
        if(peca->posicao_y_inicial < 5 && tela->peca_encaixada == 1){
            tela->Game_over = 1;
        }
    }
}
