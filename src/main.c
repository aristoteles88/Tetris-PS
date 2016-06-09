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
	time_t tempo;
    int i=0, movimento = 0, gravidade = 1000;
    Peca = malloc(sizeof(peca));
	
	inicia_ncurses();    
    keypad(stdscr, TRUE);
    curs_set(0);
    noecho();
	cbreak();
    tela_inicio(interfaceJogo);
    tempo = time(NULL);
    interfaceJogo = cria_tela();
    mostra_tela(interfaceJogo);
    nova_peca(Peca, interfaceJogo);
	timeout(-1);
	movimento = pega_input(movimento);
	
    do{
		timeout(gravidade);
		movimento = pega_input(movimento);
		
		for(int i = 0; i < QUANTIDADE_COLUNAS; i++){
			for(int j = 0; j < QUANTIDADE_LINHAS; j++){
				mvprintw(j,i,"%i", interfaceJogo->PosicoesOcupadas[i][j]);
			}
		}
		
		if(movimento != ERR){
			if(movimento == KEY_LEFT || movimento == KEY_RIGHT || movimento == KEY_DOWN || movimento == KEY_UP){
				if(movimento == KEY_UP){
					limpa_peca(Peca, interfaceJogo);
					rotacionaPeca(Peca);
					escrevePeca(Peca, interfaceJogo);
				}
				else if (movimento == KEY_DOWN){
					gravidade = gravidade*0.5;
				}
				else{
					limpa_peca(Peca, interfaceJogo);
					move_peca(Peca, interfaceJogo, movimento);
					escrevePeca(Peca, interfaceJogo);
				}
			}
		}
			
		else{
			limpa_peca(Peca, interfaceJogo);
			move_peca_y(Peca, interfaceJogo, 1);
			escrevePeca(Peca, interfaceJogo);
			for(int j = 0; j < Peca->tamanho; j++){
				if(Peca->posicao[Peca->orientacao][Peca->tamanho-1][1] == 13 || interfaceJogo->PosicoesOcupadas[Peca->posicao[Peca->orientacao][j][0]][(Peca->posicao[Peca->orientacao][j][1])+1] != 0){
					interfaceJogo->peca_encaixada = 1;
				}
			}
		}

		testa_limite(Peca,interfaceJogo);
		
		if(interfaceJogo->peca_encaixada == 1){
			gravaPosicoesOcupadas(Peca, interfaceJogo);
            verifica_linhas(interfaceJogo);
            interfaceJogo->peca_encaixada = 0;
			gravidade = 1000;
            nova_peca(Peca, interfaceJogo);
        }
    }while(interfaceJogo->Game_over == 0);
    tempo = time(NULL) - tempo;
    erase();
    tela_fim(interfaceJogo, tempo);
    finaliza_ncurses();
}

