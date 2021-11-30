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
   int fp;
   if(!strcmp(tree->attr.name, "-"))
   {

   }
   else if(!strcmp(tree->attr.name, "?"))
   {
      treeTargetCode(tree->child[0]);
      emitRO((char *)"RND", 3, 3, 6, (char *)"Op ?");
   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "not"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
      emitRO((char *)"XOR", 3, 3, 4, (char *)"Op NOT");
   }
   else
   {
      printf("NOT IN UNARY TARGET OPS\n");
   }
}

void binaryOpCode(TreeNode* tree)
{
   int fp;
   if(!strcmp(tree->attr.name, "or")
   {

   }
   else if(!strcmp(tree->attr.name, "and"))
   {
      
   }
   else if(!strcmp(tree->attr.name, "<"))
   {

   }
   else if(!strcmp(tree->attr.name, ">"))
   {

   }
   else if(!strcmp(tree->attr.name, "="))
   {

   }
   else if(!strcmp(tree->attr.name, ">="))
   {

   }
   else if(!strcmp(tree->attr.name, "<="))
   {

   }
   else if(!strcmp(tree->attr.name, "><"))
   {

   }
   else if(!strcmp(tree->attr.name, "+"))
   {

   }
   else if(!strcmp(tree->attr.name, "-"))
   {

   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "/"))
   {

   }
   else if(!strcmp(tree->attr.name, "%"))
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
   int fp;
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
   else if(!strcmp(tree->attr.name, "++"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Inc");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store var ");
   }
   else if(!strcmp(tree->attr.name, "--"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Dec");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store var ");
   }
   else
   {
      printf("NOT IN UNARY TARGET ASSIGNS\n");
   }
}

void binaryAsgnCode(TreeNode* tree)
{
   int fp;
   if(!strcmp(tree->attr.name, "+="))
   {
      fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "-="))
   {
      fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "*="))
   {
      fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "/="))
   {
      fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, ":="))
   {
      treeTargetCode(tree);
   }
   else
   {
      printf("NOT IN TARGET BINARY ASSIGNS\n");
   }
}

int frame(TreeNode* tree)
{
   TreeNode* tmp = tree->child[0];
   tmp = st.lookupNode(tmp->attr.name);
   if(tree->child[0]->isStatic || tmp != NULL)
   {
      return 0;
   }
   return 1;
}