/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */
#include <string.h>
#include <stdio.h>                              /* printf */
#include <stdlib.h>                             /* exit */
extern FILE  *yyin;
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */

char* extract_name(char* c);

int main(int argc, char **argv){
  if(argc>1){
      if((yyin = fopen(argv[1],"r")) == NULL){
          exit(1);
      }
      
      char* file = extract_name(argv[1]);
      char aux[3] = "jsm";
      strcat(file,aux);
      
      AST t; 				/* &t allows to modifie the tree */
      if ((yyparse(&t)==0)) { 		/* yyparse calls yylex */
        printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
        
        /* print the obtained tree */
        if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);	/* check if car at root */
        printAST(t); printf("\n");
        code(t,file);
        		
        freeAST(t);
      }
  }
  
  exit(EXIT_SUCCESS);
}

char* extract_name(char* c){
    int n = 0;
    
    for(int i = 0; i<strlen(c); i++){
        n++;
        
        if(c[i] == '.'){
            break;
        }
    }
    char* rst = malloc(sizeof(char)*n);
    strncpy(rst,c,n);
    
    return rst;
}

