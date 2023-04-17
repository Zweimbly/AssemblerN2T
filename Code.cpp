#include "Code.h"

uint8_t Code::Dest(std::string destMnemonic)
{
    if (destMnemonic.empty())
    {
        return 0;
    }
    
    bool containsM = (destMnemonic.find("M") != std::string::npos);
    bool containsD = (destMnemonic.find("D") != std::string::npos);
    bool containsA = (destMnemonic.find("A") != std::string::npos);
    
    uint8_t result = 0b00000000;

    uint8_t binHasM = 0b00000001 & containsM;
    uint8_t binHasD = 0b00000010 & (containsD << 1);
    uint8_t binHasA = 0b00000100 & (containsA << 2);
    result = binHasM | binHasD | binHasA;

    return result;
}

uint8_t Code::Comp(std::string compMnemonic)
{
    uint8_t result = 0;
    
    if (compMnemonic.empty())
    {
        result = 0b0000000;
    }
    else if (compMnemonic == "0")
    {
        result = 0b0101010;
    }
    else if (compMnemonic == "1")
    {
        result = 0b0111111;
    }
    else if (compMnemonic == "D")
    {
        result = 0b0001100;
    }
    else if (compMnemonic == "A")
    {
        result = 0b0110000;
    }
    else if (compMnemonic == "M")
    {
        result = 0b1110000;
    }
    else if (compMnemonic[0] == '-')
    {
        if (compMnemonic[1] == '1')
        {
            result = 0b0111010;
        }
        else if (compMnemonic[1] == 'D')
        {
            result = 0b0001111;
        }
        else if (compMnemonic[1] == 'A')
        {
            result = 0b0110011;
        }
        else if (compMnemonic[1] == 'M')
        {
            result = 0b1110011;
        }
    }
    else if (compMnemonic[0] == '!')
    {
        if (compMnemonic[1] == 'D')
        {
            result = 0b0001101;
        }
        else if (compMnemonic[1] == 'A')
        {
            result = 0b0110001;
        }
        else if (compMnemonic[1] == 'M')
        {
            result = 0b1110001;
        }
    }
    else if (compMnemonic == "D+1")
    {
        result = 0b0011111;
    }
    else if (compMnemonic == "A+1")
    {
        result = 0b0110111;
    }
    else if (compMnemonic == "M+1")
    {
        result = 0b1110111;
    }
    else if (compMnemonic == "D-1")
    {
        result = 0b0001110;
    }
    else if (compMnemonic == "A-1")
    {
        result = 0b0110010;
    }
    else if (compMnemonic == "M-1")
    {
        result = 0b1110010;
    }
    else if (compMnemonic == "D+A")
    {
        result = 0b0000010;
    }
    else if (compMnemonic == "D+M")
    {
        result = 0b1000010;
    }
    else if (compMnemonic == "D-A")
    {
        result = 0b0010011;
    }
    else if (compMnemonic == "D-M")
    {
        result = 0b1010011;
    }
    else if (compMnemonic == "A-D")
    {
        result = 0b0000111;
    }
    else if (compMnemonic == "M-D")
    {
        result = 0b1000111;
    }
    else if (compMnemonic == "D&A")
    {
        result = 0b0000000;
    }
    else if (compMnemonic == "D&M")
    {
        result = 0b1000000;
    }
    else if (compMnemonic == "D|A")
    {
        result = 0b0010101;
    }
    else if (compMnemonic == "D|M")
    {
        result = 0b1010101;
    }

    return result;
}

uint8_t Code::Jump(std::string jumpMnemonic)
{
    uint8_t result = 0;
    
    if (jumpMnemonic.empty())
    {
        result = 0b000;
    }
    else if (jumpMnemonic == "JGT")
    {
        result = 0b001;
    }
    else if (jumpMnemonic == "JEQ")
    {
        result = 0b010;
    }
    else if (jumpMnemonic == "JGE")
    {
        result = 0b011;
    }
    else if (jumpMnemonic == "JLT")
    {
        result = 0b100;
    }
    else if (jumpMnemonic == "JNE")
    {
        result = 0b101;
    }
    else if (jumpMnemonic == "JLE")
    {
        result = 0b110;
    }
    else if (jumpMnemonic == "JMP")
    {
        result = 0b111;
    }

    return result;
}

uint16_t Code::StringToBinary(std::string num)
{
    uint16_t result = 0;
    //auto isNonNumeric = [](char &a){ return (((int)a < 48) || ((int)a > 57)); };
    auto iter = std::find_if(num.begin(), num.end(), [](char &a){ return (((int)a < 48) || ((int)a > 57)); });

    //If there is a non-numeric char in the string, ignore for now
    if (iter != num.end())
    {
        result = 0;
    }
    else
    {
        int intNum = std::stoi(num);
        result = (uint16_t)intNum;
    }

    return result;
}

std::string Code::BinaryReptoString(uint16_t binaryCommand)
{
    std::string result = "";
    int temp = 0;
    
    //Each loop identifies whether a bit from the command is 0 or 1 and moves to the next bit
    for (int i = 0; i < 16; i++)
    {
        temp = (binaryCommand & 0x8000) >> 15;

        if (temp == 1)
        {
            result.push_back('1');
        }
        else
        {
            result.push_back('0');
        }

        binaryCommand <<= 1;
    }

    return result;
}

uint16_t Code::WriteAInst(uint16_t symbol)
{
    //For old binary-only version to fix endianness
    /*
    uint16_t symLeft8 = symbol & 0b1111111100000000;
    uint16_t symRight8 = symbol & 0b0000000011111111;
    uint16_t symbolShift1 = symRight8 << 8;
    uint16_t symbolShift2 = symLeft8 >> 8;
    uint16_t symbolShifted = symbolShift1 | symbolShift2;
    uint16_t result = symbolShifted & 0b0111111111111111;
    */

    uint16_t result = 0;
    result = symbol & 0b0111111111111111;

    return result;
}

uint16_t Code::WriteCInst(uint8_t dest, uint8_t comp, uint8_t jump)
{
    uint16_t result = 0;

    uint8_t destShifted = (0b111 & dest) << 3;
    uint16_t compShifted = (0b1111111 & comp) << 6;
    uint8_t jumpShifted = 0b111 & jump;

    uint16_t result1 = destShifted | compShifted | jumpShifted;
    //result1 = 0b1110000000000000 | result1;
    result = 0b1110000000000000 | result1;

    //For old binary-only version to fix endianness
    /*
    uint16_t rLeft8 = result1 & 0b1111111100000000;
    uint16_t rRight8 = result1 & 0b0000000011111111;
    uint16_t rShift1 = rRight8 << 8;
    uint16_t rShift2 = rLeft8 >> 8;
    result = rShift1 | rShift2;
    */

    return result;
}