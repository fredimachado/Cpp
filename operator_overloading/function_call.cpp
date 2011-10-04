/**
 * Studying C++
 * More on the function call operator
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>

class A
{
public:
    int GetNumber() { return _number; }
    void SetNumber(int number) { _number = number; }

    void operator()(bool debug) const
    {
        if (debug)
            std::cout << _number << std::endl;
        else
            std::cout << "No debug" << std::endl;
    }

    A operator()(int b, int c)
    {
        A a;
        a.SetNumber(b + c);
        return a;
    }

private:
    int _number;
};

int main()
{
    A a, b;

    a.SetNumber(10);

    a(true);
    a(false);

    b = a(10, 20);

    std::cout << b.GetNumber() << std::endl;
    
    return 0;
}
