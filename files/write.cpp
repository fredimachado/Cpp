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

    std::string name;
    int level, hp, mana, ap, sp;

    std::cout << "Enter name: ";
    std::getline(std::cin, name);

    std::cout << "Enter level: ";
    std::cin >> level;

    std::cout << "Enter HP: ";
    std::cin >> hp;

    std::cout << "Enter Mana: ";
    std::cin >> mana;

    std::cout << "Enter Attack Power: ";
    std::cin >> ap;

    std::cout << "Enter Spell Power: ";
    std::cin >> sp;

    Player player(name, level, hp, mana, ap, sp);

    outPlayer.write(reinterpret_cast<const char*>(&player), sizeof(Player));

    return 0;
}
