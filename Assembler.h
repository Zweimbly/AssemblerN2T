#pragma once
#include "Parser.h"
#include "Code.h"
#include "SymbolTable.h"

class Assembler
{
public:
    Assembler(std::string filename);
    void Run();

    Parser parser;
    Code code;
    SymbolTable symbolTable;

    std::ofstream hackFile;
};