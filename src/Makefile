all: msgola programa limpa rodaprograma
msgola:  
	@echo Bem vindo ao makefile. Vou tentar executar o programa. 
programa: main.o tela.o pecas.o engine.o
	gcc -g main.o tela.o pecas.o engine.o -o programa -lncurses
main.o: main.c tela.c tela.h pecas.c pecas.h engine.c engine.h
	gcc -g -c main.c -lncurses
engine.o: engine.c engine.h
	gcc -g -c engine.c -lncurses
tela.o: tela.c tela.h
	gcc -g -c tela.c -lncurses
pecas.o: pecas.c pecas.h tela.c tela.h
	gcc -g -c pecas.c -lncurses
rodaprograma:
	./programa
limpa: 
	rm *.o