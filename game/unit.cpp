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
#include "util.h"

Unit::Unit() : Object()
{
    m_objectTypeId = TYPEID_UNIT;
    m_deathState = ALIVE;
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

int32 Unit::ModifyHealth(int32 dVal)
{
    int32 gain = 0;

    if (dVal == 0)
        return 0;

    int32 curHealth = (int32)GetHealth();

    int32 val = dVal + curHealth;
    if (val <= 0)
    {
        SetHealth(0);
        return -curHealth;
    }

    int32 maxHealth = (int32)GetMaxHealth();

    if (val < maxHealth)
    {
        SetHealth(val);
        gain = val - curHealth;
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
    damageInfo->TargetState = 0;
    damageInfo->HitInfo     = 0;
    damageInfo->hitOutCome  = MELEE_HIT_MISS;

    if (!victim)
        return;

    if (!IsAlive() || !victim->IsAlive())
        return;

    damage += CalculateDamage();
    damageInfo->damage = damage;

    damageInfo->hitOutCome = RollMeleeOutcomeAgainst(damageInfo->target);

    switch (damageInfo->hitOutCome)
    {
        case MELEE_HIT_MISS:
            damageInfo->HitInfo |= HITINFO_MISS;
            damageInfo->TargetState = VICTIMSTATE_INTACT;
            damageInfo->damage = 0;
            break;
        case MELEE_HIT_NORMAL:
            damageInfo->TargetState = VICTIMSTATE_HIT;
            break;
        case MELEE_HIT_CRIT:
            damageInfo->HitInfo     |= HITINFO_CRITICALHIT;
            damageInfo->TargetState  = VICTIMSTATE_HIT;
            damageInfo->damage += damageInfo->damage;
            break;
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

MeleeHitOutcome Unit::RollMeleeOutcomeAgainst(const Unit* victim) const
{
    float miss_chance = 0.1f;
    float crit_chance = 0.25f;

    return RollMeleeOutcomeAgainst(victim, int32(crit_chance * 100), int32(miss_chance * 100));
}

MeleeHitOutcome Unit::RollMeleeOutcomeAgainst(const Unit* victim, int32 crit_chance, int32 miss_chance) const
{
    int32 sum = 0, tmp = 0;
    int32 roll = urand(0, 100);

    tmp = miss_chance;

    if (tmp > 0 && roll < (sum += tmp))
    {
        printf("RollMeleeOutcomeAgainst: MISS - roll %d between %d, %d\n", roll, sum - tmp, sum);
        return MELEE_HIT_MISS;
    }

    tmp = crit_chance;

    if (tmp > 0 && roll < (sum += tmp))
    {
        printf("RollMeleeOutcomeAgainst: CRITICAL - roll %d between %d, %d\n", roll, sum - tmp, sum);
        return MELEE_HIT_CRIT;
    }

    printf("RollMeleeOutcomeAgainst: NORMAL - roll %d greater than %d\n", roll, sum);
    return MELEE_HIT_NORMAL;
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
