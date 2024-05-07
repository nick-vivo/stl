#include <iostream>
#include "LinearProbing.cc"

HashTable::LinearProbing<int, int> repeatElementsInArray(int* arr, int size)
{
    HashTable::LinearProbing<int, int> table;
    
    for (int i = 0; i < size; ++i) 
    {
        if(table.containsKey(arr[i])) table.insert(arr[i], 1 + *table.search(arr[i]));
        else table.add(arr[i], 1);
    }

    return table;
}


int main()
{
    int myArray[16] = {1, 2, 2,1, 3, 3, 5,1, 5, 4,1, 4, 6, 1, 3, 6};

    HashTable::LinearProbing<int, int> tmp = repeatElementsInArray(myArray, 16);

    std::cout << "\n" << tmp.toString() << "\n";

    // std::cout << abs.add("a", "1");
    // std::cout << abs.add("bac", "2");
    // std::cout << abs.add("baba", "3");

    // std::cout << "\n\nLOAD_FACTOR: " << abs.goodLoadFactor() << "\n";
    // std::cout << "LOAD_FACTOR_FREQ: " << abs.loadFactor() << "\n";
    // std::cout << "\n" << abs.toString() << "\n\n";

    // std::cout << abs.contains("a");
    // std::cout << *abs.search("bac");

    // HashTable::LinearProbing<std::string, std::string> abs2(abs);

    // std::cout << "\n\nLOAD_FACTOR: " << abs2.goodLoadFactor() << "\n";
    // std::cout << "LOAD_FACTOR_FREQ: " << abs2.loadFactor() << "\n";
    // std::cout << "\n" << abs2.toString() << "\n\n";
}
