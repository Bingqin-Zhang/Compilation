/* file main.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */
#include <stdio.h>                              /* printf */
#include <stdlib.h>                             /* exit */
extern FILE  *yyin;
#define SIZE 256

//char* read_file(FILE *file);

int main(int argc, char **argv){
    if(argc<2){
        if (yyparse()==0) {                         /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n");      /* reached if parsing folllows the grammar */
        }
    }
    else{
        FILE *file;
        if((file = fopen(argv[1],"r")) == NULL){
            exit(1);
        }
        yyin = file;
        
        if (yyparse()==0) {                         /* yyparse calls yylex */
            printf("\nParsing:: syntax OK\n");      /* reached if parsing folllows the grammar */
        }
        fclose(file);
    }
    
    exit(EXIT_SUCCESS);
}


