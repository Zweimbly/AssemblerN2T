#include "Parser.h"

//Open and store each line from filename.asm into a vector of strings
Parser::Parser(std::string& filename)
{
    curLine = 0;

    asmFile.open(filename);
    std::string temp;
    
    while (getline(asmFile, temp))
    {
        //Find and erase anything after // in lines
        int commentPos = temp.find("//");
        if (commentPos != std::string::npos)
        {
            temp.erase(commentPos);
        }
        
        if (!temp.empty())
        {
            int spaces = temp.find(" ");
            if (spaces != std::string::npos)
            {
                //Remove all spaces using erase-remove_if
                temp.erase(std::remove_if(temp.begin(), temp.end(), [](char &a){ return (a == ' '); }), temp.end());
            }

            int carReturn = temp.find("\r");
            if (carReturn != std::string::npos)
            {
                //Remove carriage returns ('\r' characters)
                temp.erase(carReturn);
            }

            if (!temp.empty())
            {
                linesVec.push_back(temp);
            }
            
        }

        temp = "";
    }

    for (auto a : linesVec)
    {
        std::cout << a << '\n';
    }
}

//Check if curLine has reached the end of the list of lines
bool Parser::HasMoreCommands()
{
    if (curLine < linesVec.size())
    {
        return true;
    }
    
    return false;
}

//Advance to next line/command
void Parser::Advance()
{
    curLine++;
}

//Return 0 for A_COMMAND, 1 for C_COMMAND, 2 for L_COMMAND
int Parser::CommandType()
{
    //If the line is @Xxx, it is an A_COMMAND
    if (linesVec[curLine][0] == '@')
    {
        return A_COMMAND;
    }
    //If first char is '(' as in (Xxx), it is an L_COMMAND
    else if (linesVec[curLine][0] == '(')
    {
        return L_COMMAND;
    }
    //If neither of the above, it is a C_COMMAND
    else
    {
        return C_COMMAND;
    }
}

//Return string of A_COMMAND or L_COMMAND symbol (the "Xxx" in "@Xxx" or (Xxx))
std::string Parser::Symbol()
{
    //Sanity checks
    if (linesVec[curLine][0] == '@')
    {
        return linesVec[curLine].substr(1, linesVec[curLine].size() - 1);
    }
    else if (linesVec[curLine][0] == '(')
    {
        return linesVec[curLine].substr(1, linesVec[curLine].size() - 2);
    }
    else
    {
        return "";
    }
}

//These methods return part of a C_COMMAND as a string (dest=comp;jump)
std::string Parser::Dest()
{
    int eqPos = linesVec[curLine].find('=');

    if (eqPos != std::string::npos)
    {
        return linesVec[curLine].substr(0, eqPos);
    }
    else
    {
        return "";
    }
}

std::string Parser::Comp()
{
    int eqPos = linesVec[curLine].find('=');
    int semicolonPos = linesVec[curLine].find(';');
    
    if (eqPos != std::string::npos)
    {
        if (semicolonPos != std::string::npos)
        {
            return linesVec[curLine].substr(eqPos + 1, semicolonPos);
        }
        else
        {
            return linesVec[curLine].substr(eqPos + 1, linesVec[curLine].size() - 1);
        }
    }
    else
    {
        if (semicolonPos != std::string::npos)
        {
            return linesVec[curLine].substr(0, semicolonPos);
        }
        else
        {
            return linesVec[curLine];
        }
    }
}

//Returns empty string if no jump is included in the C_COMMAND
std::string Parser::Jump()
{
    int semicolonPos = linesVec[curLine].find(';');

    if (semicolonPos != std::string::npos)
    {
        return linesVec[curLine].substr(semicolonPos + 1, linesVec[curLine].size() - 1);
    }
    else
    {
        return "";
    }
}