#include "tela.h"

//orientação da peça
#define HORIZONTAL 0
#define VERTICAL 1

typedef struct{
    int tamanho;
    int orientacao;
    int posicao_x_inicial;
    int posicao_y_inicial;
    int cor;
}peca;

void nova_peca(peca* peca, Tela* tela);
void escrevePeca(peca* peca, Tela* tela);
void move_peca(peca* peca, Tela *tela, int movimento);
void move_peca_x(peca* peca, Tela* tela, int x);
void move_peca_y(peca* peca, Tela* tela, int y);
void limpa_peca(peca* peca,Tela* tela);
void testa_limite(peca* peca,Tela* tela);
