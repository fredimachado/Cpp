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

enum HitType
{
    HIT_MISS,
    HIT_CRITICAL,
    HIT_NORMAL
};

class Unit;

struct CalcDamageInfo
{
    Unit*  attacker;
    Unit*  target;
    uint32 damage;
    HitType hitType;
};

struct SpellNonMeleeDamage
{
    SpellNonMeleeDamage(Unit *_attacker, Unit *_target, uint32 _SpellID)
        : target(_target), attacker(_attacker), SpellID(_SpellID), damage(0)
    {}

    Unit*  target;
    Unit*  attacker;
    uint32 SpellID;
    uint32 damage;
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

        void Kill(Unit* victim);

        bool IsAlive() const { return m_deathState == ALIVE; };
        virtual void SetDeathState(DeathState state);

        uint32 DealDamage(Unit* victim, uint32 damage);

        void AttackerStateUpdate(Unit* victim);

        void CalculateMeleeDamage(Unit* victim, uint32 damage, CalcDamageInfo* damageInfo);
        void DealMeleeDamage(CalcDamageInfo* damageInfo);

        int32 CalculateSpellDamage(SpellEntry const* spellProto, uint8 effect_index) const;
        void DealSpellDamage(SpellNonMeleeDamage* damageInfo);

        int32 HealBySpell(Unit* victim, SpellEntry const* spellInfo, uint32 addHealth);
        int32 DealHeal(Unit *pVictim, uint32 addhealth);

        void CastSpell(Unit* victim, SpellEntry const* spellInfo);

        uint32 CalculateDamage();

        HitType RollHitType(const Unit* victim) const;
        HitType RollHitType(const Unit* victim, int32 crit_chance, int32 miss_chance) const;

    protected:
        explicit Unit();

        DeathState m_deathState;

    private:
        uint8 m_level, m_race, m_class, m_gender;
        uint32 m_health, m_maxhealth;

        float m_mindamage, m_maxdamage;
};

#endif
