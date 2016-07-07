#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "placar.c"

/*
 * Função que adiciona ao registro do CUnit os testes paras as funções
 * presentes no arquivo testes.c
 */
void adicionar_suite(void);


/*Abaixo estão as funções que efetuam os testes
/** Função TestaParidade:
* Entrada	Esperado
* 0			0
* 1			1
* 2			0
* 3			1
* .			.
* .			.
* .			.
*/
void teste_DT_VerificaParidade_Par(void);
void teste_DT_VerificaParidade_Impar(void);
void teste_DT_VerificaParidade_Zero(void);
