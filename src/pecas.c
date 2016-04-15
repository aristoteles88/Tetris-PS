#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ncurses.h>
#include "pecas.h"


void nova_peca(peca* NovaPeca, Tela* tela){
    srand(time(NULL)); 
    
    NovaPeca->tamanho = ((rand() % 3) + 3);
    NovaPeca->orientacao = (rand() % 2);       //orientacao: 0 = horizontal e 1 = vertical.

	if(NovaPeca->orientacao == VERTICAL){
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
    if(peca->orientacao == VERTICAL){
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

void move_peca(peca* Peca, Tela *interfaceJogo, int movimento)
{
    int posicao_invalida=0;
    char decisao = 'n',lugar_ocupado = ' ';
    if(movimento == KEY_LEFT){
            if(Peca->posicao_x_inicial > 1){
                if (Peca->orientacao == 1){
                    for(int i=Peca->posicao_y_inicial; i > Peca->posicao_y_inicial - Peca->tamanho; i--){
                        lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,i,Peca->posicao_x_inicial-1);
                        if(lugar_ocupado == 'o'){
                            lugar_ocupado = ' ';
                            posicao_invalida = 1;
                        }
                    }
                    if(posicao_invalida == 0){
                        move_peca_x(Peca, interfaceJogo, (Peca->posicao_x_inicial - 1));
                    }
                    else{
                        posicao_invalida = 0;
                    }
                }
                if (Peca->orientacao == 0){
                    lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,Peca->posicao_y_inicial,Peca->posicao_x_inicial-1);
                    if(lugar_ocupado == 'o'){
                        lugar_ocupado = ' ';
                        posicao_invalida = 1;
                    }
                    if(posicao_invalida == 0){
                        move_peca_x(Peca, interfaceJogo, (Peca->posicao_x_inicial - 1));
                    }
                    else{
                        posicao_invalida = 0;
                    }
                }
            }
        }
    if(movimento == KEY_RIGHT){
        if (Peca->orientacao == 1){
            if(Peca->posicao_x_inicial < 23){
                for(int i=Peca->posicao_y_inicial; i > Peca->posicao_y_inicial - Peca->tamanho; i--){
                    lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,i,Peca->posicao_x_inicial+1);
                    if(lugar_ocupado == 'o'){
                        posicao_invalida = 1;
                        lugar_ocupado = ' ';
                    }
                }
                if(posicao_invalida == 0){
                    move_peca_x(Peca, interfaceJogo, (Peca->posicao_x_inicial + 1));
                }
                else{
                    posicao_invalida = 0;
                }
            }
        }
        if (Peca->orientacao == 0){
            if(Peca->posicao_x_inicial < 24-Peca->tamanho){
                lugar_ocupado = mvwinch(interfaceJogo->janela_jogo,Peca->posicao_y_inicial,Peca->posicao_x_inicial + Peca->tamanho);
                if(lugar_ocupado == 'o'){
                    lugar_ocupado = ' ';
                    posicao_invalida = 1;
                }
                if(posicao_invalida == 0){
                    move_peca_x(Peca, interfaceJogo, (Peca->posicao_x_inicial + 1));
                }
                else{
                    posicao_invalida = 0;
                }
            }
        }
    }
    if(movimento == KEY_DOWN){
        if(Peca->posicao_y_inicial < 13){
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
    }
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
    if(peca->orientacao == VERTICAL){
        for(int i = peca->posicao_y_inicial; i > (peca->posicao_y_inicial - peca->tamanho); i--){
            mvwaddch(tela->janela_jogo,i,peca->posicao_x_inicial,' ');
        }
    }
    
    if(peca->orientacao == HORIZONTAL){
        for(int i = peca->posicao_x_inicial; i < (peca->posicao_x_inicial + peca->tamanho); i++){
            mvwaddch(tela->janela_jogo,peca->posicao_y_inicial,i,' ');
        }
    }
}

void testa_limite(peca* peca, Tela* tela){
    if(peca->orientacao == VERTICAL){
        if(peca->posicao_y_inicial - peca->tamanho < 5 && tela->peca_encaixada){
            tela->Game_over = 1;
        }
    }
    
    if(peca->orientacao == HORIZONTAL){
        if(peca->posicao_y_inicial < 5 && tela->peca_encaixada){
            tela->Game_over = 1;
        }
    }
}
