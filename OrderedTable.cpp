#include <iostream>
#include "OrderedTable.h"
#include <map>
#include <string>

int main()
{
    OrderedTable<int, std::string> o;

    o.emplace(1, "one");
    o.emplace(2, "two");
    o.emplace(3, "three");
    o.emplace(4, "four");

    o.insert({ 5, "five" });

    o.erase(3);

    o.erase(o.begin());

    std::cout << (*(o.find(4))).second << std::endl;


    
    
}