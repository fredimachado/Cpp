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

#include "common.h"
#include "unit.h"
#include "spell.h"

pEffect SpellEffects[TOTAL_SPELL_EFFECTS] =
{
    &Spell::EffectNULL,                       // 0
    &Spell::EffectDamage,                     // 1
    &Spell::EffectHeal                        // 2
};

extern pEffect SpellEffects[TOTAL_SPELL_EFFECTS];

Spell::Spell(Unit* caster, SpellEntry const* info) :
m_spellInfo(info),
m_caster(caster)
{
    m_healing = 0;
    m_damage = 0;

    m_effectMask = 0;
}

void Spell::DoAllEffectOnTarget()
{
    if (!m_target)
        return;

    if (!m_caster)
        return;

    if (m_healing > 0)
        m_caster->HealBySpell(m_target, m_spellInfo, m_healing);
    else if (m_damage > 0)
    {
        SpellNonMeleeDamage damageInfo(m_caster, m_target, m_spellInfo->Id);
        damageInfo.damage = m_damage;
        m_caster->DealSpellDamage(&damageInfo);
    }
}

void Spell::prepare(Unit* target)
{
    m_target = target;

    Cast();
}

void Spell::Cast()
{
    if (!m_caster)
        return;

    for (uint32 i = 0; i < MAX_SPELL_EFFECTS; ++i)
    {
        if (m_spellInfo->Effect[i] == 0)
            continue;

        HandleEffects(m_caster, i);
        m_effectMask |= (1 << i);
    }

    DoAllEffectOnTarget();
}

void Spell::HandleEffects(Unit* unitTarget, uint32 i)
{
    // if the effect has been handled we skip it
    if (m_effectMask & (1 << i))
        return;

    uint8 eff = m_spellInfo->Effect[i];

    printf("Spell: %u Effect: %u\n", m_spellInfo->Id, eff);

    damage = CalculateDamage(i);

    if (eff < TOTAL_SPELL_EFFECTS)
    {
        (this->*SpellEffects[eff])((SpellEffIndex)i);
    }
}

void Spell::EffectNULL(SpellEffIndex /*effIndex*/)
{
    printf("Spell Effect DUMMY\n\n");
}

void Spell::EffectDamage(SpellEffIndex effIndex)
{
    if (m_target && m_target->IsAlive())
    {
        m_damage += damage;
    }
    printf("Spell Effect Damage: %u\n\n", m_damage);
}

void Spell::EffectHeal(SpellEffIndex effIndex)
{
    if (m_target && m_target->IsAlive())
    {
        m_healing += damage;
    }
    printf("Spell Effect Heal\n\n");
}

int32 Spell::CalculateSpellEffectAmount(SpellEntry const* spellEntry, uint8 effIndex, Unit const* caster)
{
    float basePointsPerLevel = spellEntry->EffectRealPointsPerLevel[effIndex];
    int32 basePoints = spellEntry->EffectBasePoints[effIndex];

    // base amount modification based on caster lvl
    if (caster)
    {
        int32 level = int32(caster->GetLevel());
        basePoints += int32(level * basePointsPerLevel);
    }

    return basePoints;
}
