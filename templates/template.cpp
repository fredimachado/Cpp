/**
 * Studying C++
 * Templates
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

template <class T>
T GetMax (T a, T b)
{
    return (a > b) ? a : b;
}

int main()
{
    int i = 5, j = 6, k;
    long l = 10, m = 5, n;

    k = GetMax<int>(i, j);
    printf("Max int: %d\n", k);

    n = GetMax<long>(l, m);
    printf("Max long: %d\n", n);

    return 0;
}
