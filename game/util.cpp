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

#include "util.h"

static URandom* mURand = new URandom;

uint32 urand(uint32 min, uint32 max)
{
    return mURand->get(min, max);
}
