%{
	
#include <stdio.h>
#include "yatypes.h"
#include "latex.h"

extern int yylineno;
extern FILE *yyin;
extern char *yytext;

int yylex (void);
void yyerror (char const *);

%}

%union
{
	int ival;
	double dval;
	char *str;
	t_decls decls;
	t_decl decl;
	t_argdefs argdefs;
	t_argdef argdef;
	t_args args;
	t_ids ids;
	t_stms stms;
	t_stm stm;
	t_type type;
	t_exp exp;
}

%token <ival> INTLIT BOOLLIT
%token <dval> FLOATLIT
%token <str> STRLIT ID

%token COLON

%token DEFINE RETURN STRUCT WHILE IF THEN ELSE DO NEXT BREAK PRINT

%token T_INT T_FLOAT T_STRING T_BOOL T_VOID

%left SEMI

%right ASSIGN

%left COMMA

%left OR
%left AND
%left NOT

%nonassoc EQ NEQ GT GEQ LT LEQ

%left SUB ADD
%left MUL DIV MOD
%right POW
%left NEG

%nonassoc LCBRACE RCBRACE
%nonassoc LSBRACE RSBRACE
%nonassoc LPAR RPAR

%type	<decls>		decls
%type	<decl>		decl
%type	<argdefs>	argdefs
%type	<argdef>	argdef
%type	<args>		args
%type	<ids>		ids
%type	<stms>		stms
%type	<stm>		stm
%type	<type>		type
%type	<exp>		exp

%%

program: /* empty */	{print_prologue(); printf("[.program [.$empty$ ] ]"); print_epilogue();}
	| decls				{print_prologue(); printf("[.program "); t_decls_print($1); printf(" ]\n"); print_epilogue();}
		;

decls: decl				{$$ = t_decls_new($1, NULL);}
	| decl decls		{$$ = t_decls_new($1, $2);}
		;

decl: ids COLON type SEMI	{$$ = t_decl_new_var($1, $3, NULL);}
	| ids COLON type ASSIGN exp SEMI	{$$ = t_decl_new_var($1, $3, $5);}
	| ID LPAR RPAR COLON type LCBRACE stms RCBRACE SEMI	{$$ = t_decl_new_func($1, NULL, $5, $7);}
	| ID LPAR argdefs RPAR COLON type LCBRACE stms RCBRACE SEMI	{$$ = t_decl_new_func($1, $3, $6, $8);}
	| DEFINE ID type SEMI	{$$ = t_decl_new_define($2, $3);}
		;

argdefs: argdef				{$$ = t_argdefs_new($1, NULL);}
	| argdef COMMA argdefs	{$$ = t_argdefs_new($1, $3);}
		;

argdef: ID COLON type	{$$ = t_argdef_new($1, $3);}
        ;

args: exp				{$$ = t_args_new($1, NULL);}
	| exp COMMA args	{$$ = t_args_new($1, $3);}
		;

ids: ID					{$$ = t_ids_new($1, NULL);}
	| ID COMMA ids		{$$ = t_ids_new($1, $3);}
		;

stms: stm				{$$ = t_stms_new($1, NULL);}
	| stm stms			{$$ = t_stms_new($1, $2);}
		;

stm: decl	{$$ = t_stm_new_decl($1);}
	| exp SEMI	{$$ = t_stm_new_exp($1);}
	| RETURN exp SEMI	{$$ = t_stm_new_return($2);}
	| IF exp THEN LCBRACE stms RCBRACE SEMI	{$$ = t_stm_new_ifelse($2, $5, NULL);}
	| IF exp THEN LCBRACE stms RCBRACE ELSE LCBRACE stms RCBRACE SEMI {$$ = t_stm_new_ifelse($2, $5, $9);}
	| WHILE exp DO LCBRACE stms RCBRACE SEMI	{$$ = t_stm_new_while($2, $5);}
	| NEXT	{$$ = t_stm_new_next();}
		;

type: T_INT							{$$ = t_type_new("int");}
	| T_FLOAT						{$$ = t_type_new("float");}
	| T_STRING						{$$ = t_type_new("string");}
	| T_BOOL						{$$ = t_type_new("bool");}
	| T_VOID						{$$ = t_type_new("void");}
	| ID							{$$ = t_type_new_id($1);}
	| type LSBRACE INTLIT RSBRACE	{$$ = t_type_new_array($1, $3);}
		;

exp: INTLIT							{$$ = t_exp_new_intlit($1);}
	| FLOATLIT						{$$ = t_exp_new_floatlit($1);}
	| STRLIT						{$$ = t_exp_new_stringlit($1);}
	| BOOLLIT						{$$ = t_exp_new_boollit($1);}
	| ID							{$$ = t_exp_new_id($1);}
	| exp LSBRACE INTLIT RSBRACE	{$$ = t_exp_new_array($1, $3);}
	| exp ADD exp					{$$ = t_exp_new_op("+", $1, $3);}
	| exp SUB exp					{$$ = t_exp_new_op("-", $1, $3);}
	| exp MUL exp					{$$ = t_exp_new_op("*", $1, $3);}
	| exp DIV exp					{$$ = t_exp_new_op("/", $1, $3);}
	| exp POW exp					{$$ = t_exp_new_op("^", $1, $3);}
	| exp MOD exp					{$$ = t_exp_new_op("%", $1, $3);}
	| exp GT exp					{$$ = t_exp_new_op(">", $1, $3);}
	| exp LT exp					{$$ = t_exp_new_op("<", $1, $3);}
	| exp GEQ exp					{$$ = t_exp_new_op(">=", $1, $3);}
	| exp LEQ exp					{$$ = t_exp_new_op("*", $1, $3);}
	| exp EQ exp					{$$ = t_exp_new_op("==", $1, $3);}
	| exp NEQ exp					{$$ = t_exp_new_op("!=", $1, $3);}
	| exp AND exp					{$$ = t_exp_new_op("AND", $1, $3);}
	| exp OR exp					{$$ = t_exp_new_op("OR", $1, $3);}
	| NOT exp						{$$ = t_exp_new_op("NOT", $2, NULL);}
	| SUB exp %prec NEG				{$$ = t_exp_new_op("-", $2, NULL);}
	| LPAR exp RPAR					{$$ = t_exp_new_op("( )", $2, NULL);}
	| ID LPAR RPAR					{$$ = t_exp_new_func($1, NULL);}
	| ID LPAR args RPAR				{$$ = t_exp_new_func($1, $3);}
	| exp ASSIGN exp				{$$ = t_exp_new_assign($1, $3);}
	| PRINT LPAR args RPAR			{$$ = t_exp_new_print($3);}
		;

%%


void yyerror (char const *s)
{
	fprintf(stderr, "Syntax error at line %d at or near \"%s\"\n", yylineno,yytext);
}

int main(int argc, char **argv)
{
	++argv, --argc;

	if(argc>0)
	{
		yyin = fopen(argv[0], "r");
	} else {
		yyin = stdin;
	}

	return yyparse();
}
