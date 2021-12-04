BIN = parser
CC = g++
EXE = c-

FILS = treeNodes.c symbolTable.cpp semantic.cpp IO.c errors.c yyerror.cpp emitcode.cpp codeGen.c
SRCS = $(BIN).y  $(BIN).l
HDRS = scanType.h treeNodes.h symbolTable.h semantic.h IO.h yyerror.h emitcode.h codeGen.h
OBJS = lex.yy.o $(BIN).tab.o

$(BIN) : $(OBJS)
	$(CC) $(OBJS) $(FILS) -o $(EXE)

lex.yy.c : $(BIN).l $(BIN).tab.h $(HDRS)
	flex $(BIN).l

lex.yy.o : lex.yy.c
	$(CC) -c -g lex.yy.c -o lex.yy.o

$(BIN).tab.h $(BIN).tab.c : $(BIN).y
	bison -v -t -d $(BIN).y

$(BIN).tab.o : $(BIN).tab.c
	$(CC) -c -g $(BIN).tab.c -o $(BIN).tab.o

clean :
	rm -f *~ $(OBJS) $(EXE) lex.yy.c $(BIN).tab.h $(BIN).tab.c $(BIN).output

tar : $(HDRS) $(SRCS) $(GCC) makefile
	tar -cvf $(BIN).tar $(HDRS) $(SRCS) $(FILS) makefile tm.c
