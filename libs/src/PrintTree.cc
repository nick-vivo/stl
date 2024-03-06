#ifndef __Tree_PrintTree_Class__
#define __Tree_PrintTree_Class__

#include <iostream>
#include "TreeBinary.cc"
#include "Nodes.cc"
#include "Tools.cc"

namespace Tree
{
    template<class T>
    std::ostream& print(const Tree::Node<T>* node, std::ostream& stream = std::cout, bool name = true) 
    {
        if(!node)
            return stream;

        if(name)
        {
            stream << "Nodes: {";
            name = false;
        }

        print(node->left, stream, name);
        print(node->right, stream, name);

        if(!node->right)
            stream << node->data << ", ";
        else
            stream << node->data << "};";

        return stream;
    }

    template<class T>
    std::ostream& printTree(Tree::Node<T>* root, std::ostream& stream = std::cout, Tree::t_index space = 1, Tree::t_index plus = 4) 
    {
        if(!root)
            return stream;

        space += plus;

        printTree(root->right, stream, space, plus);
        stream << std::endl;

        for(int i = 5; i < space; ++i)
        {
            stream << " ";
        }

        stream << root->data << "\n";
        printTree(root->left, stream, space, plus);

        return stream;
    }

    template<class T>
    std::ostream& print(Tree::Binary<T>& tree, std::ostream& stream = std::cout) 
    {

        stream << "Set: {";
        Tree::t_index size = len(tree);

        if(size > 0)
        {
            for(Tree::t_index i = 0; i < size; ++i)
            {
                stream << tree[i];
                if(i < size - 1)
                    stream << ", ";
            }
        }

        stream << "};";

        return stream;
    }
}

#endif