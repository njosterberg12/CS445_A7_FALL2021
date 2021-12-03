#include <string.h>
#include "codeGen.h"
#include "emitcode.h"
#include "parser.tab.h"

extern SymbolTable st;
FILE * code;
int toffset = 0;
TreeNode* temp;

void codeGen(TreeNode* tree, char* outFile, char* fileComp)
{
   code = fopen(outFile, "w");

   // header comment
   emitComment((char *)"C- compiler version C-F21");
   emitComment((char *)"Built: Dec 3, 2021");
   emitComment((char *)"Author: Nathaniel Osterberg");
   emitComment((char *)"File compiled: ", fileComp); ////////////////// need to add file compiled
   emitComment((char *)"");

   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
   codeGenIO();
   treeTargetCode(tree);
   //codeGenMain(tree);
}

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
               /*printf("NULL \n");
               emitComment((char *)"NULL");*/
               break;
            case IfK:
               /*emitComment((char *)"If");
               for(int i = 0; i <= 2; i++)
               {
                  treeTargetCode(tree->child[i]);
               }*/
               break;
            case WhileK:
               //emitComment((char *)"While");
               break;
            case ForK:
               //emitComment((char *)"For");
               break;
            case CompoundK:
               emitComment((char *)"COMPOUND");
               emitComment((char *)"TOFF set:", toffset);
               for(int i = 0; i <= 2; i++)
               {
                  if(tree != NULL)
                  {
                     treeTargetCode(tree->child[i]);
                  }
               }
               emitComment((char *)"Compound Body");
               emitComment((char *)"TOFF set:", toffset);
               emitComment((char *)"END COMPOUND");
               break;
            case ReturnK:
               //emitComment((char *)"Return");
               break;
            case BreakK:
               //emitComment((char *)"Break");
               break;
            case RangeK:
               //emitComment((char *)"Range");
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
               //emitComment((char *)"Op");
               break;
            case ConstantK:
               //emitComment((char *)"Constant");
               break;
            case IdK:
               //emitComment((char *)"Id");
               break;
            case AssignK:
               //emitComment((char *)"Assign");
               break;
            case InitK:
               //emitComment((char *)"Init");
               break;
            case CallK:
               //emitComment((char *)"Call");
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
                  //emitComment((char *)"Var array");
               }
               else
               {
                  //emitComment((char *)"Var");
               }
               break;
            case FuncK:{
               toffset = -2;
               tree->offset = emitSkip(0);
               emitComment((char *)"FUNCTION", tree->attr.name);
               emitComment((char*)"TOFF set:", toffset);
               emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
               temp = tree->child[0];
               while(temp != NULL)
               {
                  toffset--;
                  temp = temp->sibling;
               }
               int ghost = toffset;
               treeTargetCode(tree->child[1]);
               emitComment((char *)"Add standard closing in case there is no return statement");
               emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
               emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
               emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
               emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
               emitComment((char *)"END FUNCTION", tree->attr.name);
               toffset = ghost;
               //emitComment((char *)"Function", tree->attr.name);
               break;}
            case ParamK:
               if(tree->isArray == true)
               {
                  //emitComment((char *)"Param array");
               }
               else
               {
                  //emitComment((char *)"Param");
               }
               break;
            default:
               printf("Unknown Decl LINE %d", tree->lineno);
               break;
         }
      }
      else
      {
         printf("Unknown node type: %d LINE %d\n", tree->nodekind, tree->lineno);
      }
      tree = tree->sibling;
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
      /*treeTargetCode(tree->child[0]);
      emitRO((char *)"RND", 3, 3, 6, (char *)"Op ?"); */
   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "not"))
   {
      /*treeTargetCode(tree->child[0]);
      emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
      emitRO((char *)"XOR", 3, 3, 4, (char *)"Op NOT");*/
   }
   else
   {
      printf("NOT IN UNARY TARGET OPS\n");
   }
}

void binaryOpCode(TreeNode* tree)
{
   int fp;
   if(!strcmp(tree->attr.name, "or"))
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
      /*treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Inc");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store var ");*/
   }
   else if(!strcmp(tree->attr.name, "--"))
   {
      /*treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Dec");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store var ");*/
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
      /*fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");*/
   }
   else if(!strcmp(tree->attr.name, "-="))
   {
      /*fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");*/
   }
   else if(!strcmp(tree->attr.name, "*="))
   {
      /*fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");*/
   }
   else if(!strcmp(tree->attr.name, "/="))
   {
      /*fp = frame(tree);
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");*/
   }
   else if(!strcmp(tree->attr.name, ":="))
   {
      /*treeTargetCode(tree);*/
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

void codeGenIO()
{

   // INPUT INT
   //tmp = st.lookupNode("input");
   //tmp->startLoc = emitSkip(0);
   //emitLoc = emitLoc + 1;

   emitComment((char *)"FUNCTION input");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"IN", 2, 2, 2, (char *)"Grab int input");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION input");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   // OUTPUT INT
   //tmp = st.lookupNode("output");
   //tmp->startLoc = emitSkip(0);

   emitComment((char *)"FUNCTION output");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRM((char *)"LD", 3, -2, 1, (char *)"Load return address");
   emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION output");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   //tmp = st.lookupNode("inputb");
   //tmp->startLoc = emitSkip(0);

   emitComment((char *)"FUNCTION inputb");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION inputb");
   emitComment("");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
   //tmp = st.lookupNode("outputb");
   //tmp->startLoc = emitSkip(0);

   emitComment((char *)"FUNCTION outputb");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRM((char *)"LD", 3, -2, 1, (char *)"Load return address");
   emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION outputb");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
   //tmp = st.lookupNode("inputc");
   //tmp->startLoc = emitSkip(0);

   emitComment((char *)"FUNCTION inputc");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION inputc");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   //tmp = st.lookupNode("outputc");
   //tmp->startLoc = emitSkip(0);
   
   emitComment((char *)"FUNCTION outputc");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRM((char *)"LD", 3, -2, 1, (char *)"Load return address");
   emitRO((char *)"OUT", 3, 3, 3, (char *)"Output integer");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION outputc");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   //tmp = st.lookupNode("outnl");
   //tmp->startLoc = emitSkip(0);

   emitComment((char *)"FUNCTION outnl");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"OUTNL", 3, 3, 3, (char *)"Output a newline");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION outnl");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   //treeTargetCode(tree); // process the tree

   //backPatchAJumpToHere(0, (char *) "Jump to init (backpatch)");
   //emitComment((char *)"Now backpatch");
}

void codeGenMain(TreeNode *t)
{
   /*
   toffset = -2;
   t->offset = emitSkip(0);
   emitComment((char *)"FUNCTION", t->attr.name);
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   temp = t->child[0];
   while(temp != NULL)
   {
      toffset--;
      temp = temp->sibling;
   }
   //treeTargetCode(t->child[1]);
   emitComment((char *)"Add standard closing in case there is no return statement");
   emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"END FUNCTION", t->attr.name);
   */
}