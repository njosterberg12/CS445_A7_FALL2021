#include <string.h>
#include <time.h>
#include "codeGen.h"
#include "emitcode.h"
#include "parser.tab.h"

void treeTargetCode(TreeNode* tree)
{
   char* name;
   int dif, cur, dif2;
   int breakloc, skiploc;

   TreeNode *tmp = NULL;

   while(tree != NULL)
   {
      if(tree->nodekind == StmtK)
      {
         switch(tree->subkind.stmt)
         {
            case NullK:
               printf("NULL \n");
               emitComment((char *)"NULL");
               break;
            case IfK:
               emitComment((char *)"If");
               for(int i = 0; i <= 2; i++)
               {
                  treeTargetCode(tree->child[i]);
               }
               break;
            case WhileK:
               emitComment((char *)"While");
               break;
            case ForK:
               emitComment((char *)"For");
               break;
            case CompoundK:
               emitComment((char *)"Compound");
               break;
            case ReturnK:
               emitComment((char *)"Return");
               break;
            case BreakK:
               emitComment((char *)"Break");
               break;
            case RangeK:
               emitComment((char *)"Range");
               break;
            default:
               emitComment((char *)"Unknown Stmt------");
               break;
         }
      }
      else if(tree->nodekind == ExpK)
      {
         switch(tree->subkind.exp)
         {
            case OpK:
               emitComment((char *)"Op");
               break;
            case ConstantK:
               emitComment((char *)"Constant");
               break;
            case IdK:
               emitComment((char *)"Id");
               break;
            case AssignK:
               emitComment((char *)"Assign");
               break;
            case InitK:
               emitComment((char *)"Init");
               break;
            case CallK:
               emitComment((char *)"Call");
               break;
            default:
               printf("Unknown Exp LINE %d", tree->lineno);
               break;
         }
      }
      else if(tree->nodekind == DeclK)
      {
         switch(tree->subkind.decl)
         {
            case VarK:
               if(tree->isArray == true)
               {
                  emitComment((char *)"Var array");
               }
               else
               {
                  emitComment((char *)"Var");
               }
               break;
            case FuncK:
               emitComment((char *)"Function", tree->attr.name);
               break;
            case ParamK:
               if(tree->isArray == true)
               {
                  emitComment((char *)"Param array");
               }
               else
               {
                  emitComment((char *)"Param");
               }
               break;
            default:
               printf("Unknown Decl LINE %d", tree->lineno);
               break;
         }
      }
   }
}

void unaryOpCode(TreeNode* tree)
{
   if(!strcmp(tree->attr.name, "-"))
   {

   }
   else if(!strcmp(tree->attr.name, "?"))
   {

   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "not"))
   {

   }
   else
   {
      printf("NOT IN UNARY TARGET OPS\n");
   }
}

void binaryOpCode(TreeNode* tree)
{
   if(!strcmp(tree->attr.name, "or") || !strcmp(tree->attr.name, "and"))
   {
      
   }
   else if(!strcmp(tree->attr.name, "<") || !strcmp(tree->attr.name, ">") || !strcmp(tree->attr.name, "=") || !strcmp(tree->attr.name, ">=") || !strcmp(tree->attr.name, "<=") || !strcmp(tree->attr.name, "><"))
   {

   }
   else if(!strcmp(tree->attr.name, "+") || !strcmp(tree->attr.name, "-") || !strcmp(tree->attr.name, "*") || !strcmp(tree->attr.name, "/") || !strcmp(tree->attr.name, "%"))
   {

   }
   else if(!strcmp(tree->attr.name, "["))
   {

   }
   else
   {
      printf("NOT IN BINARY TARGET OPS\n");
   }
}

void unaryAsgnCode(TreeNode* tree)
{
   if(!strcmp(tree->attr.name, "-"))
   {

   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "?"))
   {

   }
   else if(!strcmp(tree->attr.name, "not"))
   {

   }
   else if(!strcmp(tree->attr.name, "++") || !strcmp(tree->attr.name, "--"))
   {

   }
   else
   {
      printf("NOT IN UNARY TARGET ASSIGNS\n");
   }
}

void binaryAsgnCode(TreeNode* tree)
{
   if(!strcmp(tree->attr.name, "+=") || !strcmp(tree->attr.name, "-=") || !strcmp(tree->attr.name, "*=") || !strcmp(tree->attr.name, "/="))
   {

   }
   else if(!strcmp(tree->attr.name, ":="))
   {

   }
   else
   {
      printf("NOT IN TARGET BINARY ASSIGNS\n");
   }


}