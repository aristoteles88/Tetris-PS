all: msgola programa limpa rodaprograma
msgola:  
	@echo Bem vindo ao makefile. Vou tentar executar o programa. 
programa: main.o tela.o pecas.o engine.o
	gcc -std=c99 -g main.o tela.o pecas.o engine.o -o programa -lncurses
main.o: main.c tela.c tela.h pecas.c pecas.h engine.c engine.h
	gcc -std=c99 -g -c main.c -lncurses
engine.o: engine.c engine.h
	gcc -g -c engine.c -lncurses
tela.o: tela.c tela.h
	gcc -std=c99 -g -c tela.c -lncurses
pecas.o: pecas.c pecas.h tela.c tela.h
	gcc -std=c99 -g -c pecas.c -lncurses
rodaprograma:
	./programa

Teste : teste gcov 

teste : tela_Teste.c tela.c tela.h
	gcc -g -I./CUnit -L./CUnit tela_Teste.c -lcunit -lncurses -o testeTela
	./testeTela

gcov :	tela.c tela_Teste.c
	gcc -g -Wall -ftest-coverage -fprofile-arcs -I./CUnit -L./CUnit tela_Teste.c -lcunit -lncurses -o teste_gcov
	./teste_gcov

limpa : 
	rm *.o
