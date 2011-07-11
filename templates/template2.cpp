/**
 * Studying C++
 * More on templates
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

#include "stack.h"

int main()
{
    typedef Stack<float> FloatStack;
    typedef Stack<int> IntStack;

    FloatStack fs(5);
    float f = 1.1f;
    printf("Pushing elements onto fs\n");
    while (fs.push(f))
    {
        printf("%f ", f);
        f += 1.1f;
    }
    printf("\nStack Full.\n");

    printf("\nPopping elements from fs\n");
    while (fs.pop(f))
        printf("%f ", f);
    printf("\nStack Empty\n");

    IntStack is;
    int i = 1.1;
    printf("\nPushing elements onto is\n");
    while (is.push(i))
    {
        printf("%d ", i);
        ++i;
    }
    printf("\nStack Full\n");

    printf("\nPopping elements from is\n");
    while (is.pop(i))
        printf("%d ", i);
    printf("\nStack Empty\n");

    return 0;
}
