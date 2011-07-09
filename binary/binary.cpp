/**
 * Studying C++
 * Convert integers to binary and print
 *
 * Original code:
 * http://www.c.happycodings.com/Miscellaneous/code9.html
 */

#include <cstdio>

void dec_bin(int);

int main()
{
    int input = 0;

    printf("\nEnter a negative value to exit.\n\n");

    while (input >= 0)
    {
        printf("Digit (0-255): ");
        scanf("%d", &input);

        if (input >= 0 && input <= 255)
            dec_bin(input);
    }

    return 0;
}

/**
 * convert decimal to binary and print the result
 */
void dec_bin(int number)
{
    int x, y;
    x = y = 0;

    for (y = 7; y >= 0; y--)
    {
        x = number / (1 << y);
        number = number - x * (1 << y);
        printf("%d", x);
    }

    printf("\n");
}
