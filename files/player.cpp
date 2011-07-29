/**
 * Studying C++
 * Simple way to write and read objects from a file
 * 
 * Fredi Machado
 * http://github.com/fredi
 */

#include <string.h>
#include "player.h"

Player::Player(std::string name, int hp, int mana, int ap, int sp)
{
    SetName(name);
    SetHP(hp);
    SetMana(mana);
    SetAP(ap);
    SetSP(sp);
}

void Player::SetName(std::string name)
{
    const char* nameValue = name.data();
    int length = name.size();
    length = (length < 20 ? length : 19);
    strncpy(_name, nameValue, length);
    _name[length] = '\0';
}