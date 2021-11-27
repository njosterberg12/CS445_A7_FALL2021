#ifndef SEMANTIC
#define SEMANTIC
#include "treeNodes.h"
#include "symbolTable.h"
#include "scanType.h"

void analyze(TreeNode *tree);
void unaryError(TreeNode *tree, char* expect);
void notArrays(TreeNode *tree);
void checkInit(TreeNode *tree, int side);
void alreadyDecld(TreeNode *tree, char *sym, int line);
void wasUsed(std::string sym, void *ptr);
void checkArrays(TreeNode *tree);
void onlyArrays(TreeNode *tree);
void typeInts(TreeNode *tree);
void checkUnaryOps(TreeNode *tree);
void checkBinaryOps(TreeNode *tree);
void checkUnaryAsgns(TreeNode *tree);
void checkBinaryAsgns(TreeNode *tree);
const char* convertExpTypeEnum(ExpType value);
void compareParams(TreeNode *tree);
int countParameters(TreeNode *tree);

#endif