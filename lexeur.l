/* file lexeur.l */ 
/* compilation: flex lexeur.l */
/* result: lex.yy.c = lexical analyser in C */

%x COMMENT
%{
 #include <stdio.h>       /* printf */
 #include "parseur.tab.h" /* token constants def. in parseur.y via #define */
%}

%%
"True"|"False" 				{ printf("lex::BOOLEAN %s\n",yytext); yylval.str=yytext; return BOOLEAN; }
[0-9]+|[0-9]*\.[0-9]+|"NaN"           { printf("lex::NOMBRE %s\n",yytext); yylval.str=yytext; return NOMBRE; }
[0-9]*\.[0-9]+[e][-]?[0-9]+ { printf("lex::NOMBRE %s\n",yytext); yylval.str=yytext; return NOMBRE; }
"=="						{ printf("lex::EQUAL %s\n",yytext); yylval.str=yytext; return EQUAL; }
"!="						{ printf("lex::NotEQUAL %s\n",yytext); yylval.str=yytext; return NotEQUAL; }
"<="						{ printf("lex::LoEqNb %s\n",yytext); yylval.str=yytext; return LoEqNb; }
">="						{ printf("lex::GrEqNb %s\n",yytext); yylval.str=yytext; return GrEqNb; }
"++"						{ printf("lex::++ \n" ); yylval.str=yytext; return PLUSPLUS; }
[a-z][a-zA-Z_0-9-]* 		{ printf("lex::IDENT %s\n",yytext); yylval.str=yytext; return IDENT; }
[ \t\n] 	        		{ ; }     /* ignore space, tab, and line return */

"//".* {}
"/*" {BEGIN COMMENT;}
<COMMENT>\n {}
<COMMENT>"*/" {BEGIN INITIAL;}
<COMMENT>. {}

;                   		{ printf("lex::PT_VIRG %s\n", yytext); return yytext[0]; }
. 		            		{ printf("lex::char %s\n",yytext); return yytext[0]; } /* other one-char = token, ex. '+' */

%%

