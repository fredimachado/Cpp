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

#ifndef _UTIL_H
#define _UTIL_H

#include "common.h"

class URandom
{
    public:
        URandom() { init(); }

        static void init(uint32 s) { srand(s); }
        static void init() { srand((uint32)time(NULL)); }

        static uint32 get(uint32 max) { return (uint32)(((uint64)rand() * max) / (RAND_MAX + 1)); }
        static uint32 get(uint32 min, uint32 max) { return get(max - min + 1) + min; }
};

uint32 urand(uint32 min, uint32 max);

#endif
