/**
 * C++ Playground
 * Very simple example of inline assembly usage
 */

#include <iostream>

int number;

int main()
{
    number = 50;
    std::cout << "number is " << number << std::endl;

    asm(".intel_syntax noprefix\n"
        "mov eax, _number\n"
        "mov ecx, 5\n"
        "mul ecx\n"
        "mov _number, eax\n"
        ".att_syntax noprefix\n");

    std::cout << "number is now " << number << std::endl;
    return 0;
}
