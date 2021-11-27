#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "scanType.h"
#include "treeNodes.h"
#include "parser.tab.h"

int blanks = 0; 
extern bool m;

/* Framework from Tiny Compiler*/
TreeNode *newDeclNode(DeclKind kind, TokenData *tokenData)
{
   TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
   int i;
   if(t == NULL)
   {
      printf("Out of memory error at line %d\n", tokenData->linenum);
   }
   else
   {
      for(i = 0; i < MAXCHILDREN; i++)
         t->child[i] = NULL;
      t->sibling = NULL;
      t->attr.name = strdup(tokenData->tokenstr);
      t->nodekind = DeclK;
      t->subkind.decl = kind;
      t->lineno = tokenData->linenum;
      t->expType = Void;
      t->memSize = 1;
   }
   return t;
}

TreeNode *newDeclNode2(DeclKind kind)
{
   TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
   int i;
   /*if(t == NULL)
   {
      printf("Out of memory error at line %d\n", tokenData->linenum);
   }*/
   //else
   //{
      for(i = 0; i < MAXCHILDREN; i++)
         t->child[i] = NULL;
      t->sibling = NULL;
      //t->attr.name = strdup(tokenData->tokenstr);
      t->nodekind = DeclK;
      t->subkind.decl = kind;
      //t->lineno = tokenData->linenum;
      t->expType = Void;
      t->memSize = 1;
   //}
   return t;
}

TreeNode *newStmtNode(StmtKind kind, TokenData *tokenData)
{
   TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
   int i;
   if(t == NULL)
   {
      printf("Out of memory error at line %d\n", tokenData->linenum);
   }
   else
   {
      for(i = 0; i < MAXCHILDREN; i++)
         t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = StmtK;
      t->subkind.stmt = kind;
      t->attr.name = strdup(tokenData->tokenstr);
      t->lineno = tokenData->linenum;
      t->expType = Void;
      t->memSize = 1;
   }
   return t;
}

TreeNode *newExpNode(ExpKind kind, TokenData *tokenData)
{
   TreeNode *t = (TreeNode *)malloc(sizeof(TreeNode));
   int i;
   if(t == NULL)
   {
      printf("Out of memory error at line %d\n", tokenData->linenum);
   }
   else
   {
      for(i = 0; i < MAXCHILDREN; i++)
         t->child[i] = NULL;
      t->sibling = NULL;
      t->nodekind = ExpK;
      t->subkind.exp = kind;
      t->lineno = tokenData->linenum;
      t->expType = Void;
      t->memSize = 1;
   }
   return t;
}

void printSpaces(int numSpaces)
{
   int i = 0;
   for(i = 0; i < numSpaces; i++)
   {
      printf(".   ");
   }
}

void printTree(TreeNode *t, int siblingNum)
{
   int i; 
   int j = siblingNum;
   if(t == NULL)
      printf("TREE NOT PRINTING");
   while(t != NULL)
   {
      if(t->nodekind == StmtK)
      {
         switch(t->subkind.stmt)
         {
            case NullK:
               printf("NULL [line: %d]\n", t->lineno);
               break;
            case IfK:
               printf("If ");
               printf("[line: %d]\n", t->lineno);
               break;
            case WhileK:
               printf("While ");
               printf("[line: %d]\n", t->lineno);
               break;
            case ForK:
               printf("For "); 
               if(m)
               {
                  printf(" [mem: ");
                  memoryType(t->memType);
                  printf(" loc: %d size: %d] ", t->offset, t->memSize);
               }
               printf("[line: %d]\n", t->lineno);
               break;
            case CompoundK:
               printf("Compound ");
               if(m)
               {
                  printf("[mem: ");
                  memoryType(t->memType);
                  printf(" loc: %d size: %d] ", t->offset, t->memSize);
               }
               printf("[line: %d]\n", t->lineno);
               break;
            case ReturnK:
               printf("Return [line: %d]\n", t->lineno);
               break;
            case BreakK:
               printf("Break [line: %d]\n", t->lineno);
               break;
            case RangeK:
               printf("Range [line: %d]\n", t->lineno);
               break;
            default:
               //printf("Unknown StmtK kind Line: %d\n", t->lineno);
               //printf("tokenstr %s\n", t->attr.name);
               break;
         }
      }
      else if(t->nodekind == ExpK)
      {
         switch(t->subkind.exp)
         {
            case OpK:
               if(t->child[1] == NULL && !strcmp(t->attr.name, "-"))
               {
                  printf("Op: chsign");
                  if(t->expType == UndefinedType)
                  {
                     if(PAST)
                        printf(" of undefined type");
                  }
                  else
                  {
                     if(PAST)
                     {
                        printf(" of type ");
                        expTypePrint(t->expType);
                     } 
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else if(t->child[1] == NULL && !strcmp(t->attr.name, "*"))
               {
                  printf("Op: sizeof");
                  if(t->expType == UndefinedType)
                  {
                     if(PAST)
                        printf(" of undefined type");
                  }
                  else
                  {
                     if(PAST)
                     {
                        printf(" of type ");
                        expTypePrint(t->expType);
                     }
                  }
                   
                  printf(" [line: %d]\n", t->lineno);
               }
               else
               {
                  printf("Op: ");
                  printf("%s ", t->attr.name);
                  if(t->expType == UndefinedType)
                  {
                     if(PAST)
                        printf(" of undefined type");   
                  }
                  else
                  {  
                     if(PAST)
                     {
                        printf("of type ");
                        expTypePrint(t->expType);
                        //printf("\nt->expType: %i\n", t->expType);
                     }
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               break;
            case ConstantK:
               if(t->expType == Boolean) // for bools
               {
                  printf("Const %s", t->attr.name);
                  if(PAST)
                  {
                     printf(" of type bool");
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else if(t->expType == CharInt) // for strings
               {
                  printf("Const is array \"");
                  printf("%s", t->attr.string); // attr.string
                  if(PAST)
                  {
                     printf("\" of type char");
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else if(t->expType == Char) // for single chars
               {
                  //printf("Const \'%c\'", t->attr.cvalue);
                  if(t->isCharacter == false)
                  {
                     printf("Const \"%s\" of array", t->attr.name);
                  }
                  else
                  {
                     //printf("\n t->attr.name: %s\n", t->attr.name);
                     if(!strcmp(t->attr.name, "'\\t'") || !strcmp(t->attr.name, "'\\''"))
                     {
                        printf("Const '%c'", t->attr.name[2]);
                     }
                     else if(!strcmp(t->attr.name,"'\\n'"))
                     {
                        printf("Const '\n'");
                     }
                     else if(!strcmp(t->attr.name, "'\\0'"))
                     {
                        printf("Const '%c'", 00000000);
                     }
                     else
                        printf("Const %s", t->attr.name);
                  }
                  if(PAST)
                  {
                     printf(" of type char");
                  }
                  if(t->isArray)
                  {
                     if(m)
                     {
                        printf(" [mem: ");
                        memoryType(t->memType);
                        printf(" loc: %d size: %d]", t->offset, t->memSize);
                     }
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else                        // for ints
               {
                  printf("Const %d", t->attr.value);
                  if(PAST)
                  {
                     printf(" of type int");
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               break;
            case IdK:
               printf("Id: %s", t->attr.name);
               if(PAST)
               {
                  if(t->isArray == true && t->isStatic == true)
                  {
                     printf(" of static array of type ");
                  }
                  else if(t->isStatic)
                  {
                     printf(" of static type ");
                  }
                  else if(t->isArray)
                  {
                     printf(" of array of type ");
                  }
                  else
                  {
                     printf(" of type ");
                  }
                  expTypePrint(t->expType);
               }
               if(m)
               {
                  printf(" [mem: ");
                  memoryType(t->memType);
                  printf(" loc: %d size: %d]", t->offset, t->memSize);
               }
               printf(" [line: %d]\n", t->lineno);
               break;
            case AssignK:
               printf("Assign: %s", t->attr.name);
               if(PAST)
               {
                  if(t->isArray)
                  {
                     printf(" of array of type ");
                  }
                  else
                  {
                     printf(" of type ");
                  }
                  expTypePrint(t->expType);
               }
               printf(" [line: %d]\n", t->lineno);
               break;
            case InitK:
               printf("Init: [line: %d]\n", t->lineno);
               break;
            case CallK:
               printf("Call: %s", t->attr.name);
               if(PAST)
               {
                  printf(" of type ");
                  expTypePrint(t->expType);
               }
               printf(" [line: %d]\n", t->lineno);
               break;
            default:
               printf("ERROR %i ", CallK);
               printf("Unknown ExpNode subkind Line: %d\n", t->lineno);
               break;
         }
      }
      else if(t->nodekind == DeclK)
      {
         switch(t->subkind.decl)
         {
            ////////////////////////////////////////////////
            case VarK:
               if(t->isStatic == true && t->isArray == true)
               {
                  printf("Var: %s of static array of type ", t->TD->tokenstr);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else if(t->isArray == true)
               {
                  printf("Var: %s of array of type ", t->TD->tokenstr);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else if(t->isStatic == true)
               {
                  printf("Var: %s of static type ", t->attr.name);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else
               {
                  printf("Var: %s of type ", t->attr.name);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               break;
            case FuncK:
               printf("Func: %s returns type ", t->attr.name);
               expTypePrint(t->expType);
               if(m)
               {
                  printf(" [mem: ");
                  memoryType(t->memType);
                  printf(" loc: %d size: %d]", t->offset, t->memSize);
               }
               printf(" [line: %d]\n", t->lineno);
               break;
            case ParamK:
               if(t->isArray)
               {
                  printf("Parm: %s of array of type ", t->attr.name);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               else
               {
                  printf("Parm: %s of type ", t->attr.name);
                  expTypePrint(t->expType);
                  if(m)
                  {
                     printf(" [mem: ");
                     memoryType(t->memType);
                     printf(" loc: %d size: %d] ", t->offset, t->memSize);
                  }
                  printf(" [line: %d]\n", t->lineno);
               }
               break;
            default:
               printf("Unknown Decl Kind Line:%d\n", t->lineno);
               break;
         }
      }
      else
      {
         printf("Unknown node type: %d Line: %d\n", t->nodekind, t->lineno);
      }
      for(i = 0; i < MAXCHILDREN; i++)
      {
         if(t->child[i] != NULL)
         {
            blanks++;
            printSpaces(blanks);
            printf("Child: %d ", i);
            printTree(t->child[i], 0);
            blanks--;
         }
      }

      if(t->sibling != NULL)
      {
         j++;
         printSpaces(blanks);
         printf("Sibling: %d ", j);
         //j++;
      }
      t = t->sibling;
   }
}

void expTypePrint(ExpType t)
{
   switch(t)
   {
      case Void:
         printf("void");
         break;
      case Integer:
         printf("int");
         break;
      case Boolean:
         printf("bool");
         break;
      case Char:
         printf("char");
         break;
      case CharInt:
         printf("CharInt");
         break;
      case Equal:
         printf("Equal");
         break;
      case UndefinedType:
         printf("undefined type");
         break;
      default:
         printf("exprType not found\n");
         break;
   }
}

TreeNode *addSibling(TreeNode *t, TreeNode *s)
{
   if(t == NULL)
      return s;
   if(s == NULL)
      return t;
   if(s != NULL && t != NULL)
   {
      TreeNode *copy = (TreeNode *)malloc(sizeof(TreeNode));
      copy = t;

      while(copy != NULL && copy->sibling != NULL)
      {
         copy = copy->sibling;
      }
      copy->sibling = s;
   }
   return t;
}

void typeToSibling(TreeNode *t, ExpType expressionType)
{
   //printf("%i --------> expType\n", expressionType); // proper exptype is printing
   TreeNode *tmp = t;
   while(tmp != NULL)
   {
      tmp->expType = expressionType;
      tmp = tmp->sibling;
   }
}

void typeToStatic(TreeNode *t, ExpType expressionType)
{
   //printf("%i --------> expType\n", expressionType); // proper exptype is printing
   TreeNode *tmp = t;
   while(tmp != NULL)
   {
      tmp->expType = expressionType;
      tmp->isStatic = true;
      tmp = tmp->sibling;
      
   }
}

void memoryType(VarKind v)
{
   switch(v)
   {
      case None:
         printf("None");
         break;
      case Global:
         printf("Global");
         break;
      case Local:
         printf("Local");
         break;
      case LocalStatic:
         printf("LocalStatic");
         break;
      case Parameter:
         printf("Parameter");
         break;
      default:
         break;
   }
}