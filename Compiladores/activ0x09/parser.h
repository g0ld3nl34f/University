/* A Bison parser, made by GNU Bison 3.0.4.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015 Free Software Foundation, Inc.

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */

/* As a special exception, you may create a larger work that contains
   part or all of the Bison parser skeleton and distribute that work
   under terms of your choice, so long as that work isn't itself a
   parser generator using the skeleton or a modified version thereof
   as a parser skeleton.  Alternatively, if you modify or redistribute
   the parser skeleton itself, you may (at your option) remove this
   special exception, which will cause the skeleton and the resulting
   Bison output files to be licensed under the GNU General Public
   License without this special exception.

   This special exception was added by the Free Software Foundation in
   version 2.2 of Bison.  */

#ifndef YY_YY_PARSER_H_INCLUDED
# define YY_YY_PARSER_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 0
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    INTLIT = 258,
    BOOLLIT = 259,
    FLOATLIT = 260,
    STRLIT = 261,
    ID = 262,
    COLON = 263,
    DEFINE = 264,
    RETURN = 265,
    STRUCT = 266,
    WHILE = 267,
    IF = 268,
    THEN = 269,
    ELSE = 270,
    DO = 271,
    NEXT = 272,
    BREAK = 273,
    PRINT = 274,
    T_INT = 275,
    T_FLOAT = 276,
    T_STRING = 277,
    T_BOOL = 278,
    T_VOID = 279,
    SEMI = 280,
    ASSIGN = 281,
    COMMA = 282,
    OR = 283,
    AND = 284,
    NOT = 285,
    EQ = 286,
    NEQ = 287,
    GT = 288,
    GEQ = 289,
    LT = 290,
    LEQ = 291,
    SUB = 292,
    ADD = 293,
    MUL = 294,
    DIV = 295,
    MOD = 296,
    POW = 297,
    NEG = 298,
    LCBRACE = 299,
    RCBRACE = 300,
    LSBRACE = 301,
    RSBRACE = 302,
    LPAR = 303,
    RPAR = 304
  };
#endif
/* Tokens.  */
#define INTLIT 258
#define BOOLLIT 259
#define FLOATLIT 260
#define STRLIT 261
#define ID 262
#define COLON 263
#define DEFINE 264
#define RETURN 265
#define STRUCT 266
#define WHILE 267
#define IF 268
#define THEN 269
#define ELSE 270
#define DO 271
#define NEXT 272
#define BREAK 273
#define PRINT 274
#define T_INT 275
#define T_FLOAT 276
#define T_STRING 277
#define T_BOOL 278
#define T_VOID 279
#define SEMI 280
#define ASSIGN 281
#define COMMA 282
#define OR 283
#define AND 284
#define NOT 285
#define EQ 286
#define NEQ 287
#define GT 288
#define GEQ 289
#define LT 290
#define LEQ 291
#define SUB 292
#define ADD 293
#define MUL 294
#define DIV 295
#define MOD 296
#define POW 297
#define NEG 298
#define LCBRACE 299
#define RCBRACE 300
#define LSBRACE 301
#define RSBRACE 302
#define LPAR 303
#define RPAR 304

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 17 "yaexclamationmark.y" /* yacc.c:1909  */

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

#line 168 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
