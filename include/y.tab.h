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

#ifndef YY_YY_Y_TAB_H_INCLUDED
# define YY_YY_Y_TAB_H_INCLUDED
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
    ID = 258,
    CON = 259,
    STR = 260,
    CHAR = 261,
    ELSE = 262,
    FLOAT = 263,
    DOUBLE = 264,
    FOR = 265,
    IF = 266,
    INT = 267,
    RESERVED = 268,
    RETURN = 269,
    WHILE = 270,
    DO = 271,
    CONTINUE = 272,
    BREAK = 273,
    GOTO = 274,
    LVAL = 275,
    SET = 276,
    SETOR = 277,
    SETXOR = 278,
    SETAND = 279,
    SETLSH = 280,
    SETRSH = 281,
    SETADD = 282,
    SETSUB = 283,
    SETMUL = 284,
    SETDIV = 285,
    SETMOD = 286,
    OR = 287,
    AND = 288,
    BITOR = 289,
    BITXOR = 290,
    BITAND = 291,
    EQ = 292,
    NE = 293,
    GT = 294,
    GE = 295,
    LT = 296,
    LE = 297,
    LSH = 298,
    RSH = 299,
    ADD = 300,
    SUB = 301,
    MUL = 302,
    DIV = 303,
    MOD = 304,
    UNARY = 305,
    NOT = 306,
    COM = 307
  };
#endif
/* Tokens.  */
#define ID 258
#define CON 259
#define STR 260
#define CHAR 261
#define ELSE 262
#define FLOAT 263
#define DOUBLE 264
#define FOR 265
#define IF 266
#define INT 267
#define RESERVED 268
#define RETURN 269
#define WHILE 270
#define DO 271
#define CONTINUE 272
#define BREAK 273
#define GOTO 274
#define LVAL 275
#define SET 276
#define SETOR 277
#define SETXOR 278
#define SETAND 279
#define SETLSH 280
#define SETRSH 281
#define SETADD 282
#define SETSUB 283
#define SETMUL 284
#define SETDIV 285
#define SETMOD 286
#define OR 287
#define AND 288
#define BITOR 289
#define BITXOR 290
#define BITAND 291
#define EQ 292
#define NE 293
#define GT 294
#define GE 295
#define LT 296
#define LE 297
#define LSH 298
#define RSH 299
#define ADD 300
#define SUB 301
#define MUL 302
#define DIV 303
#define MOD 304
#define UNARY 305
#define NOT 306
#define COM 307

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED

union YYSTYPE
{
#line 33 "cgram.y" /* yacc.c:1909  */

    int inttype;
    char *str_ptr;
    struct sem_rec *rec_ptr;
    struct id_entry *id_ptr;

#line 165 "y.tab.h" /* yacc.c:1909  */
};

typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_Y_TAB_H_INCLUDED  */
