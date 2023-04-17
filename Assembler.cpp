#include "Assembler.h"

Assembler::Assembler(std::string filename)
    :
    parser(filename),
    code(),
    symbolTable()
{
    std::string outfilename = filename.substr(0, filename.size() - 3);
    outfilename = outfilename.append("hack");

    hackFile.open(outfilename, std::ofstream::binary);
}

void Assembler::Run()
{
    uint16_t output;
    int curCommandType;
    int lineCounter = 0;    //For ROM address for L_COMMANDs
    int RAMaddress = 16;
    std::string sym;
    std::string ASCIICommand;
    
    //First pass - dealing with labels from L_COMMANDs
    while (parser.HasMoreCommands())
    {
        curCommandType = parser.CommandType();

        if (curCommandType == Parser::L_COMMAND)
        {
            symbolTable.AddEntry(parser.Symbol(), lineCounter);
        }
        else if ((curCommandType == Parser::A_COMMAND) || (curCommandType == Parser::C_COMMAND))
        {
            lineCounter++;
        }

        parser.Advance();
    }

    //Reset parser position to the beginning of the vector of commands
    parser.curLine = 0;
    
    //Second pass - handling everything else and writing to .hack file
    while (parser.HasMoreCommands())
    {
        curCommandType = parser.CommandType();

        if (curCommandType == Parser::A_COMMAND)
        {
            sym = parser.Symbol();
            auto iter = std::find_if(sym.begin(), sym.end(), [](char &a){ return (((int)a < 48) || ((int)a > 57)); });

            //If there is a non-numeric char, handle the symbol
            if (iter != sym.end())
            {
                if (symbolTable.Contains(sym))
                {
                    output = code.WriteAInst(symbolTable.GetAddress(sym));
                }
                else
                {
                    symbolTable.AddEntry(sym, RAMaddress);
                    RAMaddress++;

                    output = code.WriteAInst(symbolTable.GetAddress(sym));
                }
            }
            //Else get the binary representation of the number
            else
            {
                output = code.WriteAInst(code.StringToBinary(parser.Symbol()));
            }
            
        }
        else if (curCommandType == Parser::C_COMMAND)
        {
            output = code.WriteCInst(code.Dest(parser.Dest()), code.Comp(parser.Comp()), code.Jump(parser.Jump()));
        }

        if (curCommandType != Parser::L_COMMAND)
        {
            ASCIICommand = code.BinaryReptoString(output);
            hackFile << ASCIICommand << '\n';

            std::cout << ASCIICommand << '\n';
        }


        //For old binary-only version
        /*
        std::cout << std::hex << output << '\n';
        hackFile.write((char*)&output, sizeof(output));
        //hackFile << '\n';
        */

        output = 0;
        parser.Advance();
    }
    
}