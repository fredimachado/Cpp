/**
 * Studying C++
 * Classes, global and local scope
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

class World
{
    public:
        World(int id)
            : _identifier(id)
        {
            printf("Hello from %d.\n", _identifier);
        }

        ~World()
        {
            printf("Good bye from %d.\n", _identifier);
        }

    private:
        const int _identifier;
};

World TheWorld(1);

int main()
{
    World myWorld(2);

    for (int i = 3; i < 6; ++i)
        World aWorld(i);

    World oneMoreWorld(6);
}
