#include <stdio.h>    // Primeiro as dependências do módulo que está sendo testado;
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h" // Aqui as bibliotecas CUnit necessárias para rodar o teste;
#include "CUnit/Basic.h"

#include "engine.c" // Este é o escopo que estará sobre julgo nesses testes
#include "tela.c"

void adicionar_suite(void);


void Teste_da_criacao_de_Tela(void){
/*Este teste verificará se a estrutura foi criada corretamente
e também se seus valores foram preenchidos como esperado*/

	int pontuacao, gameOver, pecaEncaixada;

	Tela* telaTeste;

	telaTeste = malloc(sizeof(Tela));

	telaTeste = cria_tela(); // Primeira etapa para saber se retorna um tipo Tela

	pontuacao = telaTeste->cont_pontuacao;
	gameOver = telaTeste->Game_over;
	pecaEncaixada = telaTeste->peca_encaixada;

	CU_ASSERT_TRUE( !pontuacao ); // verifica se Pontuação é igual a 0
	CU_ASSERT_TRUE( !gameOver ); // verifica se Game Over é igual a 0
	CU_ASSERT_TRUE( !pecaEncaixada ); // verifica se Peça Encaixada é igual a 0

}

void Teste_Do_Imput_Das_Setas(void){
	int setaEsquerda, setaDireita, setaBaixo;

	setaEsquerda = KEY_LEFT;
	setaDireita = KEY_RIGHT;
	setaBaixo = KEY_DOWN;

	CU_ASSERT_EQUAL(    setaBaixo, pega_input( KEY_DOWN) ); 
	CU_ASSERT_EQUAL( setaEsquerda, pega_input( KEY_LEFT) ); //Verifica se a função está capturando corretamente sua condição de saída
	CU_ASSERT_EQUAL(  setaDireita, pega_input(KEY_RIGHT) );

}

void  adicionar_suite(void){
	CU_pSuite suiteEngine;
	CU_pSuite suiteTela;
	
	/*Cria suites que conterão todos os testes*/
	suiteTela = CU_add_suite("Testes da Tela",NULL,NULL);
	suiteEngine = CU_add_suite("Testes da Engine",NULL,NULL);
	
	
	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suiteTela, Teste_da_criacao_de_Tela );
	CU_ADD_TEST(suiteEngine, Teste_Do_Imput_Das_Setas);

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