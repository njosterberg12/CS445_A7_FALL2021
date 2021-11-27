#ifndef _TREENODES_H_
#define _TREENODES_H_

#include <stdbool.h>
#include "scanType.h"

#define MAXCHILDREN 3

extern bool PAST;

// Kinds of Operators
//    these are the token numbers for the operators same as in flex
typedef int OpKind;
// Kinds of Statements
// typedef enum {DeclK, StmtK, ExpK} NodeKind;
typedef enum {DeclK, StmtK, ExpK} NodeKind;
// Subkinds of Declarations
typedef enum {VarK, FuncK, ParamK} DeclKind;
// Subkinds of Statements
typedef enum {NullK, IfK, WhileK, ForK, CompoundK, ReturnK, BreakK, RangeK} StmtKind;
// Subkinds of Expressions
typedef enum {OpK, ConstantK, IdK, AssignK, InitK, CallK} ExpKind;
// ExpType is used for type checking (Void means no type or value, UndefinedType means undefined)
typedef enum {Void, Integer, Boolean, Char, CharInt, Equal, UndefinedType} ExpType;
// What kind of scoping is used? (decided during typing)
typedef enum {Null, None, Local, Global, Parameter, LocalStatic} VarKind;


typedef struct treeNode
{
   // connectivity in the tree
   struct treeNode *child[MAXCHILDREN];   // children of the node
   struct treeNode *sibling;              // siblings for the node
   
   // what kind of node
   int lineno;                            // linenum relevant to this node
   NodeKind nodekind;                     // type of this node
   TokenData *TD;                  
   union
   {
      DeclKind decl;                      // used when DeclK
      StmtKind stmt;                      // used when StmtK
      ExpKind exp;                        // used when ExpK
   } subkind;

   // extra properties about the node depending on type of the node
   union                                  // relevant data to type -> attr
   {
      OpKind op;                          // type of token (same as in bison)
      int value;                          // used when an integer constant or boolean
      unsigned char cvalue;               // used when a character
      char *string;                       // used when a string constant
      char *name;                         // used when IdK
   } attr;
   ExpType expType;                       // used when ExpK for type checking
   bool isArray;                          // is this an array?
   int arraySize;                         // size of array
   bool isStatic;                         // is statically allocated?
   bool isUnary;                          // var is unary
   bool isUsed;                           // var is used
   bool isErr;                            // var is an error
   bool isInit;                           // var is initialized
   bool isFinished;                       // loop var is finished
   bool isCompound;                       // var is compound
   bool isCharacter;                      
   bool isIOControl;                      // used in IO.c
   int numParams;                         // used in errors.c
   bool isConstant;

   // even more semantic stuff will go here in later assignments.
   int memSize;
   VarKind memType;
   int offset;
   
} TreeNode;

// functions
TreeNode *newDeclNode(DeclKind kind, TokenData *tokenData);
TreeNode *newStmtNode(StmtKind kind, TokenData *tokenData);
TreeNode *newExpNode(ExpKind kind, TokenData *tokenData);
TreeNode *addSibling(TreeNode *t, TreeNode *s);

TreeNode *newDeclNode2(DeclKind kind);

void typeToStatic(TreeNode *t, ExpType expressionType);
void typeToSibling(TreeNode *, ExpType);
void printTree(TreeNode *, int);
void expTypePrint(ExpType);
void printSpaces(int);
void memoryType(VarKind v);
#endif