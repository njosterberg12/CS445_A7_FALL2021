#include <string.h>
#include "semantic.h"

extern SymbolTable st;
extern int numErrors;

int countParameters(TreeNode *tree)
{
   int count = 0;

   TreeNode *tmp = NULL;
   tmp = tree->child[0];

   while(tmp != NULL)
   {
      count++;
      tmp = tmp->sibling;
   }

   tree->numParams = count;

   if(strcmp("main", tree->attr.name) == 0)
   {
      tree->numParams = 0;
   }
   return count;
}

void compareParams(TreeNode *tree)
{
   TreeNode *def = NULL, *params;

   int count = 0;
   int dec_line = 0;
   int dec_count;
   bool isIO = false;

   def = st.lookupNode(tree->attr.name);
   tree->expType = def->expType;
   int callParameterCount = countParameters(tree);
   int funcParameterCount = countParameters(def);

   if(def != NULL)
   {
      dec_line = def->lineno;
      dec_count = def->numParams;
      isIO = def->isIOControl;
   }

   //printf("call param count: %i\n", callParameterCount);
   //printf("funcName: %s func param type: %s\n", tree->attr.name, convertExpTypeEnum(tree->expType));
   // count and check types
   params = tree->child[0];
   //printf("def->isArray %i def->attr.name %s def->expType %s LINE %i\n", def->isArray, def->attr.name, convertExpTypeEnum(def->expType), tree->lineno);
   TreeNode *def2 = def->child[0];


   while(params != NULL && def2 != NULL)
   {
      count++;
      //if(params != NULL && def2 != NULL)
      //printf("params->attr.name %s params->expType %s params->isArray %i def2->isArray %i def2->attr.name %s def2->expType %s LINE %i\n", params->attr.name, convertExpTypeEnum(params->expType), params->isArray, def->isArray, def->attr.name, convertExpTypeEnum(def->expType), tree->lineno);
      
      if(def2->isArray && !params->isArray)
      {
         printf("ERROR(%d): Expecting array in parameter %i of call to '%s' declared on line %d.\n", tree->lineno, count, tree->attr.name, dec_line);
         numErrors++;
      }
      if(!def2->isArray && (params->isArray /*&& params->child[0] == NULL*/))
      {
         printf("ERROR(%d): Not expecting array in parameter %i of call to '%s' declared on line %d.\n", tree->lineno, count, tree->attr.name, dec_line);
         numErrors++;
      }
      if(def2->expType != params->expType && (params->expType != UndefinedType) && !def2->isIOControl /*(params->expType != Void)*/) //&& (params->expType != Void))
      {
         printf("ERROR(%d): Expecting type %s in parameter %i of call to '%s' declared on line %d but got type %s.\n", tree->lineno, convertExpTypeEnum(def2->expType), count, tree->attr.name, dec_line, convertExpTypeEnum(params->expType));
         //expTypePrint(def2->expType);
         //printf(" in parameter %i of call to '%s' declared on line %d but got type ", count, tree->attr.name, dec_line);
         //expTypePrint(params->expType);
         //printf(".\n");
         numErrors++;
      }

      params = params->sibling;
      def2 = def2->sibling;
   }
   /*if(def->isIOControl && tree->child[0] != NULL) //&& tree->child[0]->expType != def->expType)
   {
      if(tree->child[0]->expType != def->expType)
      {
         printf("ERROR(%d): Expecting type %s in parameter 1 of call to '%s' declared on line -1 but got type %s.\n", tree->lineno, convertExpTypeEnum(tree->child[0]->expType), tree->attr.name, convertExpTypeEnum(def->expType));
         numErrors++;
      }
      
   }*/

   if(params != NULL)
      count++;
   
   if(count > dec_count && !isIO)
   {
      printf("ERROR(%d): Too many parameters passed for function '%s' declared on line %d.\n", tree->lineno, tree->attr.name, dec_line);
      numErrors++;
   }

   if(count < dec_count && !isIO)
   {
      printf("ERROR(%d): Too few parameters passed for function '%s' declared on line %d.\n", tree->lineno, tree->attr.name, dec_line);
      numErrors++;
   }
}