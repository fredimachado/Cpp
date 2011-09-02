/**
 * Studying C++
 * Function pointers
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>

class MyMath
{
    public:
        int None(int, int) { return 0; };
        int Sum(int a, int b) { return a + b; };
        int Subtract(int a, int b) { return a - b; };
        int Multiply(int a, int b) { return a * b; };
        int Divide(int a, int b) { return a / b; };
};

enum MathFunctions
{
    FUNC_NONE       = 0,
    FUNC_SUM        = 1,
    FUNC_SUBTRACT   = 2,
    FUNC_MULTIPLY   = 3,
    FUNC_DIVIDE     = 4,

    TOTAL_FUNCTIONS = 5
};

// type-definition: 'myMath' now can be used as type
typedef int (MyMath::*myMath)(int, int);

// define using typedef
myMath MathFunctions[TOTAL_FUNCTIONS] =
{
    &MyMath::None,     // 0
    &MyMath::Sum,      // 1
    &MyMath::Subtract, // 2
    &MyMath::Multiply, // 3
    &MyMath::Divide    // 4
};

int main()
{
    // calling a function using an index to address the member function pointer
    // note: an instance of MyMath is needed to call the member functions
    MyMath* instance = new MyMath();

    printf("MyMath::Sum: %d\n", (instance->*MathFunctions[FUNC_SUM])(1, 1));
    printf("MyMath::Subtract: %d\n", (instance->*MathFunctions[FUNC_SUBTRACT])(2, 1));
    printf("MyMath::Multiply: %d\n", (instance->*MathFunctions[FUNC_MULTIPLY])(2, 2));
    printf("MyMath::Divide: %d\n", (instance->*MathFunctions[FUNC_DIVIDE])(4, 2));

    delete instance;

    return 0;
}
