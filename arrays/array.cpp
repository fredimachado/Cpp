/**
 * Studying C++
 * Arrays
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

int main()
{
    int ar[10][10], i, j;

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            ar[i][j] = i * j;

    for (i = 0; i < 10; i++)
        for (j = 0; j < 10; j++)
            printf("%d x %d = %d\n", i, j, ar[i][j]);

    return 0;
}
