#include <stdio.h>    // Primeiro as dependências do módulo que está sendo testado;
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h" // Aqui as bibliotecas CUnit necessárias para rodar o teste;
#include "CUnit/Basic.h"

#include "engine.c" // Este é o escopo que estará sobre julgo nesses testes

void adicionar_suite(void);


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

