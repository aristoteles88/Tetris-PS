#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "tela.h"

void tela_inicio(){
	//Inicia Placar
	cria_placar();

	int tecla = 1;
    WINDOW *telaInicio=newwin(20,101,1,1);
    mvprintw(2,20,"///////// ///////// ///////// ////////  ///  ////////");
    mvprintw(3,20,"   ///    //           ///    //     // /// //       ");
    mvprintw(4,20,"   ///    //           ///    //    //  /// //       ");
    mvprintw(5,20,"   ///    /////////    ///    //////    ///  /////// ");
    mvprintw(6,20,"   ///    //           ///    //   //   ///        //");
    mvprintw(7,20,"   ///    //           ///    //    //  ///        //");
    mvprintw(8,20,"   ///    /////////    ///    //     // /// //////// ");
    mvprintw(20,20,"Insira seu nome de jogador e aperte (Enter) para comecar.");
		int i = 0;
		do{
			tecla = pega_input(tecla);
			if ((tecla != '\n') && (tecla != '\t') && (tecla != '\b') && (tecla != '\r') && (tecla != ' ')){
				nome_jogador[i] = (char) tecla;
				mvprintw(12,i+20,"%c", nome_jogador[i]);
				i++;
			}
		} while ((tecla != '\n') && i < 20);
    erase();
    refresh();
}

void tela_fim(Tela* t, int tempo){
    WINDOW *telaFinal=newwin(20,102,1,1);
    int tecla = 1;

		// Chama metodos de organizar e gravar pontuacao
		atualiza_placar(nome_jogador, t->cont_pontuacao, tempo);
		escreve_placar();

    do{
        mvprintw(2,1,"  /////////  ///////  //     //  /////////   ///////// //     // ///////// //////// ");
        mvprintw(3,1,"  //        //     // ///   ///  //          //     // //     // //        //     //");
        mvprintw(4,1,"  //        //     // /////////  //          //     // //     // //        //    // ");
        mvprintw(5,1,"  //  ///// ///////// // /// //  /////////   //     // //     // ///////// //////   ");
        mvprintw(6,1,"  //     // //     // //     //  //          //     //  //   //  //        //   //  ");
        mvprintw(7,1,"  //     // //     // //     //  //          //     //   // //   //        //    // ");
        mvprintw(8,1,"  ///////// //     // //     //  /////////   /////////    ///    ///////// //     //");
        mvprintw(23,20,"Pressione a tecla 'q' para encerrar.");
				mvprintw(13,20,"JOGADOR             PONTUACAO      TEMPO ");

				// Chama função que imprime placar usando ncurses
				mostra_placar();
        refresh();
        tecla = pega_input(tecla);
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

	mostraLinhaLimite(tela);

    tela->cont_pontuacao = pontos;

    tela->Game_over = 0;

    tela->peca_encaixada = 0;

	for(int i = 0; i < QUANTIDADE_COLUNAS; i++){
		for(int j = 0; j < QUANTIDADE_LINHAS; j++){
			tela->PosicoesOcupadas[i][j] = 0;
		}
	}
    return tela;
}

void mostraLinhaLimite(Tela *tela){
	char lugarocupado = ' ';
	for (int i = 1; i < 24; i++){
		lugarocupado = mvwinch(tela->janela_jogo,5,i);
		if (lugarocupado != 'o'){
			wattrset(tela->janela_jogo, COLOR_PAIR(2));
			mvwprintw(tela->janela_jogo,5,i,"-");
		}
	}
}


void mostra_tela(Tela *t){
    mvwprintw(t->janela_pontuacao,1,1, "PONTUACAO: %.12d", t->cont_pontuacao);
	mostraLinhaLimite(t);
    wrefresh(t->janela_jogo);
    wrefresh(t->janela_pontuacao);

}

void verifica_linhas(Tela* tela){
	int contaPosicoesOcupadas = 0;
    for(int j = 13; j > 4; j--){
		for(int i = 1; i < QUANTIDADE_COLUNAS-1; i++){
			if(tela->PosicoesOcupadas[i][j] != 0){
				contaPosicoesOcupadas++;
			}
		}
		if(contaPosicoesOcupadas == 23){
			for(int k = j; k > 4; k--){
				for(int l = 1; l < QUANTIDADE_COLUNAS-1; l++){
					tela->PosicoesOcupadas[l][k] = tela->PosicoesOcupadas[l][k-1];
				}
			}
			tela->cont_pontuacao += 100;
		}
		contaPosicoesOcupadas = 0;
	}
	for(int j = 13; j > 4; j--){
		for(int i = 1; i < QUANTIDADE_COLUNAS-1; i++){
			  if(tela->PosicoesOcupadas[i][j] != 0){
				  wattrset(tela->janela_jogo, COLOR_PAIR(tela->PosicoesOcupadas[i][j]));
				  mvwprintw(tela->janela_jogo,j,i,"o");
			  }
			  else{
				  mvwprintw(tela->janela_jogo,j,i," ");
			  }
		}
	}
	mostra_tela(tela);
}
