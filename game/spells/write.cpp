/**
 * Studying C++
 * Write some spells to a file for load in our game
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

#include "../define.h"
#include "../common.h"

int main()
{
    std::ofstream outSpells("../data/spells.dat", std::ios::binary);

    if (!outSpells)
    {
        std::cout << "The file could not be opened." << std::endl;
        exit(1);
    }

    uint32 header = 0x454D4147; // 'GAME'
    uint32 recordCount = 3;
    uint32 fieldCount = 10;
    uint32 recordSize = fieldCount * 4;

    outSpells.write(reinterpret_cast<char*>(&header), sizeof(uint32));
    outSpells.write(reinterpret_cast<char*>(&recordCount), sizeof(uint32));
    outSpells.write(reinterpret_cast<char*>(&fieldCount), sizeof(uint32));
    outSpells.write(reinterpret_cast<char*>(&recordSize), sizeof(uint32));

    // Damage spell
    SpellEntry spell1;
    spell1.Id = 1;
    spell1.Effect[EFFECT_0] = SPELL_EFFECT_DAMAGE;
    spell1.Effect[EFFECT_1] = 0;
    spell1.Effect[EFFECT_2] = 0;
    spell1.EffectRealPointsPerLevel[EFFECT_0] = 2.0f;
    spell1.EffectRealPointsPerLevel[EFFECT_1] = 0.0f;
    spell1.EffectRealPointsPerLevel[EFFECT_2] = 0.0f;
    spell1.EffectBasePoints[EFFECT_0] = 1;
    spell1.EffectBasePoints[EFFECT_1] = 0;
    spell1.EffectBasePoints[EFFECT_2] = 0;

    // More Damage spell
    SpellEntry spell2;
    spell2.Id = 2;
    spell2.Effect[EFFECT_0] = SPELL_EFFECT_DAMAGE;
    spell2.Effect[EFFECT_1] = 0;
    spell2.Effect[EFFECT_2] = 0;
    spell2.EffectRealPointsPerLevel[EFFECT_0] = 2.0f;
    spell2.EffectRealPointsPerLevel[EFFECT_1] = 0.0f;
    spell2.EffectRealPointsPerLevel[EFFECT_2] = 0.0f;
    spell2.EffectBasePoints[EFFECT_0] = 3;
    spell2.EffectBasePoints[EFFECT_1] = 0;
    spell2.EffectBasePoints[EFFECT_2] = 0;

    // Healing spell
    SpellEntry spell3;
    spell3.Id = 3;
    spell3.Effect[EFFECT_0] = SPELL_EFFECT_HEAL;
    spell3.Effect[EFFECT_1] = 0;
    spell3.Effect[EFFECT_2] = 0;
    spell3.EffectRealPointsPerLevel[EFFECT_0] = 1.0f;
    spell3.EffectRealPointsPerLevel[EFFECT_1] = 0.0f;
    spell3.EffectRealPointsPerLevel[EFFECT_2] = 0.0f;
    spell3.EffectBasePoints[EFFECT_0] = 1;
    spell3.EffectBasePoints[EFFECT_1] = 0;
    spell3.EffectBasePoints[EFFECT_2] = 0;

    outSpells.write(reinterpret_cast<char*>(&spell1), sizeof(SpellEntry));
    outSpells.write(reinterpret_cast<char*>(&spell2), sizeof(SpellEntry));
    outSpells.write(reinterpret_cast<char*>(&spell3), sizeof(SpellEntry));

    outSpells.close();

    std::cout << "spells.dat generated." << std::endl;

    return 0;
}
