#pragma once
#include <string>
#include <vector>
#include <unordered_map>

class SymbolTable
{
public:
    SymbolTable();
    void AddEntry(std::string symbol, int address);
    bool Contains(std::string symbol);
    int GetAddress(std::string symbol);

private:
    std::unordered_map<std::string, int> table;
};