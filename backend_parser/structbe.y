%{
#include <stdio.h>
#include <stdlib.h>
int yylex(void);
int yyerror(char* msg);
extern FILE *fp;
extern FILE* yyin;
extern int yylineno;
extern char yytext[];
extern int comacc;
%}


%token IDENTIFIER
%token LE_OP GE_OP EQ_OP NE_OP
%token EXTERN
%token INT VOID
%token IF RETURN GOTO

%token LT_OP GT_OP EG
%token CONST
%token STAR PLUS MINUS SLASH
%token LPAR RPAR RBR LBR
%token SEMI COL COMMA COMAND
%union {
        char name[150];
}

%start program
%%

primary_expression
        : IDENTIFIER                    {printf("Identifier %s encountered\n", yylval.name);}
        | CONST
        ;

postfix_expression
        : primary_expression
        | postfix_expression LPAR RPAR
        | postfix_expression LPAR argument_expression_list RPAR
        ;

argument_expression_list
        : primary_expression
        | argument_expression_list COMMA primary_expression
        ;

unary_expression
        : postfix_expression
        | unary_operator primary_expression
        ;

unary_operator
        : COMAND
        | STAR
        | MINUS
        ;

multiplicative_expression
        : unary_expression
        | primary_expression STAR primary_expression
        | primary_expression SLASH primary_expression
        ;

additive_expression
        : multiplicative_expression
        | primary_expression PLUS primary_expression
        | primary_expression MINUS primary_expression
        ;

relational_expression
        : additive_expression
        | primary_expression LT_OP primary_expression
        | primary_expression GT_OP primary_expression
        | primary_expression LE_OP primary_expression
        | primary_expression GE_OP primary_expression
        ;

equality_expression
        : relational_expression
        | primary_expression EQ_OP primary_expression
        | primary_expression NE_OP primary_expression
        ;

expression
        : equality_expression
        | unary_operator primary_expression EG primary_expression
        | primary_expression EG additive_expression
        ;

declaration
        : declaration_specifiers declarator SEMI
        ;

declaration_specifiers
        : EXTERN type_specifier
        | type_specifier
        ;

type_specifier
        : VOID {printf("Type void\n");}
        | INT   {printf("Type int\n");}
        ;

declarator
        : STAR direct_declarator
        | direct_declarator
        ;

direct_declarator
        : IDENTIFIER                    
        | direct_declarator LPAR parameter_list RPAR
        | direct_declarator LPAR RPAR
        ;

parameter_list
        : parameter_declaration
        | parameter_list COMMA parameter_declaration
        ;

parameter_declaration
        : declaration_specifiers declarator
        ;

statement
        : compound_statement
        | labeled_statement
        | expression_statement
        | selection_statement
        | jump_statement 
        ;

compound_statement
        : LBR RBR
        | LBR statement_list RBR
        | LBR declaration_list RBR
        | LBR declaration_list statement_list RBR
        ;

declaration_list
        : declaration
        | declaration_list declaration
        ;

statement_list
        : statement
        | statement_list statement
        ;

labeled_statement
        : IDENTIFIER COL statement
        ;

expression_statement
        : SEMI
        | expression SEMI
        ;

selection_statement
        : IF LPAR equality_expression RPAR GOTO IDENTIFIER SEMI
        ;
jump_statement
        : RETURN SEMI
        | RETURN expression SEMI
        | GOTO IDENTIFIER SEMI
        ;

program
        : external_declaration
        | program external_declaration
        ;

external_declaration
        : function_definition
        | declaration
        ;

function_definition
        : declaration_specifiers declarator compound_statement
        ;

%%
int yyerror(char *msg)
{       
    printf("Line no: %d Error message: %s Token: %s\n", (yylineno+comacc), msg, yytext);
    return 1;
}

int main(int argc, char* argv[]){
	// "exemples/exemple-strucit-backend.c"
	yyin = fopen(argv[1],"r");
	if (yyin == NULL) {
		printf("file not found: %s!\n", argv[1]);
		return 1;
	}
	if(!yyparse())
		printf("Parsing complete\n");
	else
		printf("Parsing failed\n");
	fclose(yyin);
	return 0;
}
