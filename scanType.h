#ifndef SCANTYPE_H
#define SCANTYPE_H

#include <string.h>
//#include "treeNodes.h"

struct TokenData{
   int tokenclass; // token class
   int linenum; // what line did this token occur on?
   char *tokenstr;
   char cvalue; // any character value
   char *idvalue; // index for id
   int nvalue; // value of the number as an int
   //char *svalue; // any string value e.g. an id
   int stringLength;
   char svalue[];
};

#endif