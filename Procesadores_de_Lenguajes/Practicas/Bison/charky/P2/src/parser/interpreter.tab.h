/* A Bison parser, made by GNU Bison 3.5.1.  */

/* Bison interface for Yacc-like parsers in C

   Copyright (C) 1984, 1989-1990, 2000-2015, 2018-2020 Free Software Foundation,
   Inc.

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

/* Undocumented macros, especially those whose name start with YY_,
   are private implementation details.  Do not rely on them.  */

#ifndef YY_YY_INTERPRETER_TAB_H_INCLUDED
# define YY_YY_INTERPRETER_TAB_H_INCLUDED
/* Debug traces.  */
#ifndef YYDEBUG
# define YYDEBUG 1
#endif
#if YYDEBUG
extern int yydebug;
#endif

/* Token type.  */
#ifndef YYTOKENTYPE
# define YYTOKENTYPE
  enum yytokentype
  {
    PLACECURSOR = 258,
    CLEAR = 259,
    SEMICOLON = 260,
    TWO_POINTS = 261,
    ASK_FOR_KEY = 262,
    PRINT = 263,
    READ = 264,
    READ_STRING = 265,
    IF = 266,
    THEN = 267,
    END_IF = 268,
    ELSE = 269,
    WHILE = 270,
    DO = 271,
    END_WHILE = 272,
    DO_WHILE = 273,
    UNTIL = 274,
    FOR = 275,
    FROM = 276,
    STEP = 277,
    END_FOR = 278,
    SWITCH = 279,
    VALUE = 280,
    DEFAULT = 281,
    END_SWITCH = 282,
    LETFCURLYBRACKET = 283,
    RIGHTCURLYBRACKET = 284,
    ASSIGNMENT = 285,
    COMMA = 286,
    NUMBER = 287,
    STRING = 288,
    BOOL = 289,
    VARIABLE = 290,
    UNDEFINED = 291,
    CONSTANT = 292,
    BUILTIN = 293,
    OR = 294,
    AND = 295,
    GREATER_OR_EQUAL = 296,
    LESS_OR_EQUAL = 297,
    GREATER_THAN = 298,
    LESS_THAN = 299,
    EQUAL = 300,
    NOT_EQUAL = 301,
    NOT = 302,
    PLUS = 303,
    MINUS = 304,
    CONCATENATION = 305,
    MULTIPLICATION = 306,
    DIVISION = 307,
    INTEGER_DIVISION = 308,
    MODULO = 309,
    LPAREN = 310,
    RPAREN = 311,
    UNARY = 312,
    POWER = 313
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 80 "interpreter.y"

  char * identifier;
  double number;  
  bool logic;
  lp::ExpNode *expNode;
  std::list<lp::ExpNode *>  *parameters;    // NOTE: #include<list> must be in interpreter.l, init.cpp, interpreter.cpp
  std::list<lp::Statement *> *stmts;
  std::list<lp::Value *> *switchValues;
  lp::Statement *st;
  lp::AST *prog;

#line 128 "interpreter.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_INTERPRETER_TAB_H_INCLUDED  */
