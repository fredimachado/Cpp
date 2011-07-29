/**
 * Studying C++
 * Simple way to read objects from a file
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
    std::fstream inPlayer("player.dat", std::ios::in);

    if (!inPlayer)
    {
        std::cout << "The file could not be opened." << std::endl;
        exit(1);
    }

    Player player;
    inPlayer.read(reinterpret_cast<char*>(&player), sizeof(Player));

    if (player.GetName() != "")
    {
        std::cout << "Name: " << player.GetName() << std::endl
            << "HP: " << player.GetHP() << std::endl
            << "Mana: " << player.GetMana() << std::endl
            << "AP: " << player.GetAP() << std::endl
            << "SP: " << player.GetSP() << std::endl;
    }

    return 0;
}
