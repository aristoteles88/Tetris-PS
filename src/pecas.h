#include "tela.h"

#define QTDE_POSICOES 7
//orientação da peça
#define ORIENTACAO 4

/**
 * Estrutura de dados que armazena o tipo, tamanho, orientacao, posicao e cor das pecas.
 */
typedef struct{
    int tipo;
	int tamanho;
    int orientacao;
    int posicao[ORIENTACAO][QTDE_POSICOES][2];
    int cor;
}peca;

/**
 * Nova peca
 *  @param peca uma peca a ser criada
 *  @param *tela instancia da tela a ser modificada
 *  @return void
 */
void nova_peca(peca* peca, Tela* tela);

/**
 * Escreve peca
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @return void
 */
void escrevePeca(peca* peca, Tela* tela);

/**
 * Rotaciona peca
 *  @param peca uma peca a ser toracionada
 *  @return void
 */
void rotacionaPeca(peca* peca);

/**
 * Move peca
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @param movimento um int correspondendo um movimento
 *  @return void
 */
void move_peca(peca* peca, Tela *tela, int movimento);

/**
 * Move peca na horizontal
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @param movimento um int correspondendo um movimento
 *  @return void
 */
void move_peca_x(peca* peca, Tela* tela, int x);

/**
 * Move peca na vertical
 * @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @param movimento um int correspondendo um movimento
 *  @return void
 */
void move_peca_y(peca* peca, Tela* tela, int y);

/**
 * Limpa peca
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @return void
 */
void limpa_peca(peca* peca,Tela* tela);

/**
 * Testa limite
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @return void
 */
void testa_limite(peca* peca,Tela* tela);

/**
 * Testa colisao horizontal
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @param movimento um int de teste de colisao
 *  @return void
 */
int testaColisaox(peca* Peca, Tela* tela, int orientacao);

/**
 * Testa colisao vertical
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @param movimento um int de teste de colisao
 *  @return void
 */
int testaColisaoy(peca* Peca, Tela* tela, int orientacao);

/**
 * Grava Posicoes Ocupadas
 *  @param peca uma peca
 *  @param *tela instancia da tela a ser modificada
 *  @return void
 */
void gravaPosicoesOcupadas(peca *peca, Tela* tela);
