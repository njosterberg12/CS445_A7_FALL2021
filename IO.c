#include "IO.h"
#include <string.h>
#include "symbolTable.h"
#include "treeNodes.h"
#include "scanType.h"
#include "semantic.h"

extern SymbolTable st;

void prototype()
{
   TreeNode *tmp, *holder;
   //TokenData *token;
   tmp = newDeclNode2(FuncK);
   //token->tokenstr = strdup("output");
   //tmp = newDeclNode(FuncK, token); ////////////////////////////////// NOT WORKING HERE.
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("output");
   //tmp->expType = Integer;
   tmp->expType = Void;
   st.insert(tmp->attr.name, (TreeNode *) tmp);
   holder = newDeclNode2(ParamK);
   holder->attr.name = strdup("dummy");
   holder->expType = Integer;
   tmp->child[0] = holder;

   //token->tokenstr = strdup("outputb");
   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("outputb");
   //tmp->expType = Boolean;
   tmp->expType = Void;
   st.insert(tmp->attr.name, (TreeNode *) tmp);
   holder = newDeclNode2(ParamK);
   holder->attr.name = strdup("dummy");
   holder->expType = Boolean;
   tmp->child[0] = holder;

   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("outputc");
   //tmp->expType = Char;
   tmp->expType = Void;
   st.insert(tmp->attr.name, (TreeNode *) tmp);
   holder = newDeclNode2(ParamK);
   holder->attr.name = strdup("dummy");
   holder->expType = Char;
   tmp->child[0] = holder;

   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("input");
   tmp->expType = Integer;
   st.insert(tmp->attr.name, (TreeNode *) tmp);

   //printf("tmp: line: %i isUsed: %i IOcontrol: %i attr.nam: %s expType: %s\n", tmp->lineno, tmp->isUsed, tmp->isIOControl, tmp->attr.name, convertExpTypeEnum(tmp->expType));

   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("inputb");
   tmp->expType = Boolean;
   st.insert(tmp->attr.name, (TreeNode *) tmp);

   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->attr.name = strdup("inputc");
   tmp->expType = Char;
   st.insert(tmp->attr.name, (TreeNode *) tmp);

   tmp = newDeclNode2(FuncK);
   tmp->lineno = -1;
   tmp->isUsed = true;
   tmp->isIOControl = true;
   tmp->expType = Void;
   tmp->attr.name = strdup("outnl");
   st.insert(tmp->attr.name, (TreeNode *) tmp);
}