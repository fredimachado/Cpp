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

#ifndef _OBJECT_H
#define _OBJECT_H

#include "common.h"

enum TypeID
{
    TYPEID_OBJECT        = 0,
    TYPEID_ITEM          = 1,
    TYPEID_UNIT          = 2,
    TYPEID_PLAYER        = 3
};

class Player;
class Unit;

class Object
{
    public:
        TypeID GetTypeId() const { return m_objectTypeId; }

        Player* ToPlayer() { if (GetTypeId() == TYPEID_PLAYER) return reinterpret_cast<Player*>(this); else return NULL; }
        const Player* ToPlayer() const { if (GetTypeId() == TYPEID_PLAYER) return (const Player*)((Player*)this); else return NULL; }

    protected:
        Object();

        TypeID m_objectTypeId;
};

#endif
