/**
 * Studying C++
 * Simple way to write and read objects from a file
 * 
 * Fredi Machado
 * http://github.com/fredi
 */

#include <string>

struct Stats
{
    int hp;     // Hit Points
    int mana;   // Mana
    int ap;     // Attack Power
    int sp;     // Spell Power
};

class Player
{
    public:
        Player(std::string = "", int = 0, int = 0, int = 0, int = 0);

        void SetName(std::string);
        const char* GetName() const { return _name; }

        void SetHP(int hp) { _stats.hp = hp; }
        void SetMana(int mana) { _stats.mana = mana; }
        void SetAP(int ap) { _stats.ap = ap; }
        void SetSP(int sp) { _stats.sp = sp; }

        int GetHP() { return _stats.hp; }
        int GetMana() { return _stats.mana; }
        int GetAP() { return _stats.ap; }
        int GetSP() { return _stats.sp; }

    private:
        char _name[20];
        Stats _stats;
};
