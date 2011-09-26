/**
 * Studying C++
 * Operator Overloading: operator() to use with std::list remove_if
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <string>
#include <list>

class Person
{
public:
    Person(std::string name, int age) : _name(name), _age(age) {};
    std::string GetName() const { return _name; };
    int GetAge() const { return _age; };

private:
    std::string _name;
    int _age;
};

class PersonDoesNotMeetRequirements
{
public:
    bool operator()(Person const person) const
    {
        // Remove people with name length < 4
        std::string name = person.GetName();
        if (name.length() < 4)
            return true;

        // Remove people with less then 18 years old
        if (person.GetAge() < 18)
            return true;

        return false;
    }
};

int main()
{
    Person fredi("Fredi", 28);
    Person mari("Mari", 26);
    Person bella("Bella", 1);
    Person bob("Bob", 30);

    std::list<Person> myList;

    myList.push_back(fredi);
    myList.push_back(mari);
    myList.push_back(bella);
    myList.push_back(bob);

    myList.remove_if(PersonDoesNotMeetRequirements());

    std::cout << "myList contains:";
    for (std::list<Person>::iterator itr = myList.begin(); itr != myList.end(); ++itr)
        std::cout << " " << (*itr).GetName();
    std::cout << std::endl;

    return 0;
}
