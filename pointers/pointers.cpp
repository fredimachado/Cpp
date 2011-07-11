/**
 * Studying C++
 * Setting values using the pointer
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

int main()
{
    int firstVal, secondVal;
    int* myPointer;

    myPointer = &firstVal;
    *myPointer = 10;

    myPointer = &secondVal;
    *myPointer = 20;

    printf("First value is %d\n", firstVal);
    printf("Second value is %d\n", secondVal);

    return 0;
} 