#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "AST.h"

#define TAILLE 1000         // On accepte jusqu'a 1000 lignes d'expressions 

int count_if;
int count_else;
int IsElse;


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
AST newLeafValAST(char car,char* nom)
{
    AST t=(struct _tree*) malloc(sizeof(struct _tree));
    if (t!=NULL){ /* malloc ok */
        t->nom=(char*) malloc(sizeof(char)*strlen(nom));
        strcpy(t->nom,nom);
        t->car=car;
        t->left=NULL;
        t->right=NULL;
    }else printf("MALLOC! ");
    return t;
}

AST newLeafNomAST(char* nom)
{
    AST t=(struct _tree*) malloc(sizeof(struct _tree));
    if (t!=NULL){ /* malloc ok */
        t->nom=(char*) malloc(sizeof(char)*strlen(nom));
        strcpy(t->nom,nom);
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
    if (t->car=='v') printf(":%s: ",t->nom);
    if (t->left==NULL && t->nom!=NULL && t->car!='v') printf(":%s: ",t->nom);
    if (t->left!=NULL && t->car!='v') printf(":%c: ",t->car); 
    printAST(t->right);
    printf("] ");
  }
}


void test(int IsElse){
    if(IsElse==1){
        count_if++;
    }
    if(IsElse==2){
        count_else++;
    }
}

void PrintElemFile(AST t, FILE* fp){
    if (t->car=='a'){
        // Si c'est une variable
        if (t->left->car=='v'){
            printf("CstNb 1\n");
            char str[] = "CstNb 1";
            fprintf(fp,"%s\n",str);
            test(IsElse);
            
            printf("AddiNb\n");
            char str1[] = "AddiNb";
            fprintf(fp,"%s\n",str1);
            test(IsElse);
            fclose(fp);
        }
        else{
            printf("CstNb 1 \n");
            char str[] = "CstNb 1";
            fprintf(fp,"%s\n",str);
            test(IsElse);
            
            printf("AddiNb\n");
            char str1[] = "AddiNb";
            fprintf(fp,"%s\n",str1);
            test(IsElse);
            
            printf("SetVar %s\n",t->left->nom);
            char str2[] = "SetVar";
            fprintf(fp,"%s %s\n",str2, t->left->nom);
            test(IsElse);
            fclose(fp);
        }
        return;
    }
    if (t->car == 'L'){
        printf("LoEqNb\n");
        char str[] = "LoEqNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'G'){
        printf("GrEqNb\n");
        char str[] = "GrEqNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'l'){
        printf("LoStNb\n");
        char str[] = "LoStNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'g'){
        printf("GrStNb\n");
        char str[] = "GrStNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'E'){
        printf("Equals\n");
        char str[] = "Equals";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'N'){
        printf("NotEquals\n");
        char str[] = "NotEquals";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }    
    if(t->car == '+'){
        printf("AddiNb\n");
        char str[] = "AddiNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if(t->car == '-'){
        if(t->right == NULL){
            printf("NegaNb\n");
            char str[] = "NegaNb";
            fprintf(fp,"%s\n",str);
            test(IsElse);
            fclose(fp);
        }
        else{
            printf("SubiNb\n");
            char str[] ="SubiNb";
            fprintf(fp,"%s\n",str);
            test(IsElse);
            fclose(fp);
        }
        return;
    }
    if(t->car == '*'){
        printf("MultNb\n");
        char str[] ="MultNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if(t->car == '/'){
        printf("DiviNb\n");
        char str[] ="DiviNb";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if (t->car == 'n'){
        printf("Not\n");
        char str[] ="Not";
        fprintf(fp,"%s\n",str);
        test(IsElse);
        fclose(fp);
    }
    if(t->car=='v'){
        printf("CstNb %s\n", t->nom);
        char str[] = "CstNb";
        fprintf(fp,"%s %s\n",str,t->nom);
        test(IsElse);
        fclose(fp);
        return;
    }
    if(t->nom!=NULL && t->car !='v'){
        printf("GetVar %s\n",t->nom);
        char str[] ="GetVar";
        fprintf(fp,"%s %s\n",str,t->nom);
        test(IsElse);
        fclose(fp);
    }
}

void codeFile(AST t, char* file){
    FILE* fp;
    fp = fopen(file,"a");
    if(fp==NULL){
        perror("Incorrect file or file name !");
    }
    
    if(t!=NULL){
        if(t->car=='f'){
            
            codeFile(t->left, file);
            printf("ConJmp\n");
            char str[] = "ConJmp";
            fprintf(fp,"%s\n",str);
            fclose(fp);
            
            IsElse=1;
            codeFile(t->right->left, file);
            
            codeFile(t->right,file);    
                
            IsElse=2;
            codeFile(t->right->right,file);
            
            return;
        }
        if(t->car=='e'){
            printf("Jump\n");
            char str1[] = "Jump";
            fprintf(fp,"%s\n",str1);
            test(IsElse);
            fclose(fp);
            return;
        }         
    	if(t->car=='='){
    		codeFile(t->right,file);
    		printf("SetVar %s\n", t->left->nom);
    		char str[] ="SetVar";
            fprintf(fp,"%s %s\n",str, t->left->nom);
            test(IsElse);
            fclose(fp);
            return;
    	}
        if (t->car!='b'){

            //printf("lchar=%c,val=%d\n", t->car,t->val);
            codeFile(t->left,file);
            //printf("lchar_out=%c,val=%d\n", t->car,t->val);

            //printf("rchar=%c,val=%d\n", t->car,t->val);
            codeFile(t->right,file);
            //printf("rchar_out=%c,val=%d\n", t->car,t->val);

            //printf("Ele_char=%c,val=%d\n", t->car,t->val);
            PrintElemFile(t, fp);
            //printf("Ele_char_out=%c,val=%d\n", t->car,t->val);
            return;
        }
        if(t->car=='b'){
            printf("CstBo %s\n", t->left->nom);
            char str[] ="CstBo";
            fprintf(fp,"%s %s\n",str, t->left->nom);
            test(IsElse);

            fclose(fp);
        } 

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
