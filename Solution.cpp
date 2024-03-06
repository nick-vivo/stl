#include "libs/Tree"

// #include "libs/src/TreeBinary.cc"

int main() 
{   
    Tree::Binary<int> tree1({1, 2, 3, 4, 5, 6});
    
    tree1 += {7, 8, 9};

    std::cout << "\n-------------------------\n";


    Tree::print(tree1);

    std::cout << "\n-------------------------\n";

    Tree

    Tree::printTree(tree1);
    
    tree1.balance();

    std::cout << "\n-------------------------\n" << "\nБаланс: " << tree1.isBalanced() << "\n\n-------------------------\n";

    Tree::printTree(tree1);
    

    return 0;
}