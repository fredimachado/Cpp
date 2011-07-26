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

#ifndef _SPELL_H
#define _SPELL_H

class Unit;

struct SpellEntry;

class Spell
{
    public:
        void EffectNULL(SpellEffIndex effIndex);
        void EffectDamage(SpellEffIndex effIndex);
        void EffectHeal(SpellEffIndex effIndex);

        Spell(Unit* caster, SpellEntry const* info);

        void prepare(Unit* target);
        void Cast();

        int32 CalculateDamage(uint8 i) { return m_caster->CalculateSpellDamage(m_spellInfo, i); }

        static int32 CalculateSpellEffectAmount(SpellEntry const* spellEntry, uint8 effIndex, Unit const* caster = NULL);

        void HandleEffects(Unit* unitTarget, uint32 i);

        const SpellEntry* const m_spellInfo;

    protected:
        Unit* const m_caster;

        Unit* m_target;

        int32 damage;

        int32 m_damage;
        int32 m_healing;

        void DoAllEffectOnTarget();

        uint32 m_effectMask;
};

typedef void(Spell::*pEffect)(SpellEffIndex effIndex);

#endif
