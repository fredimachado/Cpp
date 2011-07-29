/**
 * Studying C++
 * Simple way to write objects in a file
 * 
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "player.h"

int main()
{
    std::ofstream outPlayer("player.dat", std::ios::binary);

    if (!outPlayer)
    {
        std::cout << "The file could not be opened." << std::endl;
        exit(1);
    }

    Player player("Thunt", 20, 10, 1, 1);

    outPlayer.write(reinterpret_cast<const char*>(&player), sizeof(Player));

    return 0;
}
