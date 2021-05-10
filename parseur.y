/* file parseur.y */
/* compilation: bison -d parseur.y */
/* result: parseur.tab.c = C code for syntaxic analyser */
/* result: parseur.tab.h = def. of lexical units aka lexems */

/* comlements: https://www.gnu.org/software/bison/manual/html_node/Parser-Function.html */
/* about implicit call: https://stackoverflow.com/questions/20106574/simple-yacc-grammars-give-an-error */

%{
 #include <stdio.h>	/* printf REMOVE AFTER TEST */
 #include "AST.h"
 #include <string.h>
 int yylex(void);	/* flex with -Wall (implicite call) */
 int yyerror(struct _tree**, const char*); /* same for bison */
%}

%parse-param {struct _tree* *pT} // yyparse(&t) call => *pT = *(&t) = t 

%union {
  struct _tree* exp;
  char* str;
} ;

%type  <exp> expression
%type  <exp> commande
%type  <exp> programme

%token <str> NOMBRE
%token PT_VIRG
%token <str> BOOLEAN
%token <str> EQUAL
%token <str> IDENT
%token <str> PLUSPLUS
%token <str> OR
%token <str> AND
%token <str> If
%token <str> Else
%token <str> Do
%token <str> While


%left EQUAL NotEQUAL LoEqNb GrEqNb '<' '>'
%left '+' '-' '.' '!' 
%left '*' '/'
%right '=' PLUSPLUS AND OR
%nonassoc MOINSU 
%nonassoc POINT

%%
resultat: programme                                               { *pT = $1; }

programme: 
   commande                                                       { $$ = $1;  }
  | commande programme                                            { $$ = newBinaryAST('P',$1,$2); }
  ;

commande: 
  expression ';'                                                   { $$ = $1; }
  |';'                                                                 {$$ = NULL;}
  |'{' programme '}'                                              { $$ = $2; } 
  | If expression commande Else commande                      { $$ = newBinaryAST ('f',$2, newBinaryAST('e',$3,$5));}
  ;

expression:
   expression  '=' expression                                        { $$ = newBinaryAST('=',$1,$3);   }
  |  expression  OR  expression                                         { $$ = newBinaryAST('|',$1,$3);   }
  | expression  AND expression                                      { $$ = newBinaryAST('&',$1,$3);   }
  | expression EQUAL expression                                       { $$ = newBinaryAST('E',$1,$3);   }
  | expression NotEQUAL expression                                    { $$ = newBinaryAST('N',$1,$3);   }
  | expression LoEqNb expression                                     { $$ = newBinaryAST('L',$1,$3);   }  
  | expression GrEqNb expression                                     { $$ = newBinaryAST('G',$1,$3);   } 
  | expression '<' expression                                        { $$ = newBinaryAST('l',$1,$3);   }  
  | expression '>' expression                                         { $$ = newBinaryAST('g',$1,$3);   } 
  | expression '+' expression	                                      { $$ = newBinaryAST('+',$1,$3);   }
  | expression '-' expression	                                    { $$ = newBinaryAST('-',$1,$3);  }
  | expression '*' expression	                                    { $$ = newBinaryAST('*',$1,$3); }
  | expression '/' expression	                                    { $$ = newBinaryAST('/',$1,$3); }
  |'!' expression                                                 { $$ = newUnaryAST('n', $2 ) ;  } 
  | expression PLUSPLUS                                           { $$ = newUnaryAST('a', $1 ) ;   }
  | '-' expression  %prec MOINSU                                  { $$ = newUnaryAST('-',$2); }
  |'(' expression ')'                                               { $$ = $2; }
  | NOMBRE			                                                  { $$ = newLeafValAST('v',$1);  } 
  | BOOLEAN                                                       { $$ = newUnaryAST('b', newLeafNomAST($1)) ;  } 
  | IDENT                                                        { $$ = newLeafNomAST($1);  } 
  ;

%%

#include <stdio.h>	/* printf */
int yyerror(struct _tree **pT, const char *msg){ printf("Parsing:: syntax error\n"); return 1;}
int yywrap(void){ return 1; } /* stop reading flux yyin */

