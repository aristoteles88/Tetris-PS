# include <stdio.h>
# include <stdlib.h>
# include <ncurses.h>
# include "pecas.h"
# include "engine.h"

int main(){
    Tela *interfaceJogo;
    peca* Peca = NULL;
    int i=0, movimento, tecla=0 , posicao_invalida=0;
    char decisao = 'n',lugar_ocupado = ' ';
    
    Peca = malloc(sizeof(peca));
    
    inicia_ncurses();    
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    tela_inicio();	
    interfaceJogo = cria_tela();
    mostra_tela(interfaceJogo);
    nova_peca(Peca, interfaceJogo);
    
    do{
        movimento = pega_input(tecla);
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
        testa_limite(Peca,interfaceJogo);
        if(interfaceJogo->peca_encaixada == 1){
            verifica_linhas(interfaceJogo);
            interfaceJogo->peca_encaixada = 0;
            nova_peca(Peca, interfaceJogo);
        }
    }while(interfaceJogo->Game_over == 0);
    erase();
    tela_fim(interfaceJogo);
    finaliza_ncurses();
}

