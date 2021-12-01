%{
//Parser.y Bison File
//*************************************************************
// To send to course server, tar work into file (ex. tar cvf file.tar *)
// Then run scp file.tar oste1799@cs-445.cs.uidaho.edu:/home/oste1799/CS445v2/directory of assignment
//*************************************************************/
#include "scanType.h" // tokenData type
#include "treeNodes.h"
#include <getopt.h>
#include <stdio.h>
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <string.h>
#include "semantic.h"
#include "IO.h"
#include "codeGen.h"
#include "yyerror.h"

#define YYERROR_VERBOSE

extern int yylex();
extern int yydebug;
extern FILE *yyin;      
extern int line; // ERR line number from the scanner
int numErrors;
int numWarnings;   // ERR err count
static TreeNode *syntaxTree;
bool PAST; // PAST value is used in treeNodes.c
SymbolTable st;
int Loffset = -2;
int Goffset = 0;

bool displayOffset = false;

FILE * code;

bool m;
/*void yyerror(const char *msg)
{
   printf("ERROR(%d): %s\n", line, msg);
   numErrors++;
}*/

int i = 0;

%}

// this is the type of yylval
%union {
   ExpType type;           // For passing types (ie pass a type in a decl like int or bool)
   TokenData *tokenData;   // For terminals. Token data comes from yylex() in the $ vars
   TreeNode *tree;        // For nonterminals. Add these nodes as you build the tree.
}

//%type  <value> // LOTS OF GRAMMARS ????, THEN MUST CHANGE LOTS OF STUFF BENEATH



%token <tokenData> BOOL NUMCONST CHARCONST STRINGCONST ID 
%token <tokenData> STATIC BOOLKW CHAR INT IF THEN ELSE WHILE DO FOR TO BY RETURN
%token <tokenData> BREAK OR AND NOT NEQ GEQ LEQ INC DEC ADDASS SUBASS
%token <tokenData> MULASS DIVASS ASGN 
%token <tokenData> EQ LQ GQ PLUS MINUS STAR DIV MOD LPAREN RPAREN SEMICOLON COMMA COLON QMARK
%token <tokenData> LBRACKET RBRACKET LBRACE RBRACE
%type <type> typeSpec
// nonterminals
%type <tree> declList decl varDecl scopedVarDecl varDeclList varDeclInit varDeclId
%type <tree> funDecl parms parmList parmTypeList parmIdList parmId simpleExp
%type <tree> stmt expStmt compoundStmt localDecls stmtList endStmt
%type <tree> iterRange returnStmt breakStmt exp andExp program
%type <tree> unaryRelExp relExp relop sumExp sumop mulExp mulop unaryExp unaryop
%type <tree> factor mutable immutable call args argList constant
%type <tree> matched unmatched 

%%
program        :  declList                                     {  syntaxTree = $1; }
               ;
declList       :  declList decl                                {  $$ = addSibling($1, $2); }
               |  decl                                         {  $$ = $1; }
               ;
decl           :  varDecl                                      {  $$ = $1; }
               |  funDecl                                      {  $$ = $1; }
               |  error                                        {  $$ = NULL; }
               ;
varDecl        :  typeSpec varDeclList SEMICOLON               {  $$ = $2;
                                                                  typeToSibling($$, $1);
                                                               }
               |  error varDeclList SEMICOLON                  {  $$ = NULL; yyerrok; }
               |  typeSpec error SEMICOLON                     {  $$ = NULL; yyerrok; yyerrok; }
               ;
scopedVarDecl  :  STATIC typeSpec varDeclList SEMICOLON        {  $$ = $3;
                                                                  //$$->expType = $2;
                                                                  $$->isStatic = true; 
                                                                  typeToStatic($$, $2);
                                                                  yyerrok;
                                                               }
               |  typeSpec varDeclList SEMICOLON               {  $$ = $2;
                                                                  //$$->expType = $1;
                                                                  typeToSibling($$, $1);
                                                                  yyerrok; 
                                                               }
               ;
varDeclList    :  varDeclList COMMA varDeclInit                {  $$ = addSibling($1, $3); 
                                                                  yyerrok;
                                                               }
               |  varDeclList COMMA error                      {  $$ = NULL; }
               |  varDeclInit                                  {  $$ = $1; }
               |  error                                        {  //if($0 != NULL)
                                                                     $$ = NULL; 
                                                               }
               ;
varDeclInit    :  varDeclId                                    {  $$ = $1; }
               |  varDeclId COLON simpleExp                    {
                                                                  $$ = $1;
                                                                  if($1 != NULL)
                                                                  {
                                                                     $$->child[0] = $3;
                                                                  } 
                                                               }
               |  error COLON simpleExp                        {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               ;
varDeclId      :  ID                                           {  $$ = newDeclNode(VarK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->isInit = true; 
                                                               }
               |  ID LBRACKET NUMCONST RBRACKET                {  $$ = newDeclNode(VarK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->isArray = true;
                                                                  $$->TD = $1;
                                                                  $$->isInit = true; 
                                                                  //$$->attr.value = $3->nvalue;
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->expType = UndefinedType;
                                                                  $$->memSize = $3->nvalue + 1;
                                                               }
               |  ID LBRACKET error                            {  $$ = NULL; }
               |  error RBRACKET                               {  $$ = NULL; yyerrok; }
               ;
typeSpec       :  INT                                          {  $$ = Integer; }
               |  BOOLKW                                       {  $$ = Boolean; }
               |  CHAR                                         {  $$ = Char; }
               ;
funDecl        :  typeSpec ID LPAREN parms RPAREN compoundStmt {  $$ = newDeclNode(FuncK, $2);
                                                                  $$->attr.name = strdup($2->tokenstr);
                                                                  $$->expType = $1;
                                                                  $$->child[0] = $4;
                                                                  $$->child[1] = $6;
                                                               }
               |  ID LPAREN parms RPAREN compoundStmt          {  $$ = newDeclNode(FuncK, $1);
                                                                  $$->attr.name = strdup($1->tokenstr);
                                                                  //$$->expType = Void;
                                                                  $$->TD = $1;
                                                                  $$->child[0] = $3;
                                                                  $$->child[1] = $5;
                                                               }
               |  typeSpec error                               {  $$ = NULL; }
               |  typeSpec ID LPAREN error                     {  $$ = NULL; }
               |  ID LPAREN error                              {  $$ = NULL; }
               |  ID LPAREN parms RPAREN error                 {  $$ = NULL; }
               ;
parms          :  parmList                                     {  $$ = $1; }
               |  %empty                                       {  $$ = NULL; }// epsilon prod /////////
               ;
parmList       :  parmList SEMICOLON parmTypeList              {  $$ = addSibling($1, $3); }
               |  parmTypeList                                 {  $$ = $1; }
               |  parmList SEMICOLON error                     {  $$ = NULL; }
               |  error                                        {  $$ = NULL; }
               ;
parmTypeList   :  typeSpec parmIdList                          {  $$ = $2; 
                                                                  typeToSibling($$, $1);
                                                               }
               |  typeSpec error                               {  $$ = NULL; }
               ;
parmIdList     :  parmIdList COMMA parmId                      {  $$ = addSibling($1, $3);
                                                                  yyerrok; }
               |  parmId                                       {  $$ = $1; }
               |  parmIdList COMMA error                       {  $$ = NULL; }
               |  error                                        {  $$ = NULL; }
               ;
parmId         :  ID                                           {  $$ = newDeclNode(ParamK, $1); 
                                                                  $$->attr.name = strdup($1->tokenstr);
                                                                  //$$->isInit = true;
                                                               }
               |  ID LBRACKET RBRACKET                         {  $$ = newDeclNode(ParamK, $1);
                                                                  $$->attr.name = strdup($1->tokenstr);
                                                                  $$->isArray = true;
                                                                  //$$->isInit = true;
                                                                  //$$->expType = UndefinedType;
                                                               }
               ;
stmt           :  matched                                      {  $$ = $1; }
               |  unmatched                                    {  $$ = $1; }
               ;
expStmt        :  exp SEMICOLON                                {  $$ = $1; }
               |  SEMICOLON                                    {  $$ = NULL; }
               |  error SEMICOLON                              {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               ;
compoundStmt   :  LBRACE localDecls stmtList RBRACE            {  $$ = newStmtNode(CompoundK, $1);
                                                                  $$->isCompound = true;
                                                                  $$->child[0] = $2;
                                                                  $$->child[1] = $3;
                                                                  yyerrok;
                                                               }
               ;   
localDecls     :  localDecls scopedVarDecl                     {  $$ = addSibling($1, $2); /*$2->isStatic = true;*/ }
               |  %empty                                       {  $$ = NULL; }// epsilon prod
               ;
stmtList       :  stmtList stmt                                {  $$ = addSibling($1, $2); }
               |  %empty                                       {  $$ = NULL; }// epsilon prod
               ;
matched        :  endStmt                                      {  $$ = $1; }
               |  IF simpleExp THEN matched ELSE matched       {  $$ = newStmtNode(IfK, $1); 
                                                                  $$->child[0] = $2; 
                                                                  //$$->child[0]->expType = Boolean;
                                                                  // $1->child[0]->attr.value; //////////////////////////
                                                                  $$->child[1] = $4;
                                                                  $$->child[2] = $6;   
                                                               }
               |  IF error                                     {  $$ = NULL; }
               |  IF error ELSE matched                        {  $$ = NULL; yyerrok; }
               |  IF error THEN matched ELSE matched           {  $$ = NULL; yyerrok; }
               |  WHILE simpleExp DO matched                   {  $$ = newStmtNode(WhileK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->child[0] = $2;
                                                                  //$$->child[0]->expType = Boolean;
                                                                  $$->child[1] = $4;
                                                               }
               |  WHILE error DO matched                       {  $$ = NULL; yyerrok; }
               |  WHILE error                                  {  $$ = NULL; }
               |  FOR ID ASGN iterRange DO matched             {  $$ = newStmtNode(ForK, $1);
                                                                  $$->child[0] = newDeclNode(VarK, $2);
                                                                  $$->child[0]->expType = Integer;
                                                                  //$$->attr.op = $3->tokenclass;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  $$->attr.name = $3->tokenstr;
                                                                  //printf("attr.name: %s\n", $$->attr.name);
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  $$->child[1] = $4;
                                                                  $$->child[2] = $6;
                                                                  //$$->child[2]->expType = Integer;
                                                               }
               |  FOR ID ASGN error DO matched                 {  $$ = NULL; yyerrok; }
               |  FOR error                                    {  $$ = NULL; }
               ;
unmatched      :  IF simpleExp THEN matched ELSE unmatched     {  $$ = newStmtNode(IfK, $1); 
                                                                  $$->child[0] = $2;
                                                                  $$->child[1] = $4;
                                                                  $$->child[2] = $6;
                                                               }
               |  IF error THEN matched ELSE unmatched         {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  WHILE simpleExp DO unmatched                 {  $$ = newStmtNode(WhileK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->child[0] = $2;
                                                                  //$$->child[0]->expType = Boolean;
                                                                  $$->child[1] = $4;
                                                               }
               |  WHILE error DO unmatched                     {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  FOR ID ASGN iterRange DO unmatched           {  $$ = newStmtNode(ForK, $1);
                                                                  $$->child[0] = newDeclNode(VarK, $2);
                                                                  $$->child[0]->expType = Integer;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->attr.op = $3->tokenclass;
                                                                  $$->attr.name = $3->tokenstr;
                                                                  $$->child[1] = $4;
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  $$->child[2] = $6;
                                                                  //$$->child[2]->expType = Integer;
                                                               }
               |  FOR ID ASGN error DO unmatched               {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  FOR error                                    {  $$ = NULL; }
               |  IF simpleExp THEN stmt                       {  $$ = newStmtNode(IfK, $1); 
                                                                  $$->child[0] = $2;
                                                                  $$->child[1] = $4;
                                                               }
               |  IF error THEN matched                        {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               ;
endStmt        :  expStmt                                      {  $$ = $1; }
               |  compoundStmt                                 {  $$ = $1; }
               |  returnStmt                                   {  $$ = $1; }
               |  breakStmt                                    {  $$ = $1; }
               ;
iterRange      :  simpleExp TO simpleExp                       {  $$ = newStmtNode(RangeK, $2);
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  //$$->child[2] = newExpNode(ConstantK, $1);
                                                                  //$$->child[2]->attr.value = 1;
                                                               }
               |  simpleExp TO error                           {  $$ = NULL; }
               |  error BY error                               {  $$ = NULL; yyerrok; }
               |  simpleExp TO simpleExp BY error              {  $$ = NULL; }
               |  simpleExp TO simpleExp BY simpleExp          {  $$ = newStmtNode(RangeK, $2);
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                                  $$->child[2] = $5;
                                                                  //$$->child[0]->expType = UndefinedType;
                                                                  //$$->child[1]->expType = UndefinedType;
                                                                  //$$->child[2]->expType = UndefinedType;
                                                               }
               ;
returnStmt     :  RETURN SEMICOLON                             {  $$ = newStmtNode(ReturnK, $1); 
                                                                  //$$->attr.op = $1->tokenclass; 
                                                                  $$->attr.name = $1->tokenstr;
                                                               }
               |  RETURN exp SEMICOLON                         {  $$ = newStmtNode(ReturnK, $1);
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = $2->expType;
                                                                  $$->child[0] = $2;
                                                                  yyerrok;
                                                               }
               |  RETURN error SEMICOLON                       {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               ;
breakStmt      :  BREAK SEMICOLON                              {  $$ = newStmtNode(BreakK, $1);
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->attr.name = $1->tokenstr;
                                                               }
               ;
exp            :  mutable ASGN exp                             {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->expType = UndefinedType;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  error ASGN exp                               {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  mutable ASGN error                           {  $$ = NULL; }
               |  mutable ADDASS exp                           {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  mutable ADDASS error                         {  $$ = NULL; }
               |  mutable SUBASS exp                           {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  mutable SUBASS error                         {  $$ = NULL; }
               |  mutable MULASS exp                           {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  mutable MULASS error                         {  $$ = NULL; }
               |  mutable DIVASS exp                           {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  mutable DIVASS error                         {  $$ = NULL; }
               |  mutable INC                                  {  $$ = newExpNode(AssignK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  $$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                               }
               |  error INC                                    {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  mutable DEC                                  {  $$ = newExpNode(AssignK, $2);
                                                                  $$->attr.name = $2->tokenstr;
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->expType = Integer;
                                                                  $$->child[0] = $1;
                                                               }
               |  error DEC                                    {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               |  simpleExp                                    {  $$ = $1; }
               ;
simpleExp      :  simpleExp OR andExp                          {  $$ = newExpNode(OpK, $2); 
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  $$->expType = Boolean;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  simpleExp OR error                           {  $$ = $1; }
               |  andExp                                       {  $$ = $1; }
               ;
andExp         :  andExp AND unaryRelExp                       {  $$ = newExpNode(OpK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  $$->attr.name = $2->tokenstr;
                                                                  $$->expType = Boolean;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  andExp AND error                             {  $$ = NULL; }
               |  unaryRelExp                                  {  $$ = $1; }
               ;
unaryRelExp    :  NOT unaryRelExp                              {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Boolean;
                                                                  $$->child[0] = $2;
                                                               }
               |  NOT error                                    {  $$ = NULL; }
               |  relExp                                       {  $$ = $1; }
               ;
relExp         :  sumExp relop sumExp                          {  $$ = $2;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  sumExp                                       {  $$ = $1; }
               |  sumExp relop error                           {  $$ = NULL; }
               ;
relop          :  LQ                                           {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               |  LEQ                                          {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               |  GQ                                           {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               |  GEQ                                          {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               |  EQ         /*not assignment*/                {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               |  NEQ                                          {  $$ = newExpNode(OpK, $1); 
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                               }
               ;
sumExp         :  sumExp sumop mulExp                          {  $$ = $2;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  sumExp sumop error                           {  $$ = NULL; }
               |  mulExp                                       {  $$ = $1; }
               ;
sumop          :  PLUS                                         {  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                               }
               |  MINUS                                        {  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                               }
               ;
mulExp         :  mulExp mulop unaryExp                        {  $$ = $2;
                                                                  $$->child[0] = $1;
                                                                  $$->child[1] = $3;
                                                               }
               |  mulExp mulop error                           {  $$ = NULL; }
               |  unaryExp                                     {  $$ = $1; }   
               ;
mulop          :  STAR                                         {  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                               }
               |  DIV                                          {  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                               }
               |  MOD                                          {  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                 // $$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                               }
               ;
unaryExp       :  unaryop unaryExp                             {  $$ = $1;
                                                                  $$->child[0] = $2;
                                                               }
               |  unaryop error                                {  $$ = NULL; } ////////////////////////////////////////////////////////////////////////// Causes it to go all the way through
               |  factor                                       {  $$ = $1; }
               ;
unaryop        :  MINUS                                        {  yyerrok;
                                                                  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  $$->expType = Integer;
                                                                  $$->isUnary = true;
                                                               }
               |  STAR                                         {  yyerrok;
                                                                  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  //$$->expType = Integer;
                                                                  $$->isUnary = true;
                                                               }
               |  QMARK                                        {  yyerrok;
                                                                  $$ = newExpNode(OpK, $1);
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Integer;
                                                                  //$$->attr.op = $1->tokenclass;
                                                                  //$$->expType = Integer;
                                                               }
               ;
factor         :  mutable                                      {  $$ = $1; }
               |  immutable                                    {  $$ = $1; }
               ;
mutable        :  ID                                           {  $$ = newExpNode(IdK, $1);
                                                                  $$->attr.name = strdup($1->tokenstr);
                                                                  //$$->expType = UndefinedType;
                                                               }
               |  ID LBRACKET exp RBRACKET                     {  //$$->child[0] = newExpNode(IdK, $1);
                                                                  //printf("Here\n");
                                                                  $$ = newExpNode(OpK, $2);
                                                                  //$$->attr.op = $2->tokenclass;
                                                                  //printf("Here2\n");
                                                                  $$->attr.name = $2->tokenstr;
                                                                  $$->child[0] = newExpNode(IdK, $1);
                                                                  //printf("Here3\n");
                                                                  //$$->child[0] = $1;
                                                                  $$->child[0]->attr.name = $1->tokenstr;
                                                                  $$->child[0]->isArray = true;
                                                                  $$->child[1] = $3;
                                                                  //$$->expType = UndefinedType;
                                                               }
               ;
immutable      :  LPAREN exp RPAREN                            {  $$ = $2; 
                                                                  yyerrok;
                                                               }
               |  LPAREN error                                 {  $$ = NULL; }
               |  call                                         {  $$ = $1; }
               |  constant                                     {  $$ = $1; }
               ;
call           :  ID LPAREN args RPAREN                        {  $$ = newExpNode(CallK, $1);
                                                                  $$->attr.name = strdup($1->tokenstr);
                                                                  $$->child[0] = $3;
                                                               }
               |  error LPAREN                                 {  $$ = NULL;
                                                                  yyerrok;
                                                               }
               ;
args           :  argList                                      {  $$ = $1; }
               |  %empty                                       {  $$ = NULL; }// epsilon prod
               ;
argList        :  argList COMMA exp                            {  $$ = addSibling($1, $3);  yyerrok; }
               |  exp                                          {  $$ = $1; }
               |  argList COMMA error                          {  $$ = NULL; }
               ;
constant       :  NUMCONST                                     {  yyerrok;
                                                                  $$ = newExpNode(ConstantK, $1); 
                                                                  $$->attr.value = $1->nvalue;
                                                                  $$->expType = Integer;
                                                                  $$->isInit = true;
                                                                  $$->isConstant = true;
                                                                  $$->memSize = 1;
                                                               }
               |  CHARCONST                                    {  yyerrok;
                                                                  $$ = newExpNode(ConstantK, $1);
                                                                  $$->TD = $1;
                                                                  $$->attr.name = $1->tokenstr;
                                                                  //$$->attr.cvalue = $1->cvalue;
                                                                  $$->expType = Char;
                                                                  $$->isInit = true;
                                                                  $$->isCharacter = true;
                                                                  $$->isConstant;
                                                                  $$->memSize = 1;
                                                               }
               |  STRINGCONST                                  {  yyerrok;
                                                                  $$ = newExpNode(ConstantK, $1);
                                                                  $$->attr.string = strdup($1->svalue);
                                                                  $$->isArray = true;
                                                                  $$->expType = Char;
                                                                  $$->isCharacter = false;
                                                                  $$->isConstant = true;
                                                                  $$->memSize = $1->stringLength + 1;
                                                               }
               |  BOOL                                         {  yyerrok;
                                                                  $$ = newExpNode(ConstantK, $1);
                                                                  $$->attr.value = $1->nvalue;
                                                                  $$->attr.name = $1->tokenstr;
                                                                  $$->expType = Boolean;
                                                                  $$->isInit = true;
                                                                  $$->isConstant = true;
                                                                  $$->memSize = 1;
                                                               }
               ;                 

%%
extern int yydebug;
int main(int argc, char *argv[])
{
   extern int optind;
   int c = 0;
   bool printSyntaxTree = 0;
   TreeNode *tmp;
   int selectOption;
   numErrors = 0;
   numWarnings = 0;
   m = false;
   Loffset = 0;
   Goffset = 0;

   while((c = getopt(argc, argv, "dDhMpP")) != -1)
   {
      switch(c)
      {
         case 'c':
            //do nothing
            break;
         case 'd':
            yydebug=1;
            break;
         case 'D':
            st.debug(1);
            break;
         case 'h':
            printf("usage: -c [options] [sourcefile]\n");
            printf("options:\n");
            printf("-d     - turn on parser debugging\n");
            printf("-D     - turn on symbol table debugging\n");
            printf("-h     - print this usage message\n");
            printf("-M     - print the abstract syntax tree with memory locations\n");
            printf("-p     - print the abstract syntax tree\n");
            printf("-P     - print the abstract syntax tree plus type information\n");
            break;
         case 'M':
            printSyntaxTree = true;
            selectOption = 1;
            m = true;
            PAST = true;
            displayOffset = true;
            break;
         case 'p':
            //yyparse();
            printSyntaxTree = true;
            selectOption = 0;
            break;
         case 'P':
            // printAST with type information added.
            //yyparse();
            //analyze(syntaxTree);

            printSyntaxTree = true;
            selectOption = 1;
            PAST = true;
            break;
         default:
            exit(1);
      }
   }


   if(argc > optind)
   {
      if((yyin = fopen(argv[argc - 1], "r")))
      {
         // file open successful
         // if(!strcmp(argv[argc - 1], "syntaxerr-logic.c-"))
         // {
            //yydebug = 1;
         //}
      }
      else
      {
         // failed to open file
         printf("ERROR(ARGLIST): source file \"%s\" could not be opened.\n", argv[1]);
         numErrors++;
         printf("Number of warnings: 0\n");
         printf("Number of errors: %i\n", numErrors);
         exit(1);
      }
   }

   initErrorProcessing();
   yyparse();

   if(printSyntaxTree && selectOption == 0 && numErrors == 0)
   {
      printTree(syntaxTree, 0);
   }
   else if(printSyntaxTree && selectOption == 1 && numErrors == 0)
   {
      prototype();
      analyze(syntaxTree);
      tmp = (TreeNode *)st.lookup("main");

      if(tmp != NULL && tmp->nodekind == DeclK && (tmp->subkind.decl != FuncK && tmp->subkind.decl == ParamK) || tmp == NULL)
      {
         printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
         numErrors++;
      }
      else if(tmp != NULL && tmp->nodekind == DeclK && tmp->subkind.decl != FuncK)
      {
         if(tmp->child[0] != NULL)
         {
            printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
            numErrors++;
         }
      }
      else if(tmp->child[0] != NULL && tmp->child[0]->subkind.decl == ParamK && tmp != NULL)
      {
         printf("ERROR(LINKER): A function named 'main' with no parameters must be defined.\n");
         numErrors++;
      }
      if(numErrors < 1)
         printTree(syntaxTree, 0);
   }
   if(numErrors == 0)
   {
      genCode(syntaxTree, "w");
   }
   //printTree(syntaxTree, 0);

   if(displayOffset == true)
      printf("Offset for end of global space: %d\n", Goffset);
   printf("Number of warnings: %d\n", numWarnings);
   printf("Number of errors: %d\n", numErrors);
   return 0;
}