FILE = main.c parseur.tab.c lex.yy.c
FLEX = flex
BISON = bison -d
CC = gcc

all: $(FILE)
	$(CC) $(FILE) -o main

lex.yy.c: lexeur.l
	$(FLEX) lexeur.l

parseur.tab.c: parseur.y lexeur.l
	$(BISON) parseur.y

clean:
	rm -rf *.o lex.yy.c parseur.tab.c parseur.tab.h
