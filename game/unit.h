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

#ifndef _UNIT_H
#define _UNIT_H

#include "object.h"

enum DeathState
{
    ALIVE       = 0,
    JUST_DIED   = 1,
    CORPSE      = 2,
    DEAD        = 3
};

enum MeleeHitOutcome
{
    MELEE_HIT_MISS,
    MELEE_HIT_CRIT,
    MELEE_HIT_NORMAL
};

enum VictimState
{
    VICTIMSTATE_INTACT      = 0,
    VICTIMSTATE_HIT         = 1
};

enum HitInfo
{
    HITINFO_MISS            = 0x00000010,
    HITINFO_CRITICALHIT     = 0x00000200
};

class Unit;

struct CalcDamageInfo
{
    Unit*  attacker;
    Unit*  target;
    uint32 damage;
    uint32 HitInfo;
    uint32 TargetState;
    MeleeHitOutcome hitOutCome;
};

class Unit : public Object
{
    public:
        uint8 GetLevel() const { return m_level; }
        void SetLevel(uint8 lvl);
        uint8 GetRace() const { return m_race; }
        uint8 GetClass() const { return m_class; }
        uint8 GetGender() const { return m_gender; }

        uint32 GetHealth() const { return m_health; }
        uint32 GetMaxHealth() const { return m_maxhealth; }

        void SetHealth(uint32 val);
        void SetMaxHealth(uint32 val);
        inline void SetFullHealth() { SetHealth(GetMaxHealth()); }
        int32 ModifyHealth(int32 val);

        void SetDamage(float min_damage, float max_damage) { m_mindamage = min_damage; m_maxdamage = max_damage; }

        void CombatStop();

        void Kill(Unit* victim);

        bool IsAlive() const { return m_deathState == ALIVE; };
        virtual void SetDeathState(DeathState state);

        uint32 DealDamage(Unit* victim, uint32 damage);

        void AttackerStateUpdate(Unit* victim);

        void CalculateMeleeDamage(Unit* victim, uint32 damage, CalcDamageInfo* damageInfo);
        void DealMeleeDamage(CalcDamageInfo* damageInfo);

        uint32 CalculateDamage();

        MeleeHitOutcome RollMeleeOutcomeAgainst(const Unit* victim) const;
        MeleeHitOutcome RollMeleeOutcomeAgainst(const Unit* victim, int32 crit_chance, int32 miss_chance) const;

    protected:
        explicit Unit();

        float m_mindamage, m_maxdamage;

        DeathState m_deathState;

    private:
        uint8 m_level, m_race, m_class, m_gender;
        uint32 m_health, m_maxhealth;
};

#endif
