#ifndef __Tree_BinaryTree_Class__
#define __Tree_BinaryTree_Class__

#include "Nodes.cc"
#include "Tools.cc"
#include <initializer_list>


namespace BinaryTree
{

    template<class T>
    void insert(Tree::Node<T>*& node, const T &value) noexcept
    {
        if(!node)
            node = new Tree::Node<T>(value);

        if(node->data < value)
            insert(node->right, value);
        else if(node->data > value)
            insert(node->left, value);
    }

    template<class T>
    void insertNodes(Tree::Node<T>*& nodeForInsertion , const Tree::Node<T>* const nodeFromWhichToCopy) noexcept
    {
        if(!nodeFromWhichToCopy)
            return;

        insert(nodeForInsertion, nodeFromWhichToCopy->data);

        insertNodes(nodeForInsertion, nodeFromWhichToCopy->left);
        insertNodes(nodeForInsertion, nodeFromWhichToCopy->right);

    }

    template<class T>
    void deleteNodes(Tree::Node<T>*& nodeForDeleteNodes , const Tree::Node<T>* const nodeFromDelete) noexcept
    {
        if(!nodeFromDelete)
            return;

        deleteNodes(nodeForDeleteNodes, nodeFromDelete->left);
        deleteNodes(nodeForDeleteNodes, nodeFromDelete->right);

        removeValueWithoutChangeNodes(nodeForDeleteNodes, nodeFromDelete->data);
    }

    template<class T>
    bool nodeInNodes(const Tree::Node<T>* const nodeForSearch, const Tree::Node<T>* const nodeValues)
    {
        if(!nodeForSearch || !nodeValues)
            return true;
        return valueInNodes(nodeValues, nodeForSearch->data) && nodeInNodes(nodeForSearch->left, nodeValues) && nodeInNodes(nodeForSearch->right, nodeValues);

    }

    template<class T>
    bool nodesEqualAboutValue(const Tree::Node<T>* const node1, const Tree::Node<T>* const node2)
    {
        return nodeInNodes(node1, node2) && nodeInNodes(node2, node1);
    }



// Для работы с деревом
    template<class T>
    void popNodes(Tree::Node<T>*& node) noexcept 
    {
        if(node)
        {
            popNodes(node->left);
            popNodes(node->right);
            delete node;
            node = nullptr;
        }
    }

    template<class T>
    void removeChangeNodes(Tree::Node<T>*& node, const T &value) noexcept
    {
        if(!node)
            return;
        else if(node->data == value)
        {   
            if(!node->left)
            {
                Tree::Node<T>* tmp = node;
                node = node->right;
                delete tmp;
            }
            else if(!node->right)
            {
                Tree::Node<T>* tmp = node;
                node = node->left;
                delete tmp;
            }
            else
            {
                Tree::Node<T>* right = node->right;
                Tree::Node<T>* left = node->left;
                
                Tree::Node<T>* iterator = node;
                
                node = node->right;
                delete iterator;
                

                iterator = node;

                while(iterator->left) 
                    iterator = iterator->left;

                iterator->left = left;
            }
        }
        else if(node->data < value)
            removeChangeNodes(node->right, value);
        else if(node->data > value)
            removeChangeNodes(node->left, value);        
    }

    template<class T>
    void removeValueWithoutChangeNodes(Tree::Node<T>*& node, const T &value) noexcept
    {
        if(!node)
            return;
        else if(node->data == value)
        {   
            if(!node->left)
            {
                Tree::Node<T>* tmp = node;
                node = node->right;
                delete tmp;
            }
            else if(!node->right)
            {
                Tree::Node<T>* tmp = node;
                node = node->left;
                delete tmp;
            }
            else
            {
                Tree::Node<T>* iterator = node->left;
                Tree::Node<T>* prev = node;
                bool goRight = false;

                while(iterator->right)
                {
                    goRight = true;
                    prev = iterator;
                    iterator = iterator->right;
                }
                node->data = iterator->data;

                delete iterator;

                if(goRight)
                    prev->right = nullptr;
                else
                    prev->left = nullptr;
                
            }
        }
        else if(node->data < value)
            removeValueWithoutChangeNodes(node->right, value);
        else if(node->data > value)
            removeValueWithoutChangeNodes(node->left, value);
        
    }

    template<class T>
    Tree::t_count height(const Tree::Node<T>* const node) noexcept 
    {
        if(node)
            return 1 + Tree::max(height(node->left), height(node->right));
        return 0;

    }

    template<class T>
    Tree::t_count len(const Tree::Node<T>* const node) noexcept
    {
        if (node)
            return len(node->right) + len(node->left) + 1;
        else 
            return 0;
    }

    template<class T>
    bool valueInNodes(const Tree::Node<T>* const root, const T &value) noexcept 
    {
        if(!root)
            return false;
        
        if(root->right && root->data < value)
            return valueInNodes(root->right, value);
        else if(root->left && root->data > value)
            return valueInNodes(root->left, value);
        else if(root->data == value)
            return true;
            
        return false;
    }
    
// Для балансировки
    template<class T>
    bool isBalanced(const Tree::Node<T>* const root) noexcept
    {
        if(!root)
            return true;

        Tree::t_index first = height(root->left);
        Tree::t_index second = height(root->right);

        if(Tree::abs(first - second) > 1)
        return false;
    
        return isBalanced(root->left) && isBalanced(root->right);
    }

    template<class T>
    Tree::t_index checkBalanceFactor(const Tree::Node<T>* const root)
    {
        if(root)
            return height(root->right) - height(root->left);
        
        return 0;
    }

//Переброс левого витка на право
    template<class T>
    void leftRotate(Tree::Node<T>*& node)
    {
        if(!node || !node->right)
            throw "Невозможно соверишть поворот. Узел пуст или правый виток пуст.(перебрасывает правый виток на лево)";

        Tree::Node<T>* right = node->right;
        Tree::Node<T>* rightLeft = right->left;

        right->left = node;
        node->right = rightLeft;

        node = right;
    }

//Переброс правого витка на лево
    template<class T>
    void rightRotate(Tree::Node<T>*& node)
    {  
        if(!node || !node->left)
            throw "Невозможно соверишть поворот. Узел пуст или левый виток пуст.(перебрасывает левый виток на право)";
        Tree::Node<T>* left = node->left;
        Tree::Node<T>* leftRight = left->right;

        left->right = node;
        node->left = leftRight;

        node = left;
    }

    template<class T>
    void balanceToAVL(Tree::Node<T>*& node)
    {
        if(!node)
            return;
            
        balanceToAVL(node->right);
        balanceToAVL(node->left);

        Tree::t_index balanceFactor = checkBalanceFactor(node);
        Tree::t_count heightRoot = height(node);

        if (balanceFactor > 1)
        {
            if(checkBalanceFactor(node->right) < 0)
                rightRotate(node->right);
            leftRotate(node);

            if(heightRoot > 2)
                balanceToAVL(node->left);
        }
        else if (balanceFactor < -1)
        {
            if (checkBalanceFactor(node->left) > 0)
                leftRotate(node->left);
            rightRotate(node);
            
            if(heightRoot > 2)
                balanceToAVL(node->right);
        }

    }
    
// Обход по дереву
    template<class T>
    Tree::Node<T>* getNodeByIndexLinear(Tree::Node<T>* node, Tree::t_index index)
    {

        Tree::Node<T> *nodeFirst, *nodeSecond;

        if(index == 0)
            return node;
        else if(index < 0)
        {
            nodeFirst = node->right;
            nodeSecond = node->left;
        }
        else if(index > 0)
        {
            nodeFirst = node->left;
            nodeSecond = node->right;
        }

        Tree::t_index lenLeft = len(nodeFirst);

        if( Tree::abs(index) <= lenLeft)
            return getNodeByIndexLinear(nodeFirst, index + (index > 0 ? -1 : 1));
        else
        {
            if(len(nodeSecond) == 0)
                return nullptr;

            return getNodeByIndexLinear(nodeSecond, index + (index > 0 ? -1 : 1)* (lenLeft + 1));
        }       
    }

    template<class T>
    Tree::Node<T>* getNodeByIndexHelper(Tree::Node<T>* root, int &count, Tree::t_index index) 
    {
        if (!root)
            return nullptr;

        Tree::Node<T>* left = nullptr, * right = nullptr;
        
        if(index >= 0)
        {
            left = root->left;
            right = root->right;
        }
        else
        {
            left = root->right;
            right = root->left;
        }

        left = getNodeByIndexHelper(left, count, index);
    
        if (left)
            return left;

        index >= 0 ? ++count : --count;

        if (count == index)
            return root;

        return getNodeByIndexHelper(right, count, index);
    }

    template<class T>
    Tree::Node<T>* getNodeByMinValues(Tree::Node<T>* root, int index) 
    {
        int count;
        index >= 0 ? count = -1 : count = 0;
        return getNodeByIndexHelper(root, count, index);
    }

template<class T>
class BinaryTree 
{
public:
    
    Tree::Node<T> *root;

    BinaryTree(): root(nullptr) {}

    BinaryTree(std::initializer_list<T> ls): BinaryTree()
    {
        for(T elem : ls)
            this->add(elem);
    }

    BinaryTree(const T& value): BinaryTree() 
    {
        this->root = new Tree::Node<T>(value);
    }

    BinaryTree(const Tree::Node<T>* const node): BinaryTree() 
    {
        insertNodes(root, node);
    }

    BinaryTree(const BinaryTree<T>& other): BinaryTree()
    {
        insertNodes(root, other.root);
    }

    BinaryTree(BinaryTree<T>&& other): BinaryTree()
    {
        this->swap(other);  
    }

    ~BinaryTree()
    {
        popNodes(root);        
    }
    
    void add(const T &value) noexcept
    {
        insert(this->root, value);
    }
    
    void discard(const T &value) noexcept
    {
        removeValueWithoutChangeNodes(this->root, value);
    }

    Tree::t_count elevation() const noexcept
    {
        return height(this->root);
    }

    Tree::t_count size() const noexcept
    {
        return len(this->root);
    }

    bool in(const T &value) const noexcept
    {
        return valueInNodes(this->root, value);
    }


//Балансировка дерева
    void balance() noexcept
    {
        balanceToAVL(this->root);
    }

    bool isBalanced() const noexcept
    {
        return isBalanced(this->root);
    }


//Основной функционал закончился.
    void swap(BinaryTree<T> binaryTree) noexcept
    {
        Tools::swap(this->root, binaryTree.root);
    }

    BinaryTree<T>& operator+=(const T& value) noexcept
    {
        this->add(value);
        return *this;
    }

    BinaryTree<T>& operator+=(const BinaryTree<T>& binaryTree) noexcept
    {
        insertNodes(root, binaryTree.root);
        return *this;
    }

    BinaryTree<T>& operator+=(std::initializer_list<T> ls) noexcept
    {
        for(T elem : ls)
            this->add(elem);
        return *this;
    }

    BinaryTree<T>& operator=(const BinaryTree<T>& binaryTree) noexcept
    {   
        popNodes(this->root);
        insertNodes(this->root, binaryTree.root);
        return *this;
    }

    BinaryTree<T>& operator=(const T& value) noexcept
    {   
        popNodes(this->root);
        this->add(value);
        return *this;
    }

    BinaryTree<T>& operator-=(const T& value) noexcept
    {
        this->discard(value);
        return *this;
    }

    BinaryTree<T>& operator-=(const BinaryTree<T>& binaryTree) noexcept
    {
        deleteNodes(root, binaryTree.root);
        return *this;
    }

    BinaryTree<T>& operator-=(std::initializer_list<T> ls) noexcept
    {
        for(T elem : ls)
            this->discard(elem);
        return *this;
    }

    bool operator==(const BinaryTree<T>& binaryTree) noexcept
    {
        return nodesEqualAboutValue(binaryTree.root, this->root);
    }

    bool operator!=(const BinaryTree<T>& binaryTree) noexcept
    {
        return !nodesEqualAboutValue(binaryTree.root, this->root);
    }


    T operator[](Tree::t_index index)
    {
        Tree::Node<T> *tmp = getNodeByMinValues(root, index);

        if(!tmp)
            throw "Пуст сетик";
        return tmp->data;
    }
};

template<class T>
Tree::t_count height(const BinaryTree<T>& binaryTree) noexcept 
{
    return binaryTree.elevation();
}

template<class T>
Tree::t_count len(const BinaryTree<T>& binaryTree) noexcept
{
    return binaryTree.size();
}


template<class T>
BinaryTree<T> operator+(const BinaryTree<T>& binaryTree, const T& value) noexcept
{
    BinaryTree<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

template<class T>
BinaryTree<T> operator+(const T& value, const BinaryTree<T>& binaryTree) noexcept
{
    BinaryTree<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

template<class T>
BinaryTree<T> operator+(const BinaryTree<T>& binaryTree1, const BinaryTree<T>& binaryTree2) noexcept
{
    BinaryTree<T> sum(binaryTree1);
    sum += binaryTree1;
    sum += binaryTree2;
    sum.balance();
    return sum;
}

template<class T>
BinaryTree<T> operator-(const BinaryTree<T>& binaryTree, const T& value) noexcept
{
    BinaryTree<T> sum(binaryTree);
    sum.discard(value);
    return sum;
}

template<class T>
BinaryTree<T> operator-(const BinaryTree<T>& binaryTree1, const BinaryTree<T>& binaryTree2) noexcept
{
    BinaryTree<T> sum(binaryTree1);
    sum -= binaryTree2;
    sum.balance();
    return sum;
}

}

#endif