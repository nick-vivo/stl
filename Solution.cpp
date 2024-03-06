#include "libs/Tree"

// #include "libs/src/TreeBinary.cc"

int main() 
{   
    Tree::Binary<int> tree1 = {1, 2, 3, 4, 5, 6, 7};
    Tree::Binary<int> tree2 = {1, 2, 3};
    
    tree1 -= tree2;

    tree1.balance();


    std::cout << "\n";

    Tree::printTree(tree1);
    

    return 0;
}