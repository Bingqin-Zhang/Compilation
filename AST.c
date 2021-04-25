#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "AST.h"

/* create an AST from a root value and two AST sons */
AST newBinaryAST(char car, AST left, AST right)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->car=car;
    t->left=left;
    t->right=right;
  } else printf("MALLOC! ");
  return t;
}

/* create an AST from a root value and one AST son */
AST newUnaryAST(char car, AST son)
{
  return newBinaryAST(car, son, NULL);
}

/* create an AST leaf from a value */
AST newLeafAST(int val)
{
  AST t=(struct _tree*) malloc(sizeof(struct _tree));
  if (t!=NULL){	/* malloc ok */
    t->val=val;
    t->left=NULL;
    t->right=NULL;
  } else printf("MALLOC! ");
  return t;
}

/* delete an AST */
void freeAST(AST t)
{
  if (t!=NULL) {
    freeAST(t->left);
    freeAST(t->right);
    free(t);
  }
}

/* infix print an AST*/
void printAST(AST t)
{
  if (t!=NULL) {
    printf("[ ");
    printAST(t->left);
    /* check if node is car|val */
    if (t->left==NULL) printf(":%d: ",t->val); else printf(":%c: ",t->car);
    printAST(t->right);
    printf("] ");
  }
}

void PrintElemFile(AST t, char* file){
    FILE* fp = fopen(file,"a");
    if(fp==NULL){
        perror("Incorrect file or file name !");
    }
    
    if(t->car == '+'){
        printf("AddiNb\n");
        char str[] = "AddiNb\n";
        fwrite(str,sizeof(str),1,fp);
        fclose(fp);
    }
    if(t->car == '-'){
        if(t->right == NULL){
            printf("NegaNb\n");
            char str[] = "NegaNb\n";
            fwrite(str,sizeof(str),1,fp);
            fclose(fp);
        }
        else{
            printf("SubiNb\n");
            char str[] ="SubiNb\n";
            fwrite(str,sizeof(str),1,fp);
            fclose(fp);
        }
    }
    if(t->car == '*'){
        printf("MultNb\n");
        char str[] ="MultNb\n";
        fwrite(str,sizeof(str),1,fp);
        fclose(fp);
    }
    if(t->car == '/'){
        printf("DiviNb\n");
        char str[] ="DiviNb\n";
        fwrite(str,sizeof(str),1,fp);
        fclose(fp);
    }
    if(t->left == NULL && t->right == NULL){
        printf("CstNb %d\n", t->val);
        char val[10];
        snprintf(val,10,"%d", t->val);
        char str[] = "CstNb ";
        strcat(str,val);
        fwrite(str,sizeof(str),1,fp);
        fclose(fp);
    }
}

void codeFile(AST t, char* file){
    if(t!=NULL){
        codeFile(t->left,file);
        codeFile(t->right,file);
        
        PrintElemFile(t, file);
        return;
    }
}

void PrintElem(AST t){
    if(t->car == '+'){
        printf("AddiNb\n");
    }
    if(t->car == '-'){
        if(t->right == NULL){
            printf("NegaNb\n");
        }
        else{
            printf("SubiNb\n");
        }
    }
    if(t->car == '*'){
        printf("MultNb\n");
    }
    if(t->car == '/'){
        printf("DiviNb\n");
    }
    if(t->left == NULL && t->right == NULL){
        printf("CstNb %d\n", t->val);
    }
}

void code(AST t){
    if(t!=NULL){
        code(t->left);
        code(t->right);
        
        PrintElem(t);
        return;
    }
}

