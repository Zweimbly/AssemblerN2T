#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <algorithm>

#include <iostream>

class Parser
{
public:
    Parser(std::string& filename);
    bool HasMoreCommands();
    void Advance();
    int CommandType();
    std::string Symbol();
    std::string Dest();
    std::string Comp();
    std::string Jump();

    int curLine;

    enum Command
    {
        A_COMMAND,
        C_COMMAND,
        L_COMMAND
    };

private:
    std::ifstream asmFile;
    
    std::vector<std::string> linesVec;
};