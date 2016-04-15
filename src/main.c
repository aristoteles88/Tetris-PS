# include <stdio.h>
# include <stdlib.h>
# include <ncurses.h>
# include "pecas.h"
# include "engine.h"

int main(){
    Tela *interfaceJogo;
    peca* Peca = NULL;
    int i=0, movimento, tecla=0 , tempo;
    
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
        move_peca(Peca, interfaceJogo, movimento);

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

