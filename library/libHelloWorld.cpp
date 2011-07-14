/**
 * Studying C++
 * Creating a library
 *
 * Compilation: g++ libHelloWorld.cpp -c
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include "libHelloWorld.h"

void printHelloWorld()
{
    printf("Hello World!\n");
}

void printWord(std::string st)
{
    printf("Word is: %s\n", st.c_str());
}
