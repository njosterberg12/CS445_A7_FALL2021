#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "semantic.h"
#include "symbolTable.h"
#include "parser.tab.h"
#include "treeNodes.h"
//#include "errors.c"

extern int numErrors, numWarnings, Loffset, Goffset;
extern SymbolTable st;
bool err;
bool initialize = false;
bool NEW_SCOPE = false;
bool inCall = false;
bool returnFlag = false;
bool inRange = false;
int bug = 0;
int loopDepth = 0;
char *withinScope;
extern bool m;
int funcSize = -2;
extern void countSymbols(std::string sym, void *ptr);


void analyze(TreeNode *tree)
{
   //printf("HERE2 LINE %i\n", tree->lineno);
   TreeNode *tmp, *tmp2;
   bool fWhile = false;
   
   //printf("HERE LINE %i", tree->lineno);
   while (tree != NULL)
   {
      //printf("analyze %d \n", tree->lineno);
      if(tree->nodekind == StmtK)
      {
         //printf("analyze %d %s\n", tree->lineno, tree->attr.name);
         switch(tree->subkind.stmt)
         {
            case NullK:
               break;
            case IfK:{
               NEW_SCOPE = true;
               int tempOffset = Loffset;
               st.enter((char*)"if");
               for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[0] != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }
               if(tree->child[0]->subkind.exp == IdK)
               {
                  //printf("HERE\n");
                  //printf("child[0]->subkind.exp %i LINE %i\n", tree->child[0]->subkind.exp, tree->lineno);

                  if(tree->child[0]->expType != Boolean && !tree->child[0]->isErr)
                  {
                     printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[0]->expType));
                     numErrors++;   
                  }
               }
               //printf("tree->child[0]->subkind.exp %i LINE %i\n", tree->child[0]->subkind.exp, tree->lineno);
               //printf("tree->child[0]-attr.name %s\n", tree->child[0]->attr.name);
               if(tree->child[0]->subkind.exp == ConstantK || tree->child[0]->subkind.exp == AssignK)
               {
                  if(tree->child[0]->expType != Boolean && !tree->child[0]->isErr)
                  {
                     printf("ERROR(%d): Expecting Boolean test condition in if statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[0]->expType));
                     numErrors++;
                  }
               }
               
               if(tree->child[0]->isArray == true)
               {
                  printf("ERROR(%d): Cannot use array as test condition in if statement.\n", tree->lineno);
                  numErrors++;
               }
               st.applyToAll(countSymbols);
               NEW_SCOPE = false;
               st.leave();
               tree->memSize = Loffset;
               Loffset = tempOffset;
               break;}
            case WhileK:{
               loopDepth++;
               NEW_SCOPE = true;
               int tempOffset = Loffset;
               st.enter((char*)"simple_While");
               //}
               for(int i = 0; i <= 1; i++)
               {
                  if(tree->child[i] != NULL)
                     analyze(tree->child[i]);
               }
               if(tree->child[0]->expType != Boolean && !tree->child[0]->isErr)
               {
                  printf("ERROR(%d): Expecting Boolean test condition in while statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[0]->expType));
                  numErrors++;
               }
               if(tree->child[0]->isArray == true)
               {
                  printf("ERROR(%d): Cannot use array as test condition in while statement.\n", tree->lineno);
                  numErrors++;
               }
               st.applyToAll(countSymbols);
               NEW_SCOPE = false;
               loopDepth--;
               st.leave();
               tree->memSize = Loffset;
               Loffset = tempOffset;
               break;}
            case ForK:{
               loopDepth++;
               st.enter((char*)"For");
               NEW_SCOPE = true;
               int tempOffset = Loffset;
               for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[0] != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }   
               if(tree->child[1]->child[0]->expType != Integer && tree->child[1]->child[0]->expType != UndefinedType)
               {
                  printf("ERROR(%d): Expecting type int in position 1 in range of for statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[1]->child[0]->expType));
                  numErrors++;
               }
               if(tree->child[1]->child[1]->expType != Integer && tree->child[1]->child[1]->expType != UndefinedType)
               {
                  printf("ERROR(%d): Expecting type int in position 2 in range of for statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[1]->child[1]->expType));
                  numErrors++;
               }
               if(tree->child[1]->child[2] != NULL)
               {
                  if(tree->child[1]->child[2]->expType != Integer && tree->child[1]->child[2]->expType != UndefinedType /*&& tree->child[1]->child[2]->child[0] != NULL*/)
                  {
                     printf("ERROR(%d): Expecting type int in position 3 in range of for statement but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[1]->child[2]->expType));
                     numErrors++;
                  }
               }
               if(tree->child[1]->child[0]->isArray)
               {
                  printf("ERROR(%d): Cannot use array in position 1 in range of for statement.\n", tree->lineno);
                  numErrors++;
               }
               if(tree->child[1]->child[1]->isArray)
               {
                  printf("ERROR(%d): Cannot use array in position 2 in range of for statement.\n", tree->lineno);
                  numErrors++;
               }
               if(tree->child[1]->child[2] != NULL)
               {
                  if(tree->child[1]->child[2]->isArray /*&& && tree->child[1]->child[2]->expType != Void*/)
                  {
                     //printf("HERE\n");
                     printf("ERROR(%d): Cannot use array in position 3 in range of for statement.\n", tree->lineno);
                     numErrors++;
                  }
               }
               NEW_SCOPE = false;
               st.leave();
               tree->memType = None;
               tree->memSize = Loffset;
               Loffset = tempOffset;
               loopDepth--;
               break;}
            case CompoundK:{
               int tempOffset;
               bool tempScope = NEW_SCOPE;
               if(!NEW_SCOPE)
               {
                  st.enter((char*)"compound");
                  tempOffset = Loffset;
               }
               else
                  NEW_SCOPE = false;
               for(int i = 0; i <= 2; i++)
               {
                  if(tree != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }
               //st.applyToAll(wasUsed);
               tree->memType = None;
               tree->memSize = Loffset;

               if(!tempScope)
               {
                  st.applyToAll(countSymbols);
                  
                  Loffset = tempOffset;
                  st.leave();
               }
               break;}
            case ReturnK:
               returnFlag = true;
               for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[0] != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }

               tmp2 = st.lookupNode(withinScope); 

               if(tree->child[0] != NULL && tree->child[0]->nodekind == ExpK && tree->child[0]->subkind.exp == IdK) // for returning an ID
               {
                  //analyze(tree->child[0]);
                  tmp = st.lookupNode(tree->child[0]->attr.name);
                  if(tmp != NULL)
                  {
                     tmp->isUsed = true;
                  }
                  if(tmp != NULL && tmp->isArray)
                  {
                     printf("ERROR(%d): Cannot return an array.\n", tree->lineno);
                     numErrors++;
                  }
                  else if(tmp != NULL && tmp2 != NULL && tmp2->expType != tmp->expType && tmp2->expType != Void)
                  {
                     printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but returns type %s.\n", tree->lineno, withinScope, tmp2->lineno, convertExpTypeEnum(tmp2->expType), convertExpTypeEnum(tmp->expType));
                     numErrors++;
                  }
                  else if(tree->child[0] != NULL && tmp2->expType == Void)
                  {
                     //printf("HERE\n");
                     printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n", tree->lineno, withinScope, tmp2->lineno);
                     numErrors++;   
                  }
               }
               if(tree->child[0] != NULL && tree->child[0]->subkind.exp == AssignK && tree->child[0]->child[0] != NULL && tree->child[0]->child[1] != NULL && tree->child[0]->child[0]->isArray == true /*&& tree->child[0]->child[1]->isArray == true*/)
               {
                  printf("ERROR(%d): Cannot return an array.\n", tree->lineno);
                  numErrors++;
               }
               if(tree->child[0] != NULL && tree->child[0]->nodekind == ExpK && tree->child[0]->subkind.exp == ConstantK)
               {
                  if(tree->child[0] != NULL && tmp2 != NULL && tree->child[0]->expType != tmp2->expType && tmp2->expType != Void)
                  {
                     printf("ERROR(%d): Function '%s' at line %d is expecting to return type %s but returns type %s.\n", tree->lineno, withinScope, tmp2->lineno, convertExpTypeEnum(tmp2->expType), convertExpTypeEnum(tree->child[0]->expType));
                     numErrors++;
                  }
               }
               //printf("HERE LINE %i\n", tree->lineno);
               if(tree->child[0] == NULL && tmp2->expType != Void)
               {
                  printf("ERROR(%d): Function '%s' at line %i is expecting to return type %s but return has no value.\n", tree->lineno, withinScope, tmp2->lineno, convertExpTypeEnum(tmp2->expType));
                  numErrors++;
               }
               break;
            case BreakK:
               if(loopDepth == 0) // repeating
               {
                  printf("ERROR(%d): Cannot have a break statement outside of loop.\n", tree->lineno);
                  numErrors++;
               }
               break;
            case RangeK:
               inRange = true;
               for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[i] != NULL)
                  {
                     analyze(tree->child[i]);
                  } 
               }
               break;
            default:
               printf("Unknown Stmt LINE %i", tree->lineno);
               break;
         }
      }
      else if(tree->nodekind == ExpK)
      {
         switch(tree->subkind.exp)
         {
            case OpK:
               for(int i = 0; i <= 2; i++) // 
               {
                  if(tree->child[i] != NULL)
                     analyze(tree->child[i]);
               }
               //checkType(tree);
               if(tree->child[1] != NULL)
               {
                  checkBinaryOps(tree);
                  tree->child[1]->isUsed = true;
               }
               else
               {
                  checkUnaryOps(tree);
                  tree->child[0]->isUsed = true;
               }
               break;
            case ConstantK:
               if(tree->expType == Boolean)
               {
                  //printf("IN BOOLEAN IN CONST\n");
               }
               else if(tree->expType == CharInt)
               {
                  //printf("IN CHARINT IN CONST\n");
               }
               else if(tree->expType == Char && tree->isArray)
               {
                  //printf("IN CHAR IN CONST\n");
                  tree->memType = Global;
                  tree->offset = Goffset - 1;
                  Goffset = Goffset - tree->memSize;
               }
               else
               {

               }
               break;
            case IdK:
               tmp = st.lookupNode(tree->attr.name);
               if(tmp == NULL)
               {
                  printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
                  numErrors++;
                  tree->expType = UndefinedType;
                  tree->isErr = true;
                  err = true;
               }
               else if(tmp != NULL && (tmp->subkind.decl == VarK) || (tmp->subkind.decl == ParamK))
               {
                  tree->expType = tmp->expType; // set ID to its declaration
                  tree->isInit = tmp->isInit;
                  tree->isArray = tmp->isArray;
                  //printf("//////// %s\n", tree->attr.name);
                  tree->isStatic = tmp->isStatic;

                  ///////////////
                  tree->memType = tmp->memType;
                  tree->memSize = tmp->memSize;
                  tree->offset = tmp->offset;

                  checkInit(tree, 0); // checkInit(tree, 1)
               }
               else if(tmp != NULL && tmp->subkind.decl == FuncK)
               {
                  tree->expType = UndefinedType;
                  printf("ERROR(%d): Cannot use function '%s' as a variable.\n", tree->lineno, tree->attr.name);
                  err = true;
                  numErrors++;
                  tree->isErr = true;
                  tmp->isErr = true;
               }
               else if(tmp != NULL)
               {
                  //printf("HERE\n");
                  tmp->isUsed = true;
                  if(tmp->isInit != true && tmp->expType != UndefinedType && tmp->subkind.decl != ParamK) ////////////////////// doesn't do anything
                  {
                     //printf("WARNING(%d): Variable %s may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
                     //numWarnings++;
                  }
               }
               break;
            case AssignK:
                //printf("assignk %s %d\n", tree->attr.name, tree->lineno);
               //checkType(tree->child[0]);
               for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[0] != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }

               if(tree->child[1] == NULL)
               {
                  checkUnaryAsgns(tree);
               }
               else
               {
                  checkBinaryAsgns(tree);
               }
               if(tree->child[0]->subkind.exp == IdK) 
                  tmp = st.lookupNode(tree->child[0]->attr.name);

               if(tree->child[0]->subkind.exp == OpK && tree->child[0]->child[0]->subkind.exp == IdK) {
                  tmp = st.lookupNode(tree->child[0]->child[0]->attr.name);            
               }
               if(tmp != NULL)
               {
                  tmp->isInit = true;
                  tmp->isUsed = true;
               }
               tree->child[0]->isInit = true;
               tree->expType = tree->child[0]->expType;
               break;
            case InitK:
               break;
            case CallK:{
               bool isIO = false;
               for(int i = 0; i <= 2; i++)
               {
                  analyze(tree->child[i]);
                  if(tree->child[i] != NULL)
                  {
                     if(tree->child[i]->subkind.exp == IdK)
                     {
                        TreeNode *param = (TreeNode*)st.lookup(tree->child[i]->attr.name);
                        if(param != NULL)
                        {
                           param->isUsed = true;
                        }
                     }
                     
                  }
               }
               inCall = true;

               tmp = st.lookupNode(tree->attr.name);
               if(!strcmp("output", tree->attr.name) || !strcmp("outputb", tree->attr.name) || !strcmp("outputc", tree->attr.name) || !strcmp("outnl", tree->attr.name) || !strcmp("input", tree->attr.name) || !strcmp("inputb", tree->attr.name) || !strcmp("inputc", tree->attr.name))
               {
                  isIO = true;
               }
               if(tmp != NULL)
               {
                  tmp->isUsed = true;
                  if(!isIO)
                  {
                     tree->expType = tmp->expType;
                  }
                  if(tmp->subkind.decl == VarK || tmp->subkind.decl == ParamK)
                  {
                     printf("ERROR(%d): '%s' is a simple variable and cannot be called.\n", tree->lineno, tree->attr.name);
                     tree->isErr = true;
                     numErrors++;
                  }
               }
               else
               {
                  //printf("HERE\n");
                  printf("ERROR(%d): Symbol '%s' is not declared.\n", tree->lineno, tree->attr.name);
                  numErrors++;
                  tree->isErr = true;                  
                  err = true;
               }
               //analyze(tree->child[0]);
               
               inCall = false;
               if(!tree->isErr)
                  compareParams(tree);
               break;}
            default:
               break;
         }
      }
      else if(tree->nodekind == DeclK)
      {
         if(st.insert(tree->attr.name, (TreeNode*) tree) == 0)
         {
            TreeNode *functionName = (TreeNode*)st.lookup(tree->attr.name);
            printf("ERROR(%d): Symbol '%s' is already declared at line %d.\n", tree->lineno, tree->attr.name, functionName->lineno);
            numErrors++;
         }
         switch(tree->subkind.decl)
         {
            case VarK:
               /*for(int i = 0; i <= 2; i++)
               {
                  if(tree->child[0] != NULL)
                  {
                     analyze(tree->child[i]);
                  }
               }*/
               
               if(tree->child[0] != NULL)
               {
                  analyze(tree->child[0]);
                  if(tmp == NULL)
                  {
                     /*if(tree->child[0]->expType != tree->expType)
                     {
                        printf("ERROR(%d): Variable '%s' is of type %s but is being initialized with ")
                     }*/
                  }
                     
                  if(tree->child[0]->subkind.exp == ConstantK)
                  {
                     if(tree->isArray == true && tree->child[0]->isArray != true)
                     {
                        printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                     }
                     else if(tree->isArray != true && tree->expType != tree->child[0]->expType)
                     {
                        //printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                        printf("ERROR(%d): Initializer for variable '%s' of type %s is of type %s\n", tree->lineno, tree->attr.name, convertExpTypeEnum(tree->expType), convertExpTypeEnum(tree->child[0]->expType));
                        numErrors++;
                        //printf("HERE LINE %i\n", tree->lineno);
                        if(tree->isArray != true && tree->child[0]->isArray == true)
                        {
                           //printf("HERE LINE %i\n", tree->lineno);
                           printf("ERROR(%d): Initializer for variable '%s' requires both operands be arrays or not but variable is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
                           numErrors++;
                        }
                     }
                     //else if(tree->subkind.exp == ConstantK)
                     //{
                     //   printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                     //}
                     //if(tree->isArray != true && tree->child[0])
                  }
                  else if(!tree->child[0]->isConstant)
                  {
                     printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                     numErrors++;
                  }
                  else if(tree->child[0]->subkind.exp == IdK)
                  {
                     printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                     numErrors++;
                  }
                  else if(tree->child[0]->subkind.exp == OpK && tree->subkind.exp != ConstantK)
                  {
                     if(tree->child[0]->child[0]->subkind.exp != ConstantK && tree->child[0]->child[0]->subkind.exp == IdK)
                     {
                        printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                     } 
                     if(!strcmp(tree->child[0]->attr.name, "?") && tree->child[0]->child[0] != NULL && tree->child[0]->child[1] == NULL)
                     {
                        printf("ERROR(%d): Initializer for variable '%s' is not a constant expression.\n", tree->lineno, tree->attr.name);
                        numErrors++;
                     }        
                  }

                  tree->isInit = true;
               }

               if(st.depth() == 1)
               {
                  // this is global
                  tree->memType = Global;
                  tree->isInit = true;
                  if(tree->isArray)
                  {
                     tree->offset = Goffset - 1;
                     Goffset = Goffset - tree->memSize;
                  }
                  else
                  {
                     tree->offset = Goffset;
                     Goffset = Goffset - tree->memSize;
                  }
               }
               else if(tree->isStatic == true)
               {
                  tree->memType = LocalStatic;
                  if(tree->isArray)
                  {
                     tree->offset = Goffset - 1;
                     Goffset = Goffset - tree->memSize;
                  }
                  else
                  {
                     tree->offset = Goffset;
                     Goffset = Goffset - tree->memSize;
                  }
               }
               else
               {
                  tree->memType = Local;
                  if(tree->isArray)
                  {
                     tree->offset = Loffset - 1;
                     Loffset = Loffset - tree->memSize;
                  }
                  else
                  {
                     tree->offset = Loffset;
                     Loffset = Loffset -tree->memSize;
                  }
               } 
               break;
            case FuncK:
               tmp = st.lookupNode(tree->attr.name);
               Loffset = -2;
               if(tmp == NULL)
               {
                  st.insert(tree->attr.name, (TreeNode*) tree);
               }
               st.enter(tree->attr.name);
               NEW_SCOPE = true;
               withinScope = strdup(tree->attr.name);
               returnFlag = false;
               tree->isUsed = true;
               tree->offset = 0;
               Loffset = -2;  // offset before looking at children
               analyze(tree->child[0]);
               analyze(tree->child[1]);
               
               if(tree->expType == Void)
               {             
                  if(tree->child[1] != NULL)
                  {
                     if(tree->child[1]->subkind.stmt == CompoundK)
                     {
                        if(tree->child[1]->child[1] != NULL && tree->child[1]->child[1]->expType != Void) //&& /*tree->child[1]->child[1]->subkind.stmt == ReturnK && tree->child[1]->child[1]->child[0]->expType != tree->expType &&*/ !strcmp(tree->child[1]->child[1]->attr.name, "return")); okay
                        {
                           if(tree->child[1]->child[1]->child[0] != NULL && (!strcmp(tree->child[1]->child[1]->attr.name, "return")) && tree->child[1]->child[1]->subkind.stmt == ReturnK)
                           {
                              printf("ERROR(%d): Function '%s' at line %d is expecting no return value, but return has a value.\n", tree->child[1]->child[1]->lineno, tree->attr.name, tree->lineno);
                              numErrors++;
                           }
                        }
                        
                     }
                  }
                  
               }
               st.applyToAll(countSymbols);           ////////////////////////////////////////////// SOURCE OF EXTRA WARNINGS
               if(!returnFlag && tree->expType != Void)
               {
                  printf("WARNING(%d): Expecting to return type %s but function '%s' has no return statement.\n", tree->lineno, convertExpTypeEnum(tree->expType), tree->attr.name);
                  numWarnings++;
               }
               tree->memType = Global;
               tree->memSize = funcSize;
               st.leave();
               funcSize = -2;
               break;
            case ParamK:
               tmp = st.lookupNode(tree->attr.name);
               tree->isInit = true;
               if(tree->isArray)
               {
                  if(tmp != NULL)
                  {

                  }
                  else
                  {
                     st.insert(tree->attr.name, (TreeNode*) tree);
                  }
               }
               else
               {
                  st.insert(tree->attr.name, (TreeNode*) tree);
               }
               tree->memType = Parameter;
               tree->offset = Loffset;
               Loffset = Loffset - tree->memSize;
               funcSize--;
               break;
            default:
               printf("Unknown DecK Line %d\n", tree->lineno);
               break;
         }
      }
      tree = tree->sibling;
   }
}

void unaryError(TreeNode *tree, char* expect)
{
   TreeNode *left = tree->child[0];
   TreeNode *right = tree->child[1];

   //printf("HERE LINE: %i\n", tree->lineno);
   if(!strcmp(tree->attr.name, "-"))
   {
      //printf("HERE\n");
      printf("ERROR(%d): Unary 'chsign' requires an operand of type %s but was given type ", tree->lineno, expect);
      numErrors++;
   }
   else
   {
      // printf("here in unary error LINE %i tree->attr.name = %s\n", tree->lineno, tree->attr.name);
      printf("ERROR(%d): Unary '%s' requires an operand of type %s but was given type ", tree->lineno, tree->attr.name, expect);
      numErrors++;
   }
   expTypePrint(tree->child[0]->expType);
   printf(".\n");
   tree->isErr = true;
   //numErrors++;
}

void notArrays(TreeNode * tree)
{
   TreeNode *tmp;
   tmp = tree->child[0];
   if(tmp != NULL)
   {
      if(tmp->subkind.exp == IdK)
      {
         tmp = st.lookupNode(tmp->attr.name);

         if(tmp != NULL && tmp->isArray)
         {
            if(!strcmp(tree->attr.name, "-"))
            {
               printf("ERROR(%d): The operation 'chsign' does not work with arrays.\n", tree->lineno);
               numErrors++;
            }
            else
            {
               printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->lineno, tree->attr.name);
               numErrors++;
            }
            tree->isErr = true;
         }
         else
         {
            tmp = tree->child[1];
            if(tmp != NULL && tmp->subkind.exp == IdK)
            {
               tmp = st.lookupNode(tmp->attr.name);
               if(tmp != NULL && tmp->isArray)
               {
                  printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->lineno, tree->attr.name);
                  numErrors++;
                  tree->isErr = true;
               }
            }
         }
      }

   }
   else if(tree->child[1] != NULL)
   {
      tmp = tree->child[1];
      printf("CHECK right child %d\n", tree->lineno);
      if(tmp->subkind.exp == IdK)
      {
         tmp = st.lookupNode(tmp->attr.name);
         if(tmp != NULL && tmp->isArray && !tmp->isErr)
         {
            printf("ERROR(%d): The operation %s does not work with arrays.\n", tree->lineno, tree->attr.name);
            numErrors++;
            tree->isErr = true;
         }
      }
   }
}

void checkInit(TreeNode *tree, int side)
{
   TreeNode *tmp;
   if(tree != NULL && tree->nodekind == ExpK && !tree->isErr && !inCall)
   {
      if(tree->subkind.exp == IdK && !tree->isStatic)
      {
         tmp = st.lookupNode(tree->attr.name);
         if(!tree->isInit && !tree->isArray) ////////////////// DOESNT DO ANYTHING
         {
            //printf("HERE\n");
            //printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
            //numWarnings++;
            tree->isInit = true;
            tmp->isInit = true;
            err = true;
         }
         if(!tree->isInit && tree->isArray)  /////////////////// DOESNT DO ANYTHING
         {
            tmp = st.lookupNode(tree->attr.name);
            //printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", tree->lineno, tree->attr.name);
            //numWarnings++;
            tree->isInit = true;
            tmp->isInit = true;
            err = true;
         }
      }
      if(tree->subkind.exp == OpK)
      {
         //printf("HERE\n");
         if(tree->attr.name == "[" && tree->child[0]->subkind.exp == IdK)
         {
            tmp = st.lookupNode(tree->child[0]->attr.name);
         }
         if(side == 0 && tmp != NULL)
         {
            tree->child[0]->isInit = tmp->isInit;
         }
         if(side == 1 && tree->attr.name == "[" && tmp != NULL && !tmp->isInit)  //////////////////// DOESNT DO ANYTHING
         {
            //printf("WARNING(%d): Variable '%s' may be uninitialized when used here.\n", tree->lineno, tree->child[0]->attr.name);
            //numWarnings++;
            tree->isInit = true;
            tree->child[0]->isInit = true;
            tmp->isInit = true;
            err = true;
         }
         checkArrays(tree);
      }
   }
}

void wasUsed(std::string sym, void *ptr)
{

}

void checkArrays(TreeNode *tree)
{
   TreeNode *left = NULL;
   TreeNode *right = NULL;

   left = tree->child[0];
   right = tree->child[1];

   if(tree->child[0]->subkind.exp == IdK)
   {
      left = st.lookupNode(tree->child[0]->attr.name);
      if(left != NULL)
      {
         tree->child[0]->expType = left->expType;
         tree->expType = left->expType;
      }

      if(left == NULL || !left->isArray)
      {
         printf("ERROR(%d): Cannot index nonarray '%s'.\n", tree->lineno, tree->child[0]->attr.name);
         numErrors++;
         err = true;
         tree->isErr = true;
      }
   }
   else
   {
      printf("ERROR(%d): Cannot index nonarray.\n", tree->lineno);
      numErrors++;
      err = true;
      tree->isErr = true;
   }
   if(tree->child[1] != NULL)
   {
      if(tree->child[1]->expType != Integer && tree->child[1]->expType != UndefinedType /*&& tree->child[0]->subkind.exp == IdK && !tree->child[1]->isErr*/)
      {
         printf("ERROR(%d): Array '%s' should be indexed by type int but got type ", tree->lineno, tree->child[0]->attr.name);
         expTypePrint(tree->child[1]->expType);
         printf(".\n");
         tree->isErr = true;
         numErrors++;
      }
   }
   if(tree->child[1] != NULL && tree->child[1]->subkind.exp == IdK)
   {
      //printf("here before seg\n");
     //printf("right->isArray: %i LINE %i\n", right->isArray, tree->lineno);
      if(right != NULL && right->isArray == true)
      {
         printf("ERROR(%d): Array index is the unindexed array '%s'.\n", tree->lineno, right->attr.name); //
         tree->isErr = true;
         numErrors++;
      }
      if(right != NULL)
      {
         //tree->expType = right->expType;
         tree->child[1]->expType = right->expType;
      }
   }
   //tree->isArray = true;
}

void checkUnaryOps(TreeNode *tree)
{
   TreeNode *left, *right, *tmp;
   if(tree->child[0] != NULL)
      left = tree->child[0];
   if(tree->child[1] != NULL)
      right = tree->child[1];

   if(!strcmp(tree->attr.name, "-"))
   {
      tree->isConstant = true;
      if(left->subkind.exp == ConstantK)
      {
         
         //printf("tree->child[0]->subkind.exp %i LINE %i\n", tree->child[0]->subkind.exp, tree->lineno);
         if(left->child[0] != NULL && left->child[0]->subkind.exp != ConstantK)
            unaryError(tree, (char*) "int");
         else if(left->expType != Integer)
            unaryError(tree, (char*) "int");
      }
      if(left->subkind.exp == IdK)
      {
         tmp = st.lookupNode(left->attr.name);
         if(tmp != NULL && tmp->expType != Integer)
         {
            unaryError(tree, (char *) "int");
         }
      }
      notArrays(tree);
   }
   else if(!strcmp(tree->attr.name, "?"))
   {
      if(left->subkind.exp == IdK)
      {
         tmp = st.lookupNode(left->attr.name);
         if(tmp != NULL && tmp->expType != Integer)
         {
            unaryError(tree, (char *) "int");
         }
      }
      else if(left->subkind.exp != IdK)
      {
         if(left->expType != Integer)
         {
            unaryError(tree, (char *) "int");
         }
      }
      notArrays(tree);
   }
   else if(!strcmp(tree->attr.name, "*"))
   {
      tree->expType = Integer;
      tree->isConstant = true;
      if(left->isArray != true)
      {
         if(left->expType != UndefinedType)
         {
            printf("ERROR(%d): The operation 'sizeof' only works with arrays.\n", tree->lineno);
            numErrors++;
         }
      }
   }
   else if(!strcmp(tree->attr.name, "not"))
   {
      tree->isConstant = true;
      if(left->subkind.exp == ConstantK && tree->expType != left->expType)
      {
         if(left->child[0] != NULL && left->child[0]->subkind.exp != ConstantK)
            unaryError(tree, (char*) "bool");
         else if(left->expType != Boolean)
            unaryError(tree, (char*) "bool");
      }
      if(left->subkind.exp == IdK)
      {
         tmp = st.lookupNode(left->attr.name);
         if(tmp != NULL && tmp->expType != Boolean)
         {
            unaryError(tree, (char*) "bool");
         }
      }
      if(left->child[0] != NULL)
      {
         if(left->child[0]->expType != Boolean && left->child[0]->subkind.exp != OpK && tree->expType != left->expType)
         {
            unaryError(tree, (char*) "bool");
         }
      }
      notArrays(tree);
   }
   else
   {
      notArrays(tree);
   }
}

void checkBinaryOps(TreeNode *tree)
{
   TreeNode *left, *right, *tmp;
   if(tree->child[0] != NULL)
      left = tree->child[0];
   if(tree->child[1] != NULL)
      right = tree->child[1];

   if(tree->child[0]->isConstant && tree->child[1]->isConstant)
   {
      tree->isConstant = true;
   }

   if(!strcmp(tree->attr.name, "or") || !strcmp(tree->attr.name, "and"))
   {
      //printf("left->expType: %s right->expType: %s LINE: %i\n", convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType), tree->lineno);
      if(left->subkind.exp == IdK)
      {
         if(left->expType != Boolean && left->expType != UndefinedType && left->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType));
            numErrors++;
         }
         if(right->expType != Boolean && right->expType != UndefinedType && right->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(right->expType));
            numErrors++;
         }
         if(left->isArray == true || right->isArray == true)
         {
            printf("ERROR(%d): The operation '%s' does not work with arrays.\n", tree->lineno, tree->attr.name);
            numErrors++;
         }
      }
      else // for CallK
      {
         if(left->expType != Boolean && left->expType != UndefinedType  && left->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type bool but lhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType));
            numErrors++;
         }
         if(right->expType != Boolean && right->expType != UndefinedType && right->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type bool but rhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(right->expType));
            numErrors++;
         }
      }
   }
   else if(!strcmp(tree->attr.name, "<") || !strcmp(tree->attr.name, ">") || !strcmp(tree->attr.name, "=") || !strcmp(tree->attr.name, ">=") || !strcmp(tree->attr.name, "<=") || !strcmp(tree->attr.name, "><"))
   {
      //printf("HERE LINE %i\n", tree->lineno);
      if(tree->isErr == false)
      {
         if(left->expType != right->expType && (left->expType != UndefinedType && right->expType != UndefinedType) && (left->expType != Void && right->expType != Void))
         {
            printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
            numErrors++;
         }
         if(left->isArray == true && right->isArray != true)
         {
            printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
            numErrors++;
         }
         if(left->isArray != true && right->isArray == true)
         {
            printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
            numErrors++;
         }    
      }
      //notArrays(tree);
   }
   else if(!strcmp(tree->attr.name, "+") || !strcmp(tree->attr.name, "-") || !strcmp(tree->attr.name, "*") || !strcmp(tree->attr.name, "/") || !strcmp(tree->attr.name, "%"))
   {
      if(tree->isArray == false)
      {
         //printf("HERE LINE %i\n", tree->lineno);
         if(left->expType != Integer && left->expType != UndefinedType && left->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType));
            numErrors++;
         }
         if(right->expType != Integer && right->expType != UndefinedType && right->expType != Void)
         {
            printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(right->expType));
            numErrors++;
         }
      }

      if(left->subkind.exp == CallK && right->subkind.exp == CallK)
      {
         if(left->expType != Integer && left->expType != UndefinedType)
         {
            printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType));
            numErrors++;
         }
         if(right->expType != Integer && right->expType != UndefinedType)
         {
            printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(right->expType));
            numErrors++;
         }
      }

      notArrays(tree);
   }
   else if(!strcmp(tree->attr.name, "["))
   {
      tree->expType = left->expType;
      checkArrays(tree);
   }
}

void checkUnaryAsgns(TreeNode *tree)
{
   TreeNode *left, *right, *tmp;
   if(tree->child[0] != NULL)
      left = tree->child[0];
   if(tree->child[1] != NULL)
      right = tree->child[1];

   if(!strcmp(tree->attr.name, "-"))
   {
      notArrays(tree);
      if(left->expType != Integer && left->expType != UndefinedType)
      {
         unaryError(tree, (char *) "int");
      }
   }
   else if(!strcmp(tree->attr.name, "*"))
   {
      if(left->isArray != true)
      {
         checkUnaryOps(tree);
      }
   }
   else if(!strcmp(tree->attr.name, "?"))
   {
      notArrays(tree);
      if(left->expType != Integer && left->expType != UndefinedType)
      {
         unaryError(tree, (char *) "int");
      }
   }
   else if(!strcmp(tree->attr.name, "not"))
   {
      notArrays(tree);
      if(left->expType != Boolean && left->expType != UndefinedType)
      {
         unaryError(tree, (char *) "bool");
      }
   }
   else if(!strcmp(tree->attr.name, "++") || !strcmp(tree->attr.name, "--"))
   {
      notArrays(tree);
      if(left->expType != Integer && left->expType != UndefinedType)
      {
         unaryError(tree, (char *) "int");
      }
   }
}

void checkBinaryAsgns(TreeNode *tree)
{
   TreeNode *left, *right, *tmp;
   if(tree->child[0] != NULL)
      left = tree->child[0];
   if(tree->child[1] != NULL)
      right = tree->child[1];
   
   if(!strcmp(tree->attr.name, "+=") || !strcmp(tree->attr.name, "-=") || !strcmp(tree->attr.name, "*=") || !strcmp(tree->attr.name, "/="))
   {
      if(left->expType != Integer && left->expType != UndefinedType)
      {
         printf("ERROR(%d): '%s' requires operands of type int but lhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType));
         numErrors++;
      }
      if(right->expType != Integer && right->expType != UndefinedType)
      {
         printf("ERROR(%d): '%s' requires operands of type int but rhs is of type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(right->expType));
         numErrors++;
      }
   }
   else if(!strcmp(tree->attr.name, ":="))
   {
      if(tree->subkind.decl == ParamK)
      {
         if(left->expType != right->expType && (left->expType != UndefinedType && right->expType != UndefinedType))
         {
            printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
            numErrors++;
         }
      }
      if(left->subkind.exp == IdK)
      {
         tree->expType = left->expType;
         if(left->expType != right->expType && (left->expType != UndefinedType && right->expType != UndefinedType && right->child[0] != NULL && right->child[0]->subkind.exp != CallK) /*&& tree->subkind.decl != ParamK*/) /////////// extras are coming from here
         {
            printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
            numErrors++;
         }
         else if(left->expType != right->expType && (left->expType != UndefinedType && right->expType != UndefinedType && right->child[0] != NULL))
         {
            printf("right->attr.name %s LINE %i\n", right->attr.name, tree->lineno);
            if(!strcmp(right->attr.name, "input"))
            {
               ;
            }
            if(right->child[0]->subkind.exp != CallK)
            {
               printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
               numErrors++;
            }
         }
         else if(left->expType != right->expType && (left->expType != UndefinedType && right->expType != UndefinedType && right->child[0] == NULL))
         {
            if(right->subkind.exp == CallK)
            {
               if(!strcmp(right->attr.name, "input") || !strcmp(right->attr.name, "inputb") || !strcmp(right->attr.name, "inputc"))
               {
                  ;
               }
               else if(right->expType == Integer)
               {
                  printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
                  numErrors++;
               }
               else
               {
                  printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
                  numErrors++;
               }
            }
            else
            {
               printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
               numErrors++;
            }
            
         }
         tmp = st.lookupNode(left->attr.name);
         if(tmp != NULL)
            tmp->isInit = true;
         
         left->isInit = true;
         tree->expType = left->expType;
         tree->isArray = left->isArray;
      }
      if(left->isArray == true && right->isArray != true)
      {
         printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is an array and rhs is not an array.\n", tree->lineno, tree->attr.name);
         numErrors++;
      }
      if(left->isArray != true && right->isArray == true)
      {
         printf("ERROR(%d): '%s' requires both operands be arrays or not but lhs is not an array and rhs is an array.\n", tree->lineno, tree->attr.name);
         numErrors++;
      }
      if(left->subkind.exp != IdK && (left->expType != right->expType) && (left->expType != UndefinedType && right->expType != UndefinedType))
      {
         printf("ERROR(%d): '%s' requires operands of the same type but lhs is type %s and rhs is type %s.\n", tree->lineno, tree->attr.name, convertExpTypeEnum(left->expType), convertExpTypeEnum(right->expType));
         numErrors++;
      }
   }
   else
   {
      printf("NOT IN BINARY ASGNS\n");
   }
}

const char* convertExpTypeEnum(ExpType value)
{
   switch(value)
   {
      case 0:
         return("void");
         break;
      case 1:
         return("int");
         break;
      case 2:
         return("bool");
         break;
      case 3:
         return("char");
         break;
      case 4:
         return("char");
         break;
      case 5:
         return("equal");
         break;
      case 6:
         return("undefined type");
         break;
      default:
         break;
   }
}
