#include "Assembler.h"

int main(int argc, char *argv[])
{
    std::string filename = argv[1];
    filename = "./" + filename;

    Assembler assembler(filename);

    assembler.Run();

    return 0;
}