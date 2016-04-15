#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "tela.h"

void tela_inicio(){
    WINDOW *telaInicio=newwin(20,101,1,1);
    mvprintw(2,20,"///////// ///////// ///////// ////////  ///  ////////");
    mvprintw(3,20,"   ///    //           ///    //     // /// //       ");
    mvprintw(4,20,"   ///    //           ///    //    //  /// //       ");
    mvprintw(5,20,"   ///    /////////    ///    //////    ///  /////// ");
    mvprintw(6,20,"   ///    //           ///    //   //   ///        //");
    mvprintw(7,20,"   ///    //           ///    //    //  ///        //");
    mvprintw(8,20,"   ///    /////////    ///    //     // /// //////// ");
    mvprintw(20,30,"Pressione uma tecla para começar.");
    getch();
    erase();
    refresh();
}

void tela_fim(Tela* t, int tempo){
    WINDOW *telaFinal=newwin(20,102,1,1);
    int tecla;

    do{
        mvprintw(2,1,"  /////////  ///////  //     //  /////////   ///////// //     // ///////// //////// ");
        mvprintw(3,1,"  //        //     // ///   ///  //          //     // //     // //        //     //");
        mvprintw(4,1,"  //        //     // /////////  //          //     // //     // //        //    // ");
        mvprintw(5,1,"  //  ///// ///////// // /// //  /////////   //     // //     // ///////// //////   ");
        mvprintw(6,1,"  //     // //     // //     //  //          //     //  //   //  //        //   //  ");
        mvprintw(7,1,"  //     // //     // //     //  //          //     //   // //   //        //    // ");
        mvprintw(8,1,"  ///////// //     // //     //  /////////   /////////    ///    ///////// //     //");
        mvprintw(20,30,"Sua pontuação foi: %d", t->cont_pontuacao);
        mvprintw(21,30,"Tempo do jogo: %d", tempo);
        mvprintw(23,30,"Pressione a tecla 'q' para encerrar.");
        refresh();
        tecla = getch();
    }while(tecla != 'q');
    
    erase();
    refresh();
}

Tela *cria_tela(){
    Tela *tela;
    WINDOW *Jogo, *Pontuacao;
    int pontos=0;
    
    mvprintw(2,45,"TETRIS");
    refresh();
    
    tela = malloc(sizeof(Tela));
    
    Jogo = newwin(15, 25, 6, 35);
    tela->janela_jogo = Jogo;
    wbkgd(tela->janela_jogo,COLOR_PAIR(1));
    box(tela->janela_jogo, ACS_VLINE, ACS_HLINE);
    
    Pontuacao = newwin(3, 25, 3, 35);
    tela->janela_pontuacao = Pontuacao;
    wbkgd(tela->janela_pontuacao,COLOR_PAIR(1));
    box(tela->janela_pontuacao, ACS_VLINE, ACS_HLINE);

    wattrset(tela->janela_jogo, COLOR_PAIR(2));
    mvwprintw(tela->janela_jogo,5,1,"------------------------");
    
    tela->cont_pontuacao = pontos;
     
    tela->Game_over = 0;
    
    tela->peca_encaixada = 0;
    
    return tela;
}

void mostra_tela(Tela *t){
    mvwprintw(t->janela_pontuacao,1,1, "PONTUACAO: %.12d", t->cont_pontuacao);
    wrefresh(t->janela_jogo);
    wrefresh(t->janela_pontuacao);
    
}

void verifica_linhas(Tela* tela){
    int linha, coluna, posicao_x, posicao_y, casas_ocupadas, cor;
    char caracter_casa;
        
    casas_ocupadas = 0;
    
    for(linha = 13; linha > 0; linha--){
        for(coluna = 1; coluna < 24; coluna++){
            caracter_casa = mvwinch(tela->janela_jogo,linha,coluna);
            if(caracter_casa == 'o'){
                casas_ocupadas++;
                caracter_casa = ' ';
            }
        }
        if(casas_ocupadas == 23){
            for(posicao_y = linha; posicao_y > 1; posicao_y--){
                for(posicao_x = 1; posicao_x < 24; posicao_x++){
                   // cor = mvwinch(tela->janela_jogo,posicao_y-1,posicao_x) & A_COLOR;
                    caracter_casa = mvwinch(tela->janela_jogo,posicao_y-1,posicao_x);
                    wattrset(tela->janela_jogo, COLOR_PAIR(cor));
                    mvwaddch(tela->janela_jogo,posicao_y,posicao_x,caracter_casa);
                }
            }
            tela->cont_pontuacao = tela->cont_pontuacao + 100;
            linha++;
        }
        casas_ocupadas = 0;
        mostra_tela(tela);
    }
}
