#ifndef CODEGEN
#define CODEGEN

#include "emitcode.h"
#include "treeNodes.h"
#include "scanType.h"
#include "symbolTable.h"

extern int emitLoc;

void IOSetup(TreeNode* tree);
void treeTargetCode(TreeNode* tree);
void init();
void unaryOpCode(TreeNode* tree);
void binaryOpCode(TreeNode* tree);
void unaryAsgnCode(TreeNode* tree);
void binaryAsgnCode(TreeNode* tree);
int frame(treeNode* tree);

#endif