#include "libs/Tree"

// #include "libs/src/TreeBinary.cc"

int main() 
{   
    Tree::Binary<int> tree = {1, 2, 3, 4, 5, 6, 7};
    
    tree.balance();


    std::cout << "\n";

    Tree::Node<int> *ptr = tree.cloneNodes();

    Tree::printTree(ptr);

    TreeBinary::deleteNodes(ptr);

    Tree::print(tree);
    std::cout <<  height(tree);

    return 0;
}