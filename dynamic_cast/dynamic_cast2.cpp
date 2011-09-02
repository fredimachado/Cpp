/**
 * Studying C++
 * Dynamic cast
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>
#include <iostream>
#include <typeinfo>

struct A
{
    virtual void test()
    {
        printf("in A\n");
    }
};

struct B : A
{
    virtual void test()
    {
        printf("in B\n");
    }

    void test2()
    {
        printf("test2 in B\n");
    }
};

struct C : B
{
    virtual void test()
    {
        printf("in C\n");
    }

    void test2()
    {
        printf("test2 in C\n");
    }
};

void Globaltest(A& a)
{
    try
    {
        C& newC = dynamic_cast<C&>(a);
        printf("in Globaltest\n");
        newC.test2();
    }
    catch(const std::bad_cast& e)
    {
        printf("%s: This object is not of type C\n", e.what());
    }
}

int main()
{
    A* newC = new C;
    A* newB = new B;

    newC->test();

    B* cToB = dynamic_cast<B*>(newC);
    if (cToB)
        cToB->test2();

    // will not work because B knows nothing about C
    C* bToC = dynamic_cast<C*>(newB);
    if (bToC)
        bToC->test2();

    C newC2;
    Globaltest(newC2);

    // will fail because B knows nothing about C
    B newB2;
    Globaltest(newB2);

    delete newC;
    delete newB;
}