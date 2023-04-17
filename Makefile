OBJS = main.cpp Parser.h Parser.cpp Code.h Code.cpp SymbolTable.h SymbolTable.cpp Assembler.h Assembler.cpp

CC = g++ -g

COMPILER_FLAGS = -w

OBJ_NAME = Assembler

all : $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) -o $(OBJ_NAME)