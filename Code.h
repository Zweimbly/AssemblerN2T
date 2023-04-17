#pragma once
#include <vector>
#include <string>
#include <algorithm>

class Code
{
public:
    uint8_t Dest(std::string destMnemonic);
    uint8_t Comp(std::string compMnemonic);
    uint8_t Jump(std::string jumpMnemonic);
    uint16_t StringToBinary(std::string num);
    std::string BinaryReptoString(uint16_t binaryCommand);

    uint16_t WriteAInst(uint16_t symbol);
    uint16_t WriteCInst(uint8_t dest, uint8_t comp, uint8_t jump);
};