/**
 * Studying C++
 * More on arrays
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

int main()
{
    int values[5];
    int values2[6] = {0, 1, 2, 3, 4, 5};

    values[0] = 5;
    values[1] = 4;
    values[2] = 3;
    values[3] = 2;
    values[4] = 1;

    for (int i = 0; i < 5; i++)
        printf("Value %d : %d\n", i, values[i]);

    int* myPointer = &values[0];
    printf("Pointer value = %d\n", *myPointer);

    myPointer++;
    printf("Pointer value = %d\n", *myPointer);

    return 0;
}
