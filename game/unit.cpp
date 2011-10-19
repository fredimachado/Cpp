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

#include "unit.h"
#include "player.h"
#include "spell.h"
#include "util.h"

Unit::Unit() : Object()
{
    m_objectTypeId = TYPEID_UNIT;
    m_deathState = ALIVE;
    m_level = 1;
}

void Unit::SetLevel(uint8 lvl)
{
    m_level = lvl;
}

void Unit::SetHealth(uint32 val)
{
    uint32 maxHealth = GetMaxHealth();
    if (maxHealth < val)
        val = maxHealth;

    m_health = val;
}

void Unit::SetMaxHealth(uint32 val)
{
    if (!val)
        val = 1;

    uint32 health = GetHealth();

    m_maxhealth = val;

    if (val < health)
        SetHealth(val);
}

int32 Unit::ModifyHealth(int32 val)
{
    int32 gain = 0;

    if (val == 0)
        return 0;

    int32 curHealth = (int32)GetHealth();

    int32 newHealth = val + curHealth;
    if (newHealth <= 0)
    {
        SetHealth(0);
        return -curHealth;
    }

    int32 maxHealth = (int32)GetMaxHealth();

    if (newHealth < maxHealth)
    {
        SetHealth(newHealth);
        gain = newHealth - curHealth;
    }
    else if (curHealth != maxHealth)
    {
        SetHealth(maxHealth);
        gain = maxHealth - curHealth;
    }

    return gain;
}

uint32 Unit::DealDamage(Unit* victim, uint32 damage)
{
    uint32 health = victim->GetHealth();
    printf("DealDamage: %d to Health %d\n\n", damage, health);

    if (health <= damage)
    {
        printf("DealDamage: %s just DIED\n\n", victim->GetTypeId() == TYPEID_PLAYER ? "Player" : "Victim");
        Kill(victim);
    }
    else
        victim->ModifyHealth(-(int32)damage);

    return damage;
}

void Unit::CalculateMeleeDamage(Unit* victim, uint32 damage, CalcDamageInfo* damageInfo)
{
    damageInfo->attacker    = this;
    damageInfo->target      = victim;
    damageInfo->damage      = 0;
    damageInfo->hitType  = HIT_MISS;

    if (!victim)
        return;

    if (!IsAlive() || !victim->IsAlive())
        return;

    damage += CalculateDamage();
    damageInfo->damage = damage;

    damageInfo->hitType = RollHitType(damageInfo->target);

    switch (damageInfo->hitType)
    {
        case HIT_MISS:
            damageInfo->damage = 0;
            break;
        case HIT_CRITICAL:
            damageInfo->damage += damageInfo->damage;
            break;
        case HIT_NORMAL:
        default:
            break;
    }
}

void Unit::DealMeleeDamage(CalcDamageInfo* damageInfo)
{
    Unit* victim = damageInfo->target;

    if (!victim->IsAlive())
        return;

    DealDamage(victim, damageInfo->damage);
}

void Unit::AttackerStateUpdate(Unit* victim)
{
    if (!IsAlive() || !victim->IsAlive())
        return;

    CalcDamageInfo damageInfo;
    CalculateMeleeDamage(victim, 0, &damageInfo);

    DealMeleeDamage(&damageInfo);
}

HitType Unit::RollHitType(const Unit* victim) const
{
    float miss_chance = 0.1f;
    float crit_chance = 0.25f;

    return RollHitType(victim, int32(crit_chance * 100), int32(miss_chance * 100));
}

HitType Unit::RollHitType(const Unit* victim, int32 crit_chance, int32 miss_chance) const
{
    int32 sum = 0, tmp = 0;
    int32 roll = urand(0, 100);

    tmp = miss_chance;

    if (tmp > 0 && roll < (sum += tmp))
    {
        printf("RollHitType: MISS - roll %d between %d, %d\n", roll, sum - tmp, sum);
        return HIT_MISS;
    }

    tmp = crit_chance;

    if (tmp > 0 && roll < (sum += tmp))
    {
        printf("RollHitType: CRITICAL - roll %d between %d, %d\n", roll, sum - tmp, sum);
        return HIT_CRITICAL;
    }

    printf("RollHitType: NORMAL - roll %d greater than %d\n", roll, sum);
    return HIT_NORMAL;
}

uint32 Unit::CalculateDamage()
{
    float min_damage, max_damage;

    min_damage = m_mindamage;
    max_damage = m_maxdamage;

    if (min_damage > max_damage)
        std::swap(min_damage, max_damage);

    if (max_damage == 0.0f)
        max_damage = 5.0f;

    return urand((uint32)min_damage, (uint32)max_damage);
}

void Unit::Kill(Unit* victim)
{
    if (!victim->GetHealth())
        return;

    victim->SetDeathState(JUST_DIED);
}

void Unit::SetDeathState(DeathState state)
{
    m_deathState = state;

    if (state == JUST_DIED)
        SetHealth(0);
}

int32 Unit::HealBySpell(Unit* victim, SpellEntry const* spellInfo, uint32 addHealth)
{
    int32 gain = DealHeal(victim, addHealth);

    return gain;
}

int32 Unit::DealHeal(Unit* victim, uint32 addHealth)
{
    int32 gain = 0;

    if (addHealth)
        gain = victim->ModifyHealth(int32(addHealth));

    return gain;
}

void Unit::CastSpell(Unit* victim, uint32 spellId)
{
    SpellEntry const* spellInfo = sSpellStore.LookupEntry(spellId);

    if (!spellInfo)
    {
        printf("CastSpell: unknown spell id %i by caster: %s\n", spellId, (GetTypeId() == TYPEID_PLAYER ? "player" : "creature"));
        return;
    }

    Spell* spell = new Spell(this, spellInfo);

    spell->prepare(victim);
}

int32 Unit::CalculateSpellDamage(SpellEntry const* spellProto, uint8 effect_index) const
{
    return Spell::CalculateSpellEffectAmount(spellProto, effect_index, this);
}

void Unit::DealSpellDamage(SpellNonMeleeDamage* damageInfo)
{
    if (damageInfo == 0)
        return;

    Unit* victim = damageInfo->target;

    if (!victim || !victim->IsAlive())
        return;

    DealDamage(victim, damageInfo->damage);
}
