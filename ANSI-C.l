%{
    #include "string.h"
    #include "y.tab.h"

    int comacc = 0;
    int yylineno;
%}

%option yylineno

D                       [0-9] 
L                       [a-zA-Z_] 

%x ML_COMMENT

%%

"else"                  { strcpy(yylval.ndObj.name, (yytext)); return ELSE; }
"extern"                { strcpy(yylval.ndObj.name, (yytext)); return EXTERN; }
"for"                   { strcpy(yylval.ndObj.name, (yytext)); return FOR; }
"if"                    { strcpy(yylval.ndObj.name, (yytext)); return IF; }
"int"                   { strcpy(yylval.ndObj.name, (yytext)); return INT; }
"return"                { strcpy(yylval.ndObj.name, (yytext)); return RETURN; }
"sizeof"                { strcpy(yylval.ndObj.name, (yytext)); return SIZEOF; }
"struct"                { strcpy(yylval.ndObj.name, (yytext)); return STRUCT; }
"void"                  { strcpy(yylval.ndObj.name, (yytext)); return VOID; }
"while"                 { strcpy(yylval.ndObj.name, (yytext)); return WHILE; }

{L}({L}|{D})*           { strcpy(yylval.ndObj.name, (yytext)); return IDENTIFIER; }

{D}+                    { strcpy(yylval.ndObj.name, (yytext)); return CONSTANT; }


"/*"                    { printf("comment from line %d ", yylineno); BEGIN(ML_COMMENT); }
<ML_COMMENT>"*/"        { printf("to line %d\n", (yylineno+comacc)); BEGIN(INITIAL); }
<ML_COMMENT>[^*\n]+		
<ML_COMMENT>"*"			
<ML_COMMENT>"\n"        { comacc+=1;}


"..."                   {}
">>"                    { strcpy(yylval.ndObj.name, (yytext)); return RSHIFT; }
"<<"                    { strcpy(yylval.ndObj.name, (yytext)); return LSHIFT; }
"<"                     { strcpy(yylval.ndObj.name, (yytext)); return LT_OP; }
"<="                    { strcpy(yylval.ndObj.name, (yytext)); return LE_OP; }
">"                     { strcpy(yylval.ndObj.name, (yytext)); return GT_OP; }
">="                    { strcpy(yylval.ndObj.name, (yytext)); return GE_OP; }
"->"                    { strcpy(yylval.ndObj.name, (yytext)); return PTR_OP; }
"&&"                    { strcpy(yylval.ndObj.name, (yytext)); return AND_OP; }
"||"                    { strcpy(yylval.ndObj.name, (yytext)); return OR_OP; }
"=="                    { strcpy(yylval.ndObj.name, (yytext)); return EQ_OP; }
"!="                    { strcpy(yylval.ndObj.name, (yytext)); return NE_OP; }
"*"                     { strcpy(yylval.ndObj.name, (yytext)); return STAR;}
"("                     { strcpy(yylval.ndObj.name, (yytext)); return LPAR; }
")"                     { strcpy(yylval.ndObj.name, (yytext)); return RPAR; }
"+"                     { strcpy(yylval.ndObj.name, (yytext)); return PLUS;}
"-"                     { strcpy(yylval.ndObj.name, (yytext)); return MINUS;}
";"                     { strcpy(yylval.ndObj.name, (yytext)); return SEMI; }
"{"                     { strcpy(yylval.ndObj.name, (yytext)); return LBR; }
"}"                     { strcpy(yylval.ndObj.name, (yytext)); return RBR; }
"="                     { strcpy(yylval.ndObj.name, (yytext)); return EG; }
"&"                     { strcpy(yylval.ndObj.name, (yytext)); return COMAND; }
"/"                     { strcpy(yylval.ndObj.name, (yytext)); return SLASH;}
","                     { strcpy(yylval.ndObj.name, (yytext)); return COMMA; }


[ \t\v\n\f]             { }
.                       { printf("%s", yytext);}

%%
FILE* fp1;
int yywrap (void) {
    return 1;
}
