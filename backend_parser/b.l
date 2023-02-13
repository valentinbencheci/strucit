%{
#include <stdio.h>
#include "y.tab.h"
void yyerror(char*);
int comacc = 0;
int yylineno;
%}

D                       [0-9] 
L                       [a-zA-Z_] 
com                     \/\*.*\*\/

%x ML_COMMENT


%%
"const"                 { return CONST; }
"extern"                { return EXTERN; }
"goto"                  { return GOTO; }
"if"                    { return IF; }
"int"                   { return INT; }
"return"                { return RETURN; }
"void"                  { return VOID; }


{L}({L}|{D})*           {strcpy(yylval.name,yytext); return IDENTIFIER; }

{D}+                    { return CONST; }
L?'(\\.|[^\\'])+'       {} /* pas trop compris celle là
# any of (letter, uppercase, one of "_"), optional, literally "'",
capture (any of ((backslash, anything), none of \\'))
, once or more */
{com}                   {}
"/*"                    { printf("comment from line %d ", yylineno); BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"        { printf("to line %d\n", (yylineno+comacc)); BEGIN(INITIAL); }
<ML_COMMENT>[^*\n]+		
<ML_COMMENT>"*"			
<ML_COMMENT>"\n"        { comacc+=1;}

"<"                     { return LT_OP; }
"<="                    { return LE_OP; }
">"                     { return GT_OP; }
">="                    { return GE_OP; }
"=="                    { return EQ_OP; }
"!="                    { return NE_OP; }
"*"                     { return STAR;}
"+"                     { return PLUS;}
"-"                     { return MINUS;}
"/"                     { return SLASH;}
"("                     { return LPAR; }
")"                     { return RPAR; }
";"                     { return SEMI; }
"{"                     { return LBR; }
"}"                     { return RBR; }
"="                     { return EG; }
":"                     { return COL; }
","                     { return COMMA;}
"&"                     { return COMAND;}


"\n"                    { yylineno++; }

[ \t\v\n\f]             { }
.                       { printf("%s",yytext);}
%%

int yywrap (void) {
    return 1;
}
