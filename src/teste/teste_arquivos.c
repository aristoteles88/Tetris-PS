#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "placar.c"

void adicionar_suite(void);

/*Abaixo estão as funções que efetuam os testes de arquivo
/** Função cria_placar
*/
void teste_DT_Arquivo_Vazio(void);
void teste_DT_Cria_Placar(void);

void teste_DT_Arquivo_Vazio(void){
  FILE *fp;
  char c;

  fp = fopen("placar.txt", "w");

  c = fgetc(fp);
  if( ferror(fp) )
  {
     printf("Arquivo placar.txt vazio!\n");
  }
  //clearerr(fp);
  fclose(fp);
  CU_ASSERT_TRUE( !c );
}

void teste_DT_Cria_Placar(void){
  
}

void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da smo_datas",NULL,NULL);


	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_DT_Arquivo_Vazio);
  CU_ADD_TEST(suite, teste_DT_Cria_Placar);
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
