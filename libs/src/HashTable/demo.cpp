#include <iostream>
#include <string>
// #include "LinearProbingChainMethod.cc"
#include "LinearProbing.cc"

int main()
{
    HashTable::LinearProbing<std::string, std::string> table(3, 0.25, 0.75);

    std::cout << "\n\n\n" << table.loadFactor();
    std::cout << "\n" << table.toString();

    std::cout << table.add("1", "1");

    std::cout << "\n\n\n" << table.loadFactor();
    std::cout << "\n" << table.toString();

    std::cout << table.add("2", "2");
    
    std::cout << "\n\n\n" << table.loadFactor();
    std::cout << "\n" << table.toString();
    
    std::cout << table.add("3", "3");
    
    std::cout << "\n\n\n" << table.loadFactor();
    std::cout << "\n" << table.toString();

    std::cout << table.add("4", "4");

    std::cout << "\n\n\n" << table.loadFactor();
    std::cout << "\n" << table.toString();


    std::cout << "\n\n\n";
    std::cout << *table.search("4");
    std::cout << "\n\n\n";
}