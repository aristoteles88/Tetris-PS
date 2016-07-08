mode = -std=c99
#mode = -ansi
gcov = -ftest-coverage -fprofile-arcs
lib = -lncurses


placar: ../placar.c ../placar.h teste_arquivos.c
	gcc $(mode) -I./CUnit -L./CUnit teste_arquivos.c -lcunit -o teste_arquivos $(lib)
	./teste_arquivos

placar_gcov: ../placar.c ../placar.h teste_arquivos.c
	gcc $(gcov) -I./CUnit -L./CUnit teste_arquivos.c -lcunit -o teste_arquivos_gcov $(lib)
	./teste_arquivos_gcov


limpa :
	rm *.gcda *.gcno *.gcov
