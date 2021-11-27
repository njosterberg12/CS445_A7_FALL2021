%{
// this *order* of these includes is mandatory
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanType.h" // TokenData Type
#include "treeNodes.h"
#include "parser.tab.h" // token definitions from the bison

extern int numErrors, numWarnings;

int line = 1;

static int char_error(int lineNum, int tokenClass, char* stringVal)
{
   if(strlen(stringVal) - 2 == 0)
   {
      printf("ERROR(%d): Empty character ''\n", lineNum);
      numErrors++;
   }
   else if(strlen(stringVal) - 2 == 1)
   {

   }
   else
   {
      printf("WARNING(%d): character is %zu characters long and not a single character: '%s'. First char used.\n", lineNum, strlen(stringVal) - 2, stringVal);
      numWarnings++;
   }
   printf("LINE %i string %s \n", lineNum, stringVal);
   yylval.tokenData = new TokenData;
   yylval.tokenData->tokenclass = tokenClass;
   stringVal[2] = 39;
   stringVal[3] = 0;

   yylval.tokenData->tokenstr = strdup(stringVal);
   numWarnings++;

   return tokenClass;
}

static int setValue(int linenum, int tokenClass, char *svalue)
{
   // create the pass-back data space
   yylval.tokenData = new TokenData[100];
   yylval.tokenData->tokenclass = tokenClass;
   // fill it up
   yylval.tokenData->linenum = linenum;
   yylval.tokenData->tokenstr = strdup(svalue); // duplicating string

   char kwStatic[7];
   strcpy(kwStatic, "static");
   char kwBool[5];
   strcpy(kwBool, "bool");
   char kwChar[5];
   strcpy(kwChar, "char");
   char kwInt[4];
   strcpy(kwInt, "int");
   char kwIf[3];
   strcpy(kwIf, "if");
   char kwThen[5];
   strcpy(kwThen, "then");
   char kwElse[5];
   strcpy(kwElse, "else");
   char kwWhile[6];
   strcpy(kwWhile, "while");
   char kwDo[3];
   strcpy(kwDo, "do");
   char kwFor[4];
   strcpy(kwFor, "for");
   char kwTo[3];
   strcpy(kwTo, "to");
   char kwBy[3];
   strcpy(kwBy, "by");
   char kwReturn[7];
   strcpy(kwReturn, "return");
   char kwBreak[6];
   strcpy(kwBreak, "break");
   char kwOr[3];
   strcpy(kwOr, "or");
   char kwAnd[4];
   strcpy(kwAnd, "and");
   char kwNot[4];
   strcpy(kwNot, "not");
   char BoolTrue[5];
   strcpy(BoolTrue, "true");
   char BoolFalse[6];
   strcpy(BoolFalse, "false");
   char opAddAss[3];
   strcpy(opAddAss, "+=");
   char opInc[3];
   strcpy(opInc, "++");
   char opAsgn[4];
   strcpy(opAsgn, ":=");

   //yylval.tokenData->svalue = svalue;

   char *tmp = strdup(svalue);
   int w = 1;
   char *fin = tmp;

   //printf("line %d token %s\n", yylval.tokenData->linenum, yylval.tokenData->tokenstr);
   switch(tokenClass)
   {
      case BOOL:
         if(!strcmp(yylval.tokenData->tokenstr, BoolTrue))
         {
            char boolword[5] = "true";
            yylval.tokenData->nvalue = 1;
            for(int i = 0; i < 5; i++)
            {
               yylval.tokenData->svalue[i] = boolword[i];
            }
         }
         if(!strcmp(yylval.tokenData->tokenstr, BoolFalse))
         {
            char boolword[6] = "false";
            yylval.tokenData->nvalue = 0;
            for(int i = 0; i < 6; i++)
            {
               yylval.tokenData->svalue[i] = boolword[i];
            }
         }
         break;
      case NUMCONST:
         yylval.tokenData->nvalue = atof(svalue);
         break;
      case ID:
         //yylval.tokenData->idvalue = svalue[0] - 'a';
         break;
      case CHARCONST:
         //********** 39 = ', 48 = 0, 92 = \, 110 = n
         if(svalue[0] == 39 && svalue[strlen(svalue - 1) == 39])
         {
            yylval.tokenData->cvalue = svalue[1];
         }

         if(svalue[w] == 92 && (svalue[w+1] != 110 && svalue[w+1] != 48 && svalue[w+1] != 92))
         {
            yylval.tokenData->cvalue = yylval.tokenData->tokenstr[w+1];//svalue[w+1];
         }
         else if(strlen(svalue) == 2)
         {
            printf("ERROR(%d): Empty character ''. Characters ignored.\n", linenum);
            numErrors++;
         }
         else if(!((svalue[w] == 92 && (svalue[w+1] == 110 || svalue[w+1] == 48 || svalue[w+1] == 92)) || svalue[w+1] == 39))
         {
            while(svalue[w] != 39)
            {
               ++w;
            }
            int length = w - 1;
            yylval.tokenData->cvalue = yylval.tokenData->tokenstr[1];
            printf("WARNING(%d): character is %d characters long and not a single character: '%s'. The first char will be used.\n", linenum, length, svalue);
            numWarnings++;
         }
         else
         {
            w = 1;
            if(svalue[w] == 92 && svalue[w+1] == 110)
            {
               yylval.tokenData->cvalue = '\n';
               ++w;
            }
            else if(svalue[w] == 92 && svalue[w+1] == 39)
            {
               printf("Test");
               yylval.tokenData->cvalue = '\'';
               ++w;
            }
            else if(svalue[w] == 92 && svalue[w+1] == 48)
            {
               yylval.tokenData->cvalue = 00000000;
               ++w;
            }
            else if(svalue[w] == 92 && svalue[w+1] == 92)
            {
               yylval.tokenData->cvalue = 92;
               ++w;
            }
            else if(svalue[w] == 92)
            {
               yylval.tokenData->cvalue = svalue[w+1];
               ++w;
            }
         }
         break;
      case STRINGCONST:
         int len; 
         len = strlen(tmp);
         int i; int j;
         j = 0;
         i = 1;

         while(i < len)
         {
            fin[j] = tmp[i];

            if(tmp[i] == '\\' && tmp[i+1] == 'n') // \n
            {
               fin[j] = 10;
               i++;
            }
            else if(tmp[i] == '\\' && tmp[i+1] == '0') // \0
            {
               fin[j] = 0;
               i++;
            }
            else if(tmp[i] == '\\' && tmp[i+1] == '\\')
            {
               fin[j] = 92;
               i++;
            }
            else if(tmp[i] == '\\' && tmp[i+1] == '\"')
            {
               fin[j] = 34;
               i++;
            }
            else if(tmp[i] == '\\') // \ anything
            {
               fin[j] = tmp[i+1];
               i++;
            }
            j++;
            i++;
         }
         fin[j-1] = '\0';
         // have to set all tokenData->svalues to \0 else we have issues
         for(int i = 0; i < strlen(fin) + 1; i++)
         {
            yylval.tokenData->svalue[i] = '\0';
         }
         for(int i = 0; i < strlen(fin); i++)
         {
            yylval.tokenData->svalue[i] = fin[i];
         }
         yylval.tokenData->nvalue = strlen(yylval.tokenData->svalue);
         yylval.tokenData->stringLength = strlen(fin);
         break;
      default:
         yylval.tokenData->tokenstr = strdup(svalue);
         break;
   }
   yylval.tokenData->tokenstr = strdup(svalue);
   return tokenClass;
}
%}

%option noyywrap

%%
\/\/(.*)                                     { line;}
"static"                                     { return setValue(line, STATIC, yytext); }
"bool"                                       { return setValue(line, BOOLKW, yytext); }
"char"                                       { return setValue(line, CHAR, yytext); }
"int"                                        { return setValue(line, INT, yytext); }
"if"                                         { return setValue(line, IF, yytext); }
"then"                                       { return setValue(line, THEN, yytext); }
"else"                                       { return setValue(line, ELSE, yytext); }
"while"                                      { return setValue(line, WHILE, yytext); }
"do"                                         { return setValue(line, DO, yytext); }
"for"                                        { return setValue(line, FOR, yytext); }
"to"                                         { return setValue(line, TO, yytext); }
"by"                                         { return setValue(line, BY, yytext); }
"return"                                     { return setValue(line, RETURN, yytext); }
"break"                                      { return setValue(line, BREAK, yytext); }
"or"                                         { return setValue(line, OR, yytext); }
"and"                                        { return setValue(line, AND, yytext); }
"not"                                        { return setValue(line, NOT, yytext); }
"true"                                       { return setValue(line, BOOL, yytext); }         
"false"                                      { return setValue(line, BOOL, yytext); }
[0-9]+|[0-9]*                                { return setValue(line, NUMCONST, yytext); }
\'([^\n\']|\\.)*\'                           { return setValue(line, CHARCONST, yytext); }
\"([^\\\n"]|\\.)*\"                          { return setValue(line, STRINGCONST, yytext); }
"="                                          { return setValue(line, EQ, yytext); }
"<"                                          { return setValue(line, LQ, yytext); }
">"                                          { return setValue(line, GQ, yytext); }
"+"                                          { return setValue(line, PLUS, yytext); }
"-"                                          { return setValue(line, MINUS, yytext); }
"*"                                          { return setValue(line, STAR, yytext); }
"/"                                          { return setValue(line, DIV, yytext); }
"%"                                          { return setValue(line, MOD, yytext); }
"("                                          { return setValue(line, LPAREN, yytext); }
")"                                          { return setValue(line, RPAREN, yytext); }
";"                                          { return setValue(line, SEMICOLON, yytext); }
","                                          { return setValue(line, COMMA, yytext); }   
":"                                          { return setValue(line, COLON, yytext); }
"?"                                          { return setValue(line, QMARK, yytext); }
"["                                          { return setValue(line, LBRACKET, yytext); }
"]"                                          { return setValue(line, RBRACKET, yytext); }
"{"                                          { return setValue(line, LBRACE, yytext); }
"}"                                          { return setValue(line, RBRACE, yytext); }
"><"                                         { return setValue(line, NEQ, yytext); }
">="                                         { return setValue(line, GEQ, yytext); }
"<="                                         { return setValue(line, LEQ, yytext); }
"++"                                         { return setValue(line, INC, yytext); }
"--"                                         { return setValue(line, DEC, yytext); }
"+="                                         { return setValue(line, ADDASS, yytext); }
"-="                                         { return setValue(line, SUBASS, yytext); }
"*="                                         { return setValue(line, MULASS, yytext); }
"/="                                         { return setValue(line, DIVASS, yytext); }
":="                                         { return setValue(line, ASGN, yytext); }
\n                                           { line++; }
" "                                          { ; }
\t                                           { ; }


[a-zA-Z]+[a-zA-Z|0-9]*                       { return setValue(line, ID, yytext); }
.                                            { printf("ERROR(%d): Invalid or misplaced input character: '%c'. Character Ignored.\n", line, yytext[0]); numErrors++; }
%%