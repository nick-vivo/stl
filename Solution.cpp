#include "libs/Tree"

// #include "libs/src/TreeBinary.cc"

int main() 
{   
    Tree::Binary<int> tree = {1, 2, 3, 4, 5, 6, 7};
    
    tree.balance();


    std::cout << "\n";

    Tree::printTree(tree.root);

    Tree::print(tree);
    // std::cout <<  heigh  t(tree);

    return 0;
}