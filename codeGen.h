#ifndef CODEGEN
#define CODEGEN

#include "emitcode.h"
#include "treeNodes.h"
#include "scanType.h"
#include "symbolTable.h"

extern int emitLoc;

void codeGen(TreeNode* t, char* outFile);
void codeGenIO();
void codeGenMain(TreeNode* t);
void treeTargetCode(TreeNode* tree);
void unaryOpCode(TreeNode* tree);
void binaryOpCode(TreeNode* tree);
void unaryAsgnCode(TreeNode* tree);
void binaryAsgnCode(TreeNode* tree);
int frame(treeNode* tree);

#endif