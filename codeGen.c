#include <string.h>
#include "codeGen.h"
#include "emitcode.h"
#include "parser.tab.h"

extern SymbolTable st;
FILE * code;
int toffset = 0;
TreeNode* temp;
int ghost;

void codeGen(TreeNode* tree, char* passedFile)
{
   code = fopen(passedFile, "w");

   // header comment
   emitComment((char *)"C- compiler version C-F21");
   emitComment((char *)"Built: Dec 3, 2021");
   emitComment((char *)"Author: Nathaniel Osterberg");
   emitComment((char *)"File compiled: ", passedFile); ////////////////// need to add file compiled
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
               emitComment((char *)"Compound Body");
               for(int i = 0; i <= 2; i++)
               {
                  if(tree != NULL)
                  {
                     treeTargetCode(tree->child[i]);
                  }
               }
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
         emitComment((char *)"EXPRESSION");
         switch(tree->subkind.exp)
         {
            case OpK:
               //emitComment((char *)"Op");
               break;
            case ConstantK:
               if(tree->expType == Integer)
               {
                  emitRM((char *)"LDC", 3, tree->attr.value, 6, (char *)"Load integer const");
               }
               break;
            case IdK:
               //emitComment((char *)"Id");
               break;
            case AssignK:
               //emitComment((char *)"Assign");
               break;
            case InitK:
               /*emitComment((char *)"INIT");
               emitRM((char *)"LDA", 1, 0, 0, (char *)"set first frame at end of globals");
               emitRM((char *)"ST", 1, 0, 1, "store old fp (point to self)");
               emitComment((char *)"INIT GLOBALS AND STATICS");
               emitComment((char *)"END INIT GLOBALS AND STATICS");
               emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
               emitRM((char *)"JMP", 7, -9, 7, "Jump to main");
               emitRM((char *)"HALT", 0, 0, 0, "DONE!");
               emitComment((char *)"END INIT");*/
               break;
            case CallK:
               emitComment((char *)"CALL output");

               emitRM((char *)"ST", 1, toffset, 1, (char *)"Store fp in ghost frame for", tree->attr.name);
               tmp = tree->child[0]; // parameter
               while(tmp != NULL)
               {
                  emitComment((char *)"Param ///////", tree->attr.name);
                  if(tmp->subkind.exp == ConstantK)
                  {
                     if(tmp->expType == Integer)
                     {
                        emitRM((char *)"LDC", 3, tmp->attr.value, 6, (char *)"Load integer constant");
                     }
                  }
                  emitRM((char *)"ST", 3, ghost - 2, 1, (char *)"Push parameter"); // endOfFrame - 2, 
                  tmp = tmp->sibling;
               }
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
               //emitRM((char *)"JMP", 7, 43, 7, (char *)"Jump to init [backpatch]");
               toffset = ghost;
               emitComment((char *)"INIT");
               emitRM((char *)"LDA", 1, 0, 0, (char *)"set first frame at end of globals");
               emitRM((char *)"ST", 1, 0, 1, "store old fp (point to self)");
               emitComment((char *)"INIT GLOBALS AND STATICS");
               emitComment((char *)"END INIT GLOBALS AND STATICS");
               emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
               emitRM((char *)"JMP", 7, -10, 7, "Jump to main");
               emitRM((char *)"HALT", 0, 0, 0, "DONE!");
               emitComment((char *)"END INIT");
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
   emitRM((char *)"JMP", 7, 43, 7, (char *)"Jump to init [backpatch]");

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
}