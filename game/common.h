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

#ifndef _COMMON_H
#define _COMMON_H

#include "define.h"

enum SpellEffIndex
{
    EFFECT_0 = 0,
    EFFECT_1 = 1,
    EFFECT_2 = 2
};

#define MAX_SPELL_EFFECTS 3

enum SpellEffects
{
    SPELL_EFFECT_DAMAGE                    = 1,
    SPELL_EFFECT_HEAL                      = 2,
    TOTAL_SPELL_EFFECTS                    = 3
};

struct SpellEntry
{
    uint32    Id;
    uint32    Effect[MAX_SPELL_EFFECTS];
    float     EffectRealPointsPerLevel[MAX_SPELL_EFFECTS];
    int32     EffectBasePoints[MAX_SPELL_EFFECTS];
};

#include <cstdio>
#include <cstdlib>

#include <set>

#endif
