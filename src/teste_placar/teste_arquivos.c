#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ncurses.h>

#include "CUnit/CUnit.h"
#include "CUnit/Basic.h"
#include "../placar.c"

void adicionar_suite(void);

/*Abaixo estão as funções que efetuam os testes de arquivo
/** Função cria_placar
*/
void teste_DT_Arquivo_Vazio(void);
void teste_DT_Arquivo_Cheio(void);

/**
 * Instancia um tipo arquivo vazio e o submete à analise da funcao verifica_placar()
 * Caso o arquivo esteja vazio o teste tera sucesso.
 *  @param void
 *  @return void
 */
void teste_DT_Arquivo_Vazio(void){
  FILE *fp;
  int result;

  if (!(fp = fopen("placar.txt", "r+"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(0);
  }

  result = verifica_placar(fp);

  fclose(fp);
  CU_ASSERT_EQUAL(result, 0);
}


/**
 * Instancia um tipo arquivo com 5 linhas e o submete à analise da funcao verifica_placar()
 * Caso o arquivo esteja cheio o teste tera sucesso e a quantidade de linhas do arquivo
 * é impressa.
 *  @param void
 *  @return void
 */
void teste_DT_Arquivo_Cheio(void){
  FILE *fp;
  int result;

  if (!(fp = fopen("placar2.txt", "r+"))){
        printf("Erro! Impossivel abrir o arquivo!\n");
        exit(0);
  }

  result = verifica_placar(fp);
  printf("Arquivo possui %d linhas!\t", result);

  fclose(fp);
  CU_ASSERT_NOT_EQUAL(result, 0);
}

void  adicionar_suite(void){
	CU_pSuite suite;

	/*Cria uma suite que conterá todos os testes*/
	suite = CU_add_suite("Testes da smo_datas",NULL,NULL);


	/*Adiciona os testes para a função DT_data_valida*/
	CU_ADD_TEST(suite, teste_DT_Arquivo_Vazio);
  CU_ADD_TEST(suite, teste_DT_Arquivo_Cheio);
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
