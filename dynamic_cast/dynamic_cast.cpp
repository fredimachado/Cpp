/**
 * Studying C++
 * Dynamic cast
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <cstdio>
#include <iostream>

class baseClass
{
    protected:
        int x;

    public:
        baseClass()  { x = 55; };
        virtual int returnX() { printf("Base class\n"); return x;}
        void setX(int newXValue) { x = newXValue;}
};

class subBaseClass : public baseClass
{
    public:
        subBaseClass() : baseClass() {};
        int returnX() { printf("Subclass\n"); return x;}
};

int main()
{
    // this one does work because of the virtual method in the base class.
    // but we can create a sub class of the base class first.
    subBaseClass* subBase = new subBaseClass();
    // convert it to the base class
    baseClass* base = dynamic_cast<baseClass*>(subBase);

    // check to see if the casting worked e.g. not equal to 0
    if (base)
        printf("%d\n", base->returnX());
    else
        printf("Bad casting\n");

    // re-set the value of X
    base->setX(30);

    // convert it back again to the sub class and things are still great :).
    subBaseClass* subBase2 = dynamic_cast<subBaseClass*>(base);
    if (subBase2)
        printf("%d\n", subBase2->returnX());
    else
        printf("Bad casting\n");

    return 0;
}
