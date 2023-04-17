#include "SymbolTable.h"

SymbolTable::SymbolTable()
{
    std::string label;
    
    table.emplace("SP", 0x0);
    table.emplace("LCL", 0x1);
    table.emplace("ARG", 0x2);
    table.emplace("THIS", 0x3);
    table.emplace("THAT", 0x4);
    table.emplace("SCREEN", 0x4000);
    table.emplace("KBD", 0x6000);

    for (int i = 0; i < 16; i++)
    {
        label = "R";
        label.append(std::to_string(i));
        table.emplace(label, i);
    }
}

void SymbolTable::AddEntry(std::string symbol, int address)
{
    table.emplace(symbol, address);
}

bool SymbolTable::Contains(std::string symbol)
{
    auto iter = table.find(symbol);

    if (iter != table.end())
    {
        return true;
    }
    else
    {
        return false;
    }
}

int SymbolTable::GetAddress(std::string symbol)
{
    int addressRef = table.at(symbol);

    return addressRef;
}