/**
 * Studying C++
 * Simple Turn Based Battle Game
 * 
 * Based on TrinityCore's code
 * https://github.com/TrinityCore/TrinityCore
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include "player.h"

Player::Player() : Unit()
{
    m_objectTypeId = TYPEID_PLAYER;
}

void Player::CalculateMinMaxDamage(float& min_damage, float& max_damage)
{
    float base_value  = 1.0f;

    float weapon_mindamage = m_mindamage;
    float weapon_maxdamage = m_maxdamage;

    min_damage = base_value + weapon_mindamage;
    max_damage = base_value + weapon_maxdamage;
}
