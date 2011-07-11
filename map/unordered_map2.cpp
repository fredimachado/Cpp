/**
 * Studying C++
 * Unordered maps
 *
 * Fredi Machado
 * http://github.com/fredi
 */

#include <iostream>
#include <string>
#include <tr1/unordered_map>

#define UNORDERED_MAP std::tr1::unordered_map

struct Person
{
    std::string name;
    int age;
};

typedef UNORDERED_MAP<std::string, Person> NewMap;

int main() 
{
    NewMap testMap;

    Person bella;
    bella.name = "Isabella Machado";
    bella.age = 1;

    testMap.insert(std::pair<std::string, Person>("Bella", bella));

    testMap["Fredi"].name = "Fredi Machado";
    testMap["Fredi"].age = 28;

    for (NewMap::const_iterator itr = testMap.begin(); itr != testMap.end(); ++itr)
    {
        std::cout << "ID: " << itr->first << "\nName: " << itr->second.name
            << "\nAge: " << itr->second.age << "\n\n";
    }

    return 0;
}