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

#include "creature.h"
#include "player.h"

#include <conio.h>

int main()
{
    Player* player1 = new Player();
    player1->SetMaxHealth(30);
    player1->SetHealth(30);
    player1->SetDamage(1.0f, 4.0f);

    Creature* mob1 = new Creature();
    mob1->SetMaxHealth(30);
    mob1->SetHealth(30);
    mob1->SetDamage(1.0f, 4.0f);

    while (player1->IsAlive() && mob1->IsAlive())
    {
        printf("Player's turn:\n");
        player1->AttackerStateUpdate(mob1);
        getch();

        if (mob1->IsAlive())
        {
            printf("Creature's turn:\n");
            mob1->AttackerStateUpdate(player1);
            getch();
        }
    }

    return 0;
}
