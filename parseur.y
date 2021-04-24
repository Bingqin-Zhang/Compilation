/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

%{
    #include <stdio.h>        /* printf */
    int yylex(void);                    /* -Wall : avoid implicit call */
    int yyerror(const char*);           /* same for bison */
%}

%union { double dval; int ival; }

%token <dval> NOMBRE
%type <dval> expression
%start resultat                         /* axiom */


%left '+' '-'
%left '*' '/'
%nonassoc MOINSU


%%

resultat: expression { printf("Resultat= %fd\n", $1); };

expression:
     expression'+'expression            { $$ = $1+$3; }
    | expression'-'expression            { $$ = $1-$3; }
    | expression'*'expression       { $$ = $1*$3; }
    | expression'/'expression       { $$ = $1/$3; }
    |'('expression')'               { $$ = $2; }
    |'-'expression %prec MOINSU     { $$ = -$2; }
    | NOMBRE                        { $$ = $1; }    /* default semantic value */
    ;
    
%%


int yyerror(const char *msg){ 
    printf("Parsing:: syntax error\n");
    return 1;
}

int yywrap(void){ 
    return 1;
}/* stop reading flux yyin */
