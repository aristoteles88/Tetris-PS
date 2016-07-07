#include <stdio.h>    // Primeiro as dependências do módulo que está sendo testado;
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h" // Aqui as bibliotecas CUnit necessárias para rodar o teste;
#include "CUnit/Basic.h"

#include "placar.c"


void adicionar_suite(void);

void Teste_criacao_placar(void){
  /*Este teste verificará se a estrutura foi criada corretamente
  e também se seus valores foram preenchidos como esperado*/

  	int pontos, tempo, i;
    char player[20];

  	cria_placar();

    for (i = 0; i < 5; i++){
    	pontos = pontuacao[i].pontos;
    	tempo = pontuacao[i].tempo;
    	strncpy(player, pontuacao[i].player, 20);

    	CU_ASSERT_TRUE( !pontos ); // verifica se Pontuação é igual a 0
    	CU_ASSERT_TRUE( !tempo ); // verifica se tempo é igual a 0
    	CU_ASSERT_EQUAL(  player, "-" ); // verifica se player é igual ao caractere de inicialização "-"
    }

}

void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da engine",NULL,NULL);


	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, Teste_Do_Imput_Das_Setas /*Coloque aqui o nome da função a ser testada*/ );

}



int main(void){
	/*Inicializa o registro de suítes e testes do CUnit*/
	if (CUE_SUCCESS != CU_initialize_registry())
    		return CU_get_error();

    	/*Adiciona os testes ao registro*/
   	adicionar_suite();

	/*Muda o modo do CUnit para o modo VERBOSE
	 O modo VERBOSE mostra algumas informacoes a
	 mais na hora da execucao. Outras opções: NORMAL e SILENT*/
	CU_basic_set_mode(CU_BRM_VERBOSE);

	/*Roda os testes e mostra na tela os resultados*/
	CU_basic_run_tests();
	//CU_console_run_tests();
	//CU_automated_run_tests();


	/*Limpa o registro*/
	CU_cleanup_registry();

	return CU_get_error();
}
