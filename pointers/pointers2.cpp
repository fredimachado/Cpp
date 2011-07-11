/**
 * Studying C++
 * Pointers
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

int main()
{
    int x = 4;
    int* pX = &x;

    printf("[%p] %d\n", pX, *pX);

    int y = 10;
    pX = &y;

    printf("[%p] %d\n", pX, *pX);

    return 0;
}
