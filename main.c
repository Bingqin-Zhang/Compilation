/* file TP.c :: limited to yyparse() call and printed result */
/* compilation: gcc -o main main.c parseur.tab.c lex.yy.c */
/* result: main = syntaxic analysis */
/* usage: ./main < input.txt */

#include <string.h>
#include <stdio.h>	/* printf */
#include <stdlib.h>	/* exit */
#include "parseur.tab.h"/* header for TOKEN */
#include "AST.c"	/* AST fonctions */

extern FILE  *yyin;

char* extract_name(char* c);
void completion(char* file);
int countline(char* file, char* str);
int exist(char* file, char* str);

int main(int argc, char **argv){
  if(argc>1){
      if((yyin = fopen(argv[1],"r")) == NULL){
          exit(1);
      }
      
      char* file = extract_name(argv[1]);
      char aux[3] = "jsm";
      strcat(file,aux);
      
      AST t;        /* &t allows to modifie the tree */
      if ((yyparse(&t)==0)) {     /* yyparse calls yylex */
        printf("\nParsing:: syntax OK\n\n");/* reached if parsing folllows the grammar */
        /* print the obtained tree */
        if (t->left!=NULL) printf("Root symbol:: %c\n", t->car);  /* check if car at root */
        printAST(t); 
        printf("\n");
        
        FILE* fp = fopen(file,"a");
        fclose(fp);
        fp =NULL;
        
        codeFile(t,"temp.jsm");

        completion(file);
        
        printf("Halt\n");
        remove("temp.jsm");
        
        free(file);
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

void completion(char* file){
    char ch;
    char temp[] = "temp.jsm";
	FILE* pfr = fopen(temp, "r");
	FILE* pfw = fopen(file, "w");
 
	if (NULL == pfw)
	{
		perror("open file temp.jsm");
	}
 
	if (NULL == pfr)
	{
		perror("open file");
	}
    int line = 0;
	int lineConJmp = 0;
    int lineJump = 0;
    int i;
    
    if((exist(temp,"ConJmp\n")) != 0 ){
        lineConJmp = countline(temp,"ConJmp");
        lineJump = countline(temp,"Jump");
        
        while((ch=fgetc(pfr))!=EOF) {
            if((ch=='\n')){
                if(line == lineConJmp){
                    char tmp[1000000];
                    sprintf(tmp,"%d",count_if);
                    fputc(' ',pfw);
                    for(i=0;i<strlen(tmp);i++){
                        fputc(tmp[i],pfw);
                    }
                }
                if(line == lineJump){
                    char tmp[1000000];     
                    sprintf(tmp,"%d",count_else);
                    fputc(' ',pfw);
                    for(i=0;i<strlen(tmp);i++){
                        fputc(tmp[i],pfw);
                    }
                }
                line++;
            }
            fputc(ch,pfw);
	    }
    }
    char str[] ="Halt";
    fprintf(pfw,"%s\n",str);
	
	fclose(pfr);
	fclose(pfw);
	pfr = NULL;
	pfw = NULL;
	return ;
}


int countline(char* file, char* str){
    FILE* fp = fopen(file,"r");
    if(fp==NULL){
        perror("Incorrect file or file name !");
    }
    int line = 0;
    int i=0;
    char c[strlen(str)+1];
    //char string[strlen(str)+1];
    char c1[strlen(str)+1];


    while((fgets(c,strlen(str)+1,fp)) != NULL){
        if(strchr(c,'\n')){
                line++;
        }
        strncpy(c1,c,strlen(str)+1);
        if(strcmp(c1,str) == 0){
            fclose(fp);
            return line++;
        }
    }

    fclose(fp);
    return -1;
}

int exist(char* file, char* str){
    FILE* fp = fopen(file,"r");
    if(fp==NULL){
        perror("Incorrect file or file name !");
    }
    char c[strlen(str)+1];
    while((fgets(c,strlen(str)+1,fp)) != NULL){
        if(strcmp(c,str) == 0){
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}









