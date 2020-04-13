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
    T_INT = 274,
    T_FLOAT = 275,
    T_STRING = 276,
    T_BOOL = 277,
    T_VOID = 278,
    SEMI = 279,
    ASSIGN = 280,
    COMMA = 281,
    OR = 282,
    AND = 283,
    NOT = 284,
    EQ = 285,
    NEQ = 286,
    GT = 287,
    GEQ = 288,
    LT = 289,
    LEQ = 290,
    SUB = 291,
    ADD = 292,
    MUL = 293,
    DIV = 294,
    MOD = 295,
    POW = 296,
    NEG = 297,
    LCBRACE = 298,
    RCBRACE = 299,
    LSBRACE = 300,
    RSBRACE = 301,
    LPAR = 302,
    RPAR = 303
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
#define T_INT 274
#define T_FLOAT 275
#define T_STRING 276
#define T_BOOL 277
#define T_VOID 278
#define SEMI 279
#define ASSIGN 280
#define COMMA 281
#define OR 282
#define AND 283
#define NOT 284
#define EQ 285
#define NEQ 286
#define GT 287
#define GEQ 288
#define LT 289
#define LEQ 290
#define SUB 291
#define ADD 292
#define MUL 293
#define DIV 294
#define MOD 295
#define POW 296
#define NEG 297
#define LCBRACE 298
#define RCBRACE 299
#define LSBRACE 300
#define RSBRACE 301
#define LPAR 302
#define RPAR 303

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 15 "yaexclamationmark.y" /* yacc.c:1909  */

	int ival;
	double dval;
	char *str;	

#line 156 "parser.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_H_INCLUDED  */
