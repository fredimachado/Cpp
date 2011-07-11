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

int main()
{
    typedef UNORDERED_MAP<int, std::string> NewMap;

    NewMap testMap;

    testMap.insert(std::pair<int, std::string>(0, "Hello"));
    testMap[1] = "World";
    testMap[2] = "Bye!";

    for (NewMap::const_iterator itr = testMap.begin(); itr != testMap.end(); ++itr)
    {
        std::cout << (*itr).first << ": " << (*itr).second << std::endl;
    }

    return 0;
}
