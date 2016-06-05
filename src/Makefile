all: msgola programa limpa rodaprograma

teste: engine.o tela.o pecas.o
	gcc -I./CUnit -L./CUnit testes.c tela.o pecas.o engine.o -lcunit -lncurses -o testes -std=c99
	./testes
	rm *.o

msgola:  
	@echo Bem vindo ao makefile. Vou tentar executar o programa. 

programa: main.o tela.o pecas.o engine.o
	gcc -std=c99 main.o tela.o pecas.o engine.o -o programa -lncurses -g

main.o: main.c tela.c tela.h pecas.c pecas.h engine.c engine.h
	gcc -std=c99 -c main.c -lncurses -g

engine.o: engine.c engine.h
	gcc -c engine.c -lncurses -g

tela.o: tela.c tela.h
	gcc -std=c99 -c tela.c -lncurses -g

pecas.o: pecas.c pecas.h tela.c tela.h
	gcc -std=c99 -c pecas.c -lncurses -g

rodaprograma:
	./programa


limpa : 
	rm *.o
