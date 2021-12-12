#include <string.h>
#include "codeGen.h"
#include "emitcode.h"
#include "parser.tab.h"

extern SymbolTable st;
FILE * code;
int toffset = 0;
int temp1;
TreeNode* temp;
bool Globals = false;
int paramCount = 0;
bool store;
bool arrayOp = false;
int loopBegin = 0; // attempt to do break stuff
int whileLoops[10]; // more break stuff
int breakloc = 0;

void codeGenGlobalsAndStatics(TreeNode *t){
   
   if (t == NULL){
      return;
   }
   
   if (t->nodekind == DeclK && t->subkind.decl == VarK){
      if (t->memType==Global){
         //TreeNode* found = (TreeNode*)symbolTable.lookup((char *)t->attr.name);
         if(t->isArray){
         
            emitRM((char *)"LDC", 3, t->memSize-1, 6,(char *)"load saved size of array",(char *)t->attr.name);
            emitRM((char *)"ST", 3, t->offset+1, 0,(char *)"save size of array",(char *)t->attr.name);
         }
         else{
            treeTargetCode(t->child[0]);
            emitRM((char *)"ST", 3, t->offset, 0,(char *)"1Store variable",(char *)t->attr.name);
            //tOffset -= t->memSize;
         }
         //numGlobals++;
      }
   }
   
   for(int i = 0; i < 3; i++) {
      codeGenGlobalsAndStatics(t->child[i]);
   }
   codeGenGlobalsAndStatics(t->sibling);
}
void codeGen(TreeNode* tree, char* passedFile)
{
   int i = 0;
   int globalEnd = 0;
   code = fopen(passedFile, "w");

   // header comment
   emitComment((char *)"C- compiler version C-F21");
   emitComment((char *)"Built: Dec 3, 2021");
   emitComment((char *)"Author: Nathaniel Osterberg");
   emitComment((char *)"File compiled: ", passedFile); ////////////////// need to add file compiled
   emitComment((char *)"");
   temp = tree;
   while(temp != NULL)
   {
      if(temp->subkind.decl == VarK)
      {
         globalEnd -= temp->memSize;
      }
      temp = temp->sibling;
   }
   emitSkip(1); // start at one
   codeGenIO();
   emitSkip(0);
   treeTargetCode(tree);


   backPatchAJumpToHere(0, (char *)"Jump to init [backpatch]");
   emitComment((char *)"INIT");
   //emitRM((char *)"LD", 0, 0, 0, (char *)"Set the global pointer");
   emitRM((char *)"LDA", 1, globalEnd, 0, (char *)"Set first frame at end of globals");
   emitRM((char *)"ST", 1, 0, 1, (char *)"Store old fp (point to self)");
   emitComment((char *)"INIT GLOBALS AND STATICS");
   codeGenGlobalsAndStatics(tree);
   temp = tree;
   //initialize globals function
   emitComment((char *)"END INIT GLOBALS AND STATICS");
   emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
   // find main offset
   temp = (treeNode *)st.lookupGlobal("main");
   emitGotoAbs(temp->offset, (char *)"Jump to main");
   emitRO((char *)"HALT", 0, 0, 0, (char *)"Done!");
   emitComment((char *)"END INIT");
   fclose(code);
   //codeGenMain(tree);
}

void treeTargetCode(TreeNode* tree)
{
   char* name;
   int dif, cur, dif2;
   int skiploc;

   TreeNode *tmp = NULL;

   while(tree != NULL)
   {
      if(tree->nodekind == StmtK)
      {
         switch(tree->subkind.stmt)
         {
            case NullK:
               emitComment((char *)"NULL");
               break;
            case IfK:{
               store = false;
               emitComment((char *)("IF"));
               treeTargetCode(tree->child[0]);
               emitComment((char *)("THEN"));
               int elseLocation = 0;
               int thenLocation = emitSkip(1);
               treeTargetCode(tree->child[1]);
               if(tree->child[2] != NULL)
               {
                  elseLocation = emitSkip(1);
               }
               backPatchAJumpToHere((char *)("JZR"),3,thenLocation, (char *)("Jump around the THEN if false [backpatch]"));
               if(tree->child[2] != NULL)
               {
                  emitComment((char *)("ELSE"));
                  treeTargetCode(tree->child[2]);
                  backPatchAJumpToHere((char *)("JMP"),7,elseLocation, (char *)("Jump around the ELSE [backpatch]"));
               }
               emitComment((char *)("END IF"));
               break;}
            case WhileK:{
               int backpatch = emitSkip(0);
               store = false;
               //printf("main address %p\n", (void *) &mainLookup);
               emitComment((char *)("WHILE"));
               treeTargetCode(tree->child[0]);
               int backBreak = breakloc;
               breakloc = emitSkip(0);
               //toffset++;
               //emitComment((char *)("TOFF inc:"), toffset);
               //emitRM((char *)"LD",4,tree->memOffset,1,(char *)("Pop left into acl"));
               //emitRO((char *)"TLT",3,4,3,(char *)("Op"), (char *)tree->child[0]->attr.name);
               emitRM((char *)"JNZ",3,1,7,(char *)("Jump to while part"));
               emitComment((char *)("DO"));
               int whileJump = emitSkip(1);
               treeTargetCode(tree->child[1]);
               //toffset--;
               //emitComment((char *)("TOFF dec:"), toffset);
               emitRM((char *)"JMP",7,backpatch-emitSkip(0)-1,7,(char *)("go to beginning of loop"));
               int jumpLocation = emitSkip(0);
               backPatchAJumpToHere(whileJump, (char *)("Jump past loop [backpatch]"));
               breakloc = backBreak;
               emitNewLoc(jumpLocation);
               emitComment((char *)("END WHILE"));
               break;}
            case ForK:
               //emitComment((char *)"For");
               break;
            case CompoundK:{
               int ghost = toffset;
               emitComment((char *)"COMPOUND");
               emitComment((char *)"TOFF set:", toffset);
               for(int i = 0; i <= 2; i++)
               {
                  if(tree != NULL)
                  {
                     treeTargetCode(tree->child[i]);
                  }
               }
               toffset = tree->memSize;
               emitComment((char *)"Compound Body");
               toffset = ghost;
               emitComment((char *)"TOFF set:", toffset);
               emitComment((char *)"END COMPOUND");
               break;}
            case ReturnK:
               emitComment((char *)"RETURN");
               if(tree->child[0] != NULL)
               {
                  if(tree->isArray == true)
                  {
                     if(!strcmp(tree->child[0]->attr.name, "["))
                     {

                     }
                     else
                     {
                        store = false;
                        treeTargetCode(tree->child[0]);
                        emitRM((char *)"LDA", 2, 0, 3, (char *)"Copy result to return register");
                     }
                  }
                  else
                  {
                     store = false;
                     treeTargetCode(tree->child[0]);
                     emitRM((char *)"LDA", 2, 0, 3, (char *)"Copy result to return register");
                  }
               }
               emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
               emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
               emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
               break;
            case BreakK:
               emitComment((char *)"BREAK");
               emitRM((char *)"JMP", 7, breakloc - emitSkip(0), 7, (char *)"break");
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
         int pCount = 0;
         emitComment((char *)"EXPRESSION");
         switch(tree->subkind.exp)
         {
            case OpK:
               //emitComment((char *)"Op");
               /*for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[i] != NULL)
                  {
                     treeTargetCode(tree->child[i]);
                  }
               }*/
               if(tree->child[1] != NULL)
               {
                  binaryOpCode(tree);
               }
               else
               {
                  treeTargetCode(tree->child[0]);
                  unaryOpCode(tree);
               }
               break;
            case ConstantK:
               if(tree->expType == Integer)
               {
                  emitRM((char *)"LDC", 3, tree->attr.value, 6, (char *)"Load integer const");
               }
               else if(tree->expType == Boolean)
               {
                  if(!strcmp(tree->attr.name, "true"))
                  {
                     emitRM((char *)"LDC", 3, 1, 6, (char *)"Load boolean const");
                  }
                  else
                  {
                     emitRM((char *)"LDC", 3, 0, 6, (char *)"Load boolean const");
                  }
               }
               else if(tree->expType == Char)
               {
                  emitRM((char *)"LDC", 3, tree->cvalue, 6, (char *)"Load character const");
               }
               break;
            case IdK:
               //emitComment((char *)"Id");
               if(store == true)
               {
                  if(tree->memType == Global)
                  {
                     if(tree->isArray)
                     {
                        emitRM((char *)"ST", 3, toffset, 1, (char *)"Push index");
                        store = false;
                     }
                     else
                     {
                        emitRM((char *)"ST", 3, tree->offset, 0, (char *)"Store variable", tree->attr.name);
                        store = false;
                     }
                  }
                  else if(tree->memType == Local)
                  {
                     if(tree->isArray)
                     {
                        
                     }
                     else
                     {
                        emitRM((char *)"ST", 3, tree->offset, 1, (char *)"Store variable", tree->attr.name);
                        store = false;
                     }
                  }
                  else if(tree->memType == LocalStatic)
                  {
                     if(tree->isArray)
                     {

                     }
                     else
                     {
                        emitRM((char *)"ST", 3, tree->offset, 0, (char *)"Store variable", tree->attr.name);
                     }
                  }
               }
               else // if store is false
               {
                  if(tree->memType == Global)
                  {
                     if(tree->isArray)
                     {

                     }
                     else
                     {
                        emitRM((char *)"LD", 3, tree->offset, 0, (char *)"Load variable", tree->attr.name);
                     }
                  }
                  else if(tree->memType == Local)
                  {
                     if(tree->isArray)
                     {

                     }
                     else
                     {
                        emitRM((char *)"LD", 3, tree->offset, 1, (char *)"Load variable", tree->attr.name);
                     }
                  }
                  else if(tree->memType == LocalStatic)
                  {
                     if(tree->isArray)
                     {

                     }
                     else
                     {

                     }
                  }
                  else if(tree->memType == Parameter)
                  {
                     emitRM((char *)"LD", 3, tree->offset, 1, (char *)"Load variable", tree->attr.name);
                  }
               }
               break;
            case AssignK:
               store = false;
               emitComment((char *)"Assign");
               if(tree->child[1] != NULL)
               {
                  binaryAsgnCode(tree);
               }
               else
               {
                  unaryAsgnCode(tree);
               }
               //emitRM((char *)"LDC", )
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
            case CallK:{
               TreeNode* pchild = tree->child[0];
               paramCount = 0;
               int ghost = toffset;
               TreeNode* function = (TreeNode*)st.lookup(tree->attr.name);
               while(pchild != NULL)
               {
                  pchild = pchild->sibling;
                  paramCount++;
                  pCount++;
               }
               emitComment((char *)"CALL", tree->attr.name);
               emitRM((char *)"ST", 1, toffset, 1, (char *)"Store fp in ghost frame for", tree->attr.name);
               if(paramCount == 0)
               {
                  //toffset--;
                  //emitComment((char *)"TOFF dec:", toffset);
                  //toffset--;
                  //emitComment((char *)"TOFF dec:", toffset);

                  tmp = tree->child[0]; // parameter
                  emitComment((char *)"Param end");
                  store = false;
                  //printf("tree->attr.name %s LINE %i\n", tree->attr.name, tree->lineno);
                  emitRM((char *)"LDA", 1, ghost, 1, (char *)"Ghost frame becomes new active frame");
                  emitRM((char *)"LDA", 3, 1, 7, (char *)"  Return address in ac");
                  int intCurrent = emitSkip(0);
                  emitRM((char *)"JMP", 7, function->offset - intCurrent - 1, 7, (char *)"CALL", tree->attr.name); ///////////////////////////////////////
                  emitRM((char *)"LDA", 3, 0, 2, (char *)"  Save the result in ac");
                  toffset = ghost;
                  emitComment((char *)"Call end", tree->attr.name);
               }
               else if(paramCount == 1)
               {
                  toffset = toffset - pCount;
                  emitComment((char *)"TOFF dec:", toffset); // good
                  if(tree->child[0]->isArray == true)
                  {
                     
                  }
                  else
                  {
                     toffset = toffset - pCount;
                     emitComment((char *)"TOFF dec:", toffset); // good
                     emitComment((char *)"Param", paramCount);
                     store = false;
                     treeTargetCode(tree->child[0]);
                     //emitComment((char *)"HERE");
                     emitRM((char *)"ST", 3, toffset, 1, (char *)"Push parameter"); // endOfFrame - 2
                  }
                  tmp = tree->child[0]; // parameter
                  emitComment((char *)"Param end");
                  emitRM((char *)"LDA", 1, ghost, 1, (char *)"Ghost frame becomes new active frame");
                  function = (treeNode *)st.lookup(tree->attr.name); // output
                  emitRM((char *)"LDA", 3, 1, 7, (char *)"  Return address in ac");
                  int intCurrent = emitSkip(0);
                  if(!strcmp(tree->attr.name, "output") || !strcmp(tree->attr.name, "outputb") || !strcmp(tree->attr.name, "outputc"))
                  {
                     //printf("offset %i intCurrent %i\n", function->offset, intCurrent);
                     emitRM((char *)"JMP", 7, function->offset - intCurrent, 7, (char *)"CALL", tree->attr.name);
                  }
                  else
                  {
                     emitRM((char *)"JMP", 7, function->offset - intCurrent - 1, 7, (char *)"CALL", tree->attr.name); ///////////////////////////////////////
                  }
                  emitRM((char *)"LDA", 3, 0, 2, (char *)"  Save the result in ac");
                  toffset = ghost;
                  emitComment((char *)"Call end", tree->attr.name);
               }
               else if(paramCount > 1)
               {
                  emitRM((char *)"ST", 1, toffset, 1, (char *)"Store fp in ghost frame for", tree->attr.name);
               }
               //tmp = tree->child[0]; // parameter
               //emitComment((char *)"Param end");
               /*emitRM((char *)"LDA", 1, ghost, 1, (char *)"Ghost frame becomes new active frame");
               function = (treeNode *)st.lookup(tree->attr.name); // output
               emitRM((char *)"LDA", 3, 1, 7, (char *)"  Return address in ac");
               int intCurrent = emitSkip(0);
               emitRM((char *)"JMP", 7, function->offset - intCurrent, 7, (char *)"CALL", tree->attr.name); ///////////////////////////////////////
               emitRM((char *)"LDA", 3, 0, 2, (char *)"  Save the result in ac");
               toffset = ghost;
               emitComment((char *)"Call end", tree->attr.name);*/
               break;}
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
                  if(tree->child[0] != NULL)
                  {
                     treeTargetCode(tree->child[0]);
                     emitRM((char *)"ST", 3, toffset, 1, (char *)"store variable", tree->attr.name);
                  }
                  //toffset -= tree->memSize;
                  //emitComment((char *)"TOFF dec:", toffset);
               }
               if(tree->isArray == true)
               {
                  int ghost = toffset;
                  //emitComment((char *)"HERE +++++++++++++++++++++++\n");
                  //printf("tree->attr.name %s\n", tree->attr.name);
                  if(tree != NULL)
                  {
                     //treeTargetCode(tree->child[0]); ///////////////////////////////////
                     toffset = tree->memSize;
                     emitRM((char *)"LDC", 3, tree->memSize - 1, 6,(char *)"  load size of array",(char *)tree->attr.name);
                     toffset = ghost;
                     emitRM((char *)"ST", 3, toffset, 1,(char *)"save size of array",(char *)tree->attr.name);
                     //emitComment((char *)"TOFF dec:", toffset); ///////////////
                  }
                  toffset -= tree->memSize;
               }
               else
               {
                  //emitComment((char *)"Var");
                  if(tree->child[0] != NULL)
                  {
                     treeTargetCode(tree->child[0]);
                     emitRM((char *)"ST", 3, toffset, 1, (char *)"store variable", tree->attr.name);
                  }
                  toffset -= tree->memSize;
                  emitComment((char *)"TOFF dec:", toffset);
               }
               break;
            case FuncK:{
               Globals = true;
               toffset = -2;
               //if(tree->child[1] != NULL)
                  //printf("IN FUNCK tree->child[0]->offset %i\n", tree->child[0]->offset);
               tree->offset = emitSkip(0);
               emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");
               emitComment((char *)"FUNCTION", tree->attr.name);
               emitComment((char*)"TOFF set:", toffset);
               emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
               tmp = tree->child[0];
               while(tmp != NULL)
               {
                  toffset--;
                  tmp = tmp->sibling;
               }
               int ghost = toffset;
               //printf("%s\n", tree->child[1]->attr.name);
               /*if (tree->child[1]!=NULL){
                  //treeTargetCode(tree->child[1]);
               }*/
               for (int i = 0; i<3; i++){
                  treeTargetCode(tree->child[i]);
               }
               emitComment((char *)"Add standard closing in case there is no return statement");
               emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
               emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
               emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
               emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
               emitComment((char *)"END FUNCTION", tree->attr.name);
               //emitRM((char *)"JMP", 7, 43, 7, (char *)"Jump to init [backpatch]");
               toffset = ghost;
               /*emitComment((char *)"INIT");
               emitRM((char *)"LDA", 1, 0, 0, (char *)"set first frame at end of globals");
               emitRM((char *)"ST", 1, 0, 1, (char *)"store old fp (point to self)");
               emitComment((char *)"INIT GLOBALS AND STATICS");
               emitComment((char *)"END INIT GLOBALS AND STATICS");
               emitRM((char *)"LDA", 3, 1, 7, (char *)"Return address in ac");
               emitRM((char *)"JMP", 7, -10, 7, (char *)"Jump to main");
               emitRO((char *)"HALT", 0, 0, 0, (char *)"DONE!");
               emitComment((char *)"END INIT");*/
               //emitComment((char *)"Function", tree->attr.name);
               break;}
            case ParamK:
               for(int i = 0; i < 2; i++)
               {
                  treeTargetCode(tree->child[i]);
               }
               /*if(tree->isArray == true)
               {
                  //emitComment((char *)"Param array");
               }
               else
               {
                  //emitComment((char *)"Param");
               }*/
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
      treeTargetCode(tree->child[0]);
      emitRO((char *)"NEG", 3, 3, 3, (char *)"Op Unary -");
   }
   else if(!strcmp(tree->attr.name, "?"))
   {
      emitRO((char *)"RND", 3, 3, 6, (char *)"Op ?");
   }
   else if(!strcmp(tree->attr.name, "*"))
   {
      if(tree->memType == Global)
      {
         emitRM((char *)"LDA", 3, tree->offset, isGlobal(tree), (char *)"Load address of base of array", (char *)tree->attr.name);
      }
      else if(tree->memType == Parameter)
      {
         emitRM((char *)"LDA", 3, tree->offset, isGlobal(tree), (char *)"Load address of base of array", (char *)tree->attr.name);
      }
      else
      {
         emitRM((char *)"LDA", 3, tree->offset, isGlobal(tree), (char *)"Load address of base of array", (char *)tree->attr.name);
      }
      emitRM((char *)"LD", 3, 1, 3, (char *)"Load array size");
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
   // if it breaks b files, most likely add additional checks here. 
   if (tree->child[0]->subkind.exp!= ConstantK && tree->child[1]->subkind.exp!=ConstantK)
   {
      if(!strcmp(tree->child[0]->attr.name, "[") && !strcmp(tree->child[1]->attr.name, "["))
      {
         arrayOp = true;
      }
   }

   emitComment((char *)"OpK");
   if(!strcmp(tree->attr.name, "or"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"OR", 3, 4, 3, (char *)"Op or");
   }
   else if(!strcmp(tree->attr.name, "and"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"AND", 3, 4, 3, (char *)"Op and");
   }
   else if(!strcmp(tree->attr.name, "<"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TLT", 3, 4, 3, (char *)"Op <");
   }
   else if(!strcmp(tree->attr.name, ">"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TGT", 3, 4, 3, (char *)"Op >");
   }
   else if(!strcmp(tree->attr.name, "="))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TEQ", 3, 4, 3, (char *)"Op =");
   }
   else if(!strcmp(tree->attr.name, ">="))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TGE", 3, 4, 3, (char *)"Op >=");
   }
   else if(!strcmp(tree->attr.name, "<="))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TLE", 3, 4, 3, (char *)"Op <=");
   }
   else if(!strcmp(tree->attr.name, "><"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"TNE", 3, 4, 3, (char *)"Op ><");
   }
   else if(!strcmp(tree->attr.name, "+")) ///////////////////////////
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         toffset++;
         emitComment((char *)"TOFF inc:", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop left into ac1");
      emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +");
   }
   else if(!strcmp(tree->attr.name, "-")) ///////////////////////////
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         toffset++;
         emitComment((char *)"TOFF inc", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -");
   }
   else if(!strcmp(tree->attr.name, "*")) //////////////////////////
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec:////", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         toffset++;
         emitComment((char *)"TOFF inc", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop left into ac1");
      emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *");
   }
   else if(!strcmp(tree->attr.name, "/")) /////////////////////////
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      toffset--;
      emitComment((char *)"TOFF dec://///", toffset);
      if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }
      treeTargetCode(tree->child[1]);
      if(arrayOp == true)
      {
         toffset++;
         emitComment((char *)"TOFF inc", toffset);
      }
      toffset++;
      emitComment((char *)"TOFF inc://///", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /");
   }
   else if(!strcmp(tree->attr.name, "%"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"ST", 3, toffset, 1, (char *)"Push left side");
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Load left into ac1");
      emitRO((char *)"DIV", 5, 4, 3, (char *)"Op %");
      emitRO((char *)"MUL", 5, 5, 3, (char *)"");
      emitRO((char *)"SUB", 3, 4, 5, (char *)"");
   }
   else if(!strcmp(tree->attr.name, "["))
   {

      int ghost = toffset;
      int index = emitSkip(0);
      if(tree->child[0]->isArray == true)
      {
         emitRM((char *)"LDA", 3, tree->child[0]->offset, isGlobal(tree->child[0]), (char *)"Load address of base of array");
      }
      
      emitRM((char *)"ST", 3, toffset, 1, (char *)"   Push left side");
      /*if(arrayOp == true)
      {
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
      }*/
      toffset--;
      emitComment((char *)"TOFF dec:", toffset);
      treeTargetCode(tree->child[1]);
      toffset++;
      emitComment((char *)"TOFF inc:", toffset);
      emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop left into ac1");
      emitRO((char *)"SUB", 3, 4, 3, (char *)"Compute location from index");
      emitRM((char *)"LD", 3, 0, 3, (char *)"Load array element");
      /*if(arrayOp == true)
      {
         toffset++;
         emitComment((char *)"TOFF inc:", toffset);
         arrayOp = false;
      }*/
      //treeTargetCode(tree->child[1]);
      //emitRM((char *)"ST", 3, -2, 1, (char *)"Push index");


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
      treeTargetCode(tree->child[0]);
      emitRO((char *)"NEG", 3, 3, 3, (char *)"Op unary -");
   }
   else if(!strcmp(tree->attr.name, "*"))
   {

   }
   else if(!strcmp(tree->attr.name, "?"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"RND", 3, 3, 6, (char *)"Op ?");
   }
   else if(!strcmp(tree->attr.name, "not"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDC", 4, 1, 6, (char *)"Load 1");
      emitRO((char *)"XOR", 3, 3, 4, (char *)"Op not");
   }
   else if(!strcmp(tree->attr.name, "++"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Inc");
      emitRM((char *)"ST", 3, tree->child[0]->offset, 1, (char *)"Store var ++++++++++++++++++++++");
   }
   else if(!strcmp(tree->attr.name, "--"))
   {
      treeTargetCode(tree->child[0]);
      emitRM((char *)"LDA", 3, 1, 3, (char *)"Dec");
      emitRM((char *)"ST", 3, tree->child[0]->offset, 1, (char *)"Store var ----------------------");
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
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"ADD", 3, 4, 3, (char *)"Op +=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "-="))
   {
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"SUB", 3, 4, 3, (char *)"Op -=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "*="))
   {
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"MUL", 3, 4, 3, (char *)"Op *=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, "/="))
   {
      treeTargetCode(tree->child[1]);
      emitRM((char *)"LD", 4, tree->child[0]->offset, fp, (char *) "Load LHS");
      emitRO((char *)"DIV", 3, 4, 3, (char *)"Op /=");
      emitRM((char *)"ST", 3, tree->child[0]->offset, fp, (char *)"Store left ");
   }
   else if(!strcmp(tree->attr.name, ":="))
   {
      if(!strcmp(tree->child[0]->attr.name, "["))
      {
         
         treeTargetCode(tree->child[0]->child[1]);
         emitRM((char *)"ST", 3, toffset, 1, (char *)"Push index");
         toffset--;
         emitComment((char *)"TOFF dec:", toffset);
         treeTargetCode(tree->child[1]);
         toffset++;
         emitComment((char *)"TOFF inc:", toffset);
         emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop index");
         if(tree->child[0]->child[0]->memType == Global)
         {
            emitRM((char *)"LDA", 5, tree->child[0]->child[0]->offset, 0, (char *)"Load address of base of array", tree->child[0]->child[0]->attr.name);
         }
         else
         {
            emitRM((char *)"LDA", 5, tree->child[0]->child[0]->offset, 1, (char *)"Load address of base of array", tree->child[0]->child[0]->attr.name);
         }
         emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value", tree->child[0]->child[0]->attr.name);
         emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", tree->child[0]->child[0]->attr.name);
      }
      else
      {
         treeTargetCode(tree->child[1]);
         store = true;
         treeTargetCode(tree->child[0]);
      }
      /*treeTargetCode(tree);*/
      /*if(tree->child[0] != NULL)
      {
         if(!strcmp(tree->child[0]->attr.name, "["))
         {
            if(tree->child[1] != NULL)
            {
               if(tree->child[1]->subkind.exp != ConstantK)
               {
                  if(!strcmp(tree->child[1]->attr.name, "["))
                  {
                     int index = emitSkip(0);
                     if(tree->child[0]->child[1] != NULL)
                        treeTargetCode(tree->child[0]->child[1]);
                     store = true;
                     if(tree->child[0]->child[0] != NULL)
                        treeTargetCode(tree->child[0]->child[0]);
                     store = false;
                     toffset--;
                     emitComment((char *)"TOFF dec:", toffset);
                     treeTargetCode(tree->child[1]);
                     toffset++;
                     emitComment((char *)"TOFF inc:", toffset);
                     if(tree->child[0]->child[0] != NULL && tree->child[0]->child[0]->isArray)
                     {
                        emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop index");
                        emitRM((char *)"LDA", 5, tree->child[0]->child[0]->offset, isGlobal(tree->child[0]->child[0]), (char *)"Load address of base of array", tree->child[0]->child[0]->attr.name); // pop index ---> toffset
                        emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");
                        emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", tree->child[0]->child[0]->attr.name);
                     }
                     
                  }
                  else
                  {
                     if(tree->child[1]->subkind.exp == OpK)
                     {
                        arrayOp = true;
                        printf("dec : %i\n", toffset);
                     }
                     else
                     {
                        arrayOp = false;
                     }
                  }
               }
               else
               {*/
                  //printf("tree->child[0]->subkind.exp %i, name %s\n", tree->child[0]->subkind.exp, tree->child[0]->attr.name);
                  /*if(tree->child[1]->subkind.exp == OpK)
                  {
                     arrayOp = true;
                  }
                  else
                  {
                     arrayOp = false;
                  }*/
                  /*int index = emitSkip(0);
                  if(tree->child[0]->child[1] != NULL)
                     treeTargetCode(tree->child[0]->child[1]);
                  store = true;
                  if(tree->child[0]->child[0] != NULL)
                     treeTargetCode(tree->child[0]->child[0]);
                  treeTargetCode(tree->child[1]);
                  emitRM((char *)"LD", 4, toffset, 1, (char *)"Pop index");
                  emitRM((char *)"LDA", 5, tree->child[0]->child[0]->offset, isGlobal(tree->child[0]->child[0]), (char *)"Load address of base of array", tree->child[0]->child[0]->attr.name); // pop index ---> toffset
                  emitRO((char *)"SUB", 5, 5, 4, (char *)"Compute offset of value");
                  emitRM((char *)"ST", 3, 0, 5, (char *)"Store variable", tree->child[0]->child[0]->attr.name);
                  // SUB 5 5 4
                  // ST 3 0 5
               }
            }
         }
         else
         {
            treeTargetCode(tree->child[1]);
            store = true;
            treeTargetCode(tree->child[0]);
         }
      }*/
   }
   else
   {
      printf("NOT IN TARGET BINARY ASSIGNS\n");
   }
}

void codeGenIO()
{

   //emitSkip(1);
   // INPUT INT
   temp = st.lookupNode("input");
   temp->offset = emitSkip(0) - 1;
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
   temp = st.lookupNode("output");
   temp->offset = emitSkip(0) - 1;
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

   temp = st.lookupNode("inputb");
   temp->offset = emitSkip(0) - 1;

   emitComment((char *)"FUNCTION inputb");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"INB", 2, 2, 2, (char *)"Grab bool input");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION inputb");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   temp = st.lookupNode("outputb");
   temp->offset = emitSkip(0) - 1;

   emitComment((char *)"FUNCTION outputb");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRM((char *)"LD", 3, -2, 1, (char *)"Load return address");
   emitRO((char *)"OUTB", 3, 3, 3, (char *)"Output integer");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION outputb");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   temp = st.lookupNode("inputc");
   temp->offset = emitSkip(0) - 1;

   emitComment((char *)"FUNCTION inputc");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRO((char *)"INC", 2, 2, 2, (char *)"Grab bool input");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION inputc");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   temp = st.lookupNode("outputc");
   temp->offset = emitSkip(0) - 1;
   
   emitComment((char *)"FUNCTION outputc");
   emitRM((char *)"ST", 3, -1, 1, (char *)"Store return address");
   emitRM((char *)"LD", 3, -2, 1, (char *)"Load return address");
   emitRO((char *)"OUTC", 3, 3, 3, (char *)"Output integer");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"End FUNCTION outputc");
   emitComment((char *)"");
   emitComment((char *)"** ** ** ** ** ** ** ** ** ** ** **");

   temp = st.lookupNode("outnl");
   temp->offset = emitSkip(0);

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
   printf("test\n");
   emitComment((char *)"Add standard closing in case there is no return statement");
   emitRM((char *)"LDC", 2, 0, 6, (char *)"Set return value to 0");
   emitRM((char *)"LD", 3, -1, 1, (char *)"Load return address");
   emitRM((char *)"LD", 1, 0, 1, (char *)"Adjust fp");
   emitRM((char *)"JMP", 7, 0, 3, (char *)"Return");
   emitComment((char *)"END FUNCTION", t->attr.name);
}

int isGlobal(TreeNode *tree)
{
   //TreeNode * found = (TreeNode *)st.lookup((char *)tree->attr.name);

   //if(found != NULL)
   //{
      if(tree->memType == Global)
         return 0;
      else
         return 1;
   //}
   return 1;
}
