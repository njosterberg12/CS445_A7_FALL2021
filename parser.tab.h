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

#ifndef YY_YY_PARSER_TAB_H_INCLUDED
# define YY_YY_PARSER_TAB_H_INCLUDED
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
    BOOL = 258,
    NUMCONST = 259,
    CHARCONST = 260,
    STRINGCONST = 261,
    ID = 262,
    STATIC = 263,
    BOOLKW = 264,
    CHAR = 265,
    INT = 266,
    IF = 267,
    THEN = 268,
    ELSE = 269,
    WHILE = 270,
    DO = 271,
    FOR = 272,
    TO = 273,
    BY = 274,
    RETURN = 275,
    BREAK = 276,
    OR = 277,
    AND = 278,
    NOT = 279,
    NEQ = 280,
    GEQ = 281,
    LEQ = 282,
    INC = 283,
    DEC = 284,
    ADDASS = 285,
    SUBASS = 286,
    MULASS = 287,
    DIVASS = 288,
    ASGN = 289,
    EQ = 290,
    LQ = 291,
    GQ = 292,
    PLUS = 293,
    MINUS = 294,
    STAR = 295,
    DIV = 296,
    MOD = 297,
    LPAREN = 298,
    RPAREN = 299,
    SEMICOLON = 300,
    COMMA = 301,
    COLON = 302,
    QMARK = 303,
    LBRACKET = 304,
    RBRACKET = 305,
    LBRACE = 306,
    RBRACE = 307
  };
#endif

/* Value type.  */
#if ! defined YYSTYPE && ! defined YYSTYPE_IS_DECLARED
union YYSTYPE
{
#line 52 "parser.y"

   ExpType type;           // For passing types (ie pass a type in a decl like int or bool)
   TokenData *tokenData;   // For terminals. Token data comes from yylex() in the $ vars
   TreeNode *tree;        // For nonterminals. Add these nodes as you build the tree.

#line 116 "parser.tab.h"

};
typedef union YYSTYPE YYSTYPE;
# define YYSTYPE_IS_TRIVIAL 1
# define YYSTYPE_IS_DECLARED 1
#endif


extern YYSTYPE yylval;

int yyparse (void);

#endif /* !YY_YY_PARSER_TAB_H_INCLUDED  */
