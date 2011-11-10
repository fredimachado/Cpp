/**
 * Studying C++
 * Check flags set in a given mask
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <cstdlib>

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Argument missing.\n";
        return 1;
    }

    int mask = atoi(argv[1]);

    for (int i = 0; i < 31; ++i)
    {
        int flag = 1 << i;
        if (mask & flag)
            std::cout << std::hex << "0x" << flag << " (" << std::dec << flag << ")\n";
    }

    return 0;
}
