/**
 * Studying C++
 * Check flags set in a given mask
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <cstdlib>

unsigned int flags[32] =
{
    0x00000001, 0x00000002, 0x00000004, 0x00000008,
    0x00000010, 0x00000020, 0x00000040, 0x00000080,
    0x00000100, 0x00000200, 0x00000400, 0x00000800,
    0x00001000, 0x00002000, 0x00004000, 0x00008000,
    0x00010000, 0x00020000, 0x00040000, 0x00080000,
    0x00100000, 0x00200000, 0x00400000, 0x00800000,
    0x01000000, 0x02000000, 0x04000000, 0x08000000,
    0x10000000, 0x20000000, 0x40000000, 0x80000000
};

int main(int argc, char* argv[])
{
    if (argc < 2)
    {
        std::cout << "Argument missing.\n";
        return 1;
    }

    int mask = atoi(argv[1]);

    for (int i = 0; i < 32; ++i)
    {
        if (mask & flags[i])
            std::cout << std::hex << "0x" << flags[i] << " (" << std::dec << flags[i] << ")\n";
    }

    return 0;
}
