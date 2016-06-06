#include "tela.h"

#define QTDE_POSICOES 7
//orientação da peça
#define ORIENTACAO 4

typedef struct{
    int tipo;
	int tamanho;
    int orientacao;
    int posicao[ORIENTACAO][QTDE_POSICOES][2];
    int cor;
}peca;

void nova_peca(peca* peca, Tela* tela);
void escrevePeca(peca* peca, Tela* tela);
void rotacionaPeca(peca* peca);
void move_peca(peca* peca, Tela *tela, int movimento);
void move_peca_x(peca* peca, Tela* tela, int x);
void move_peca_y(peca* peca, Tela* tela, int y);
void limpa_peca(peca* peca,Tela* tela);
void testa_limite(peca* peca,Tela* tela);
int testaColisao(peca* Peca, Tela* tela, int orientacao);