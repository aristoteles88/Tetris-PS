//! Arquivo principal do programa Tetris implementado para o trabalho prático da disciplina Programação Sistemática..
/////////////////////////////////////////////////////////////
/*!
 *	\author Arthur Moreira
 *	\author Pedro Araújo
 *	\author Marcos Vinicius Pereira Marques		
 *	\author Aristóteles Soares Benício Júnior
 *	\version 2.0
 */
/////////////////////////////////////////////////////////////

# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <ncurses.h>
# include "pecas.h"
# include "engine.h"

int main(){
    Tela *interfaceJogo;
    peca* Peca = NULL;
    int i=0, movimento, tecla=0;
    time_t tempo;
    Peca = malloc(sizeof(peca));
	
	inicia_ncurses();    
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
    tela_inicio(interfaceJogo);
    tempo = time(NULL);
    interfaceJogo = cria_tela();
    mostra_tela(interfaceJogo);
    nova_peca(Peca, interfaceJogo);
    
    do{
        movimento = pega_input(tecla);
		if(movimento == KEY_UP){
			limpa_peca(Peca, interfaceJogo);
			rotacionaPeca(Peca, interfaceJogo);
			escrevePeca(Peca, interfaceJogo);
		}
		else if (movimento == KEY_DOWN){
			move_peca(Peca, interfaceJogo, movimento);
		}
		else{
			move_peca(Peca, interfaceJogo, movimento);
		}

        testa_limite(Peca,interfaceJogo);
        if(interfaceJogo->peca_encaixada == 1){
            verifica_linhas(interfaceJogo);
            interfaceJogo->peca_encaixada = 0;
            nova_peca(Peca, interfaceJogo);
        }
    }while(interfaceJogo->Game_over == 0);
    tempo = time(NULL) - tempo;
    erase();
    tela_fim(interfaceJogo, tempo);
    finaliza_ncurses();
}

