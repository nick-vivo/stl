#ifndef __Tree_Binary_Class__
#define __Tree_Binary_Class__

#include "Node.cc"
#include "Tools.cc"
#include <initializer_list>

/**
 * @file src/Tree/TreeBinary.cc, lib - Tree.
 * 
 * @brief Бинарное дерево поиска
 * 
 * Файл с бинарным деревом поиска и функиями для работы с бинарными
 * узлами поиска.
 * 
 * Используемые стандартные библиотеки:
 * 1.#incldue <initializer_list>;
 */


/**
* @brief Содержит функции для работы с 
* 
* Функция меняет местами два объекта. Нужно иметь оператор.
* присваивания и конструктор копирования. Стандартный swap(a, b);
*
* Используется рекурсия вида: Значение больше - идём вправо, меньше - идём влево.
*
*/
namespace TreeBinary
{

    /**
    * @brief Вставка значения в какой-нибудь узел корня.
    * 
    * Функция рекурсивно проходится по узлам и вставляет значение в зависимости
    * от параметра value.(выделяется память, после надо удалить с помощью функций
    * очистки)
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @tparam T Тип поля data узлов
    * 
    * @param node Корень узла для вставки.
    * @param value Значение для вставки.
    * 
    * @return void.
    */
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

    /**
    * @brief Вставка значений из одного узла в другой.
    * 
    * Функция рекурсивно вставляет элементы из nodeFromWhichToCopy в
    * nodeForInsertion. В результате в узле nodeForInsertion будут
    * присутствовать значения из nodeFromWhichToCopy.(выделяется память,
    * после надо удалить с помощью функций очистки)
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    *
    * @tparam T Тип поля data узлов.
    * 
    * @param nodeForInsertion Узел для вставки.
    * @param nodeFromWhichToCopy Значения копирования.
    * 
    * @return void.
    */
    template<class T>
    void insertNodes(Tree::Node<T>*& nodeForInsertion , const Tree::Node<T>* const nodeFromWhichToCopy) noexcept
    {
        if(!nodeFromWhichToCopy)
            return;

        insert(nodeForInsertion, nodeFromWhichToCopy->data);

        insertNodes(nodeForInsertion, nodeFromWhichToCopy->left);
        insertNodes(nodeForInsertion, nodeFromWhichToCopy->right);

    }

    /**
    * @brief Удаление значения из корня.
    * 
    * Функция рекурсивно проходится по элементам и удаляет нужный, меняя
    * структуру дерева. Не рекомендуется использовать. Лучше использовать
    * аналог removeChangeNodes(...) для сохранения структуры дерева.(присходит
    * очистка памяти, удалённые узлы = nullptr)
    * 
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node Узел для удаления.
    * @param value Значение которое нужно удалить.
    * 
    * @return void.
    */
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

    /**
    * @brief Удаление значения из корня.
    * 
    * Функция рекурсивно проходится по элементам и удаляет нужный, меняя только
    * два значения в структуре дерева(само значение и максимальное из левого
    * подузла), то есть структура дерева не страдает.(присходит очистка памяти,
    * удалённые узлы = nullptr)
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    *
    * @tparam T Тип поля data узлов.
    * 
    * @param node Узел для удаления.
    * @param value Значение которое нужно удалить.
    * 
    * @return void.
    */
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

    /**
    * @brief Удаление значений из одного узла, взяв значения из другого.
    * 
    * Функция рекурсивно удаляет элементы nodeFromDelete из nodeForDeleteNodes
    * nodeFromDelete. В результате в узле nodeForInsertion будут присутствовать
    * значения из nodeFromWhichToCopy. (присходит очистка памяти, удалённые
    * узлы = nullptr)
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param nodeForDeleteNodes Узел для очистки.
    * @param nodeFromDelete Узел значений.
    * 
    * @return void.
    */
    template<class T>
    void popNodes(Tree::Node<T>*& nodeForDeleteNodes , const Tree::Node<T>* const nodeFromDelete) noexcept
    {
        if(!nodeFromDelete)
            return;

        popNodes(nodeForDeleteNodes, nodeFromDelete->left);
        popNodes(nodeForDeleteNodes, nodeFromDelete->right);

        removeValueWithoutChangeNodes(nodeForDeleteNodes, nodeFromDelete->data);
    }

    /**
    * @brief Содержит ли nodeForSearch все значения из nodeValues.
    * 
    * Функция рекурсивно проверяет находятся ли все значения из nodeForSearch
    * в nodeValues
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param nodeForSearch Проверяемый узел.
    * @param nodeValues Значения для проверки.
    * 
    * @return false - если не все значения в nodeForSearch, и true в противном случае.
    */
    template<class T>
    bool nodeInNodes(const Tree::Node<T>* const nodeForSearch, const Tree::Node<T>* const nodeValues) noexcept
    {
        if(!nodeForSearch || !nodeValues)
            return true;
        return valueInNodes(nodeValues, nodeForSearch->data) && nodeInNodes(nodeForSearch->left, nodeValues) && nodeInNodes(nodeForSearch->right, nodeValues);

    }

    /**
    * @brief Равны ли узлы по значениям.
    * 
    * Функция рекурсивно проверяет все ли значения из node<1,2>находятся в
    * node<2,1>.
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node1 Первый узел.
    * @param nodeFromWhichToCopy Второй узел проверки.
    * 
    * @return true если их значения равны. false если значения разные.
    */
    template<class T>
    bool nodesEqualAboutValue(const Tree::Node<T>* const node1, const Tree::Node<T>* const node2) noexcept
    {
        return nodeInNodes(node1, node2) && nodeInNodes(node2, node1);
    }

    /**
    * @brief Удаление значений из одного узла, взяв значения из другого.
    * 
    * Функция рекурсивно удаляет элементы nodeFromDelete из nodeForDeleteNodes
    * nodeFromDelete. В результате в узле nodeForInsertion будут присутствовать
    * значения из nodeFromWhichToCopy. (присходит очистка памяти, удалённые
    * узлы = nullptr)
    *
    * @throw Нету.
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param nodeForDeleteNodes Узел для очистки.
    * @param nodeFromDelete Узел значений.
    * 
    * @return void.
    */
    template<class T>
    void deleteNodes(Tree::Node<T>*& node) noexcept 
    {
        if(node)
        {
            deleteNodes(node->left);
            deleteNodes(node->right);
            delete node;
            node = nullptr;
        }
    }

    template<class T>
    Tree::t_count height(const Tree::Node<T>* const node) noexcept 
    {
        if(node)
            return 1 + Tools::max(height(node->left), height(node->right));
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
}

namespace Tree
{
template<class T>
class Binary
{
public:
    
    Tree::Node<T> *root;

    Binary(): root(nullptr) {}

    Binary(std::initializer_list<T> ls): Binary()
    {
        for(T elem : ls)
            this->add(elem);
    }

    Binary(const T& value): Binary() 
    {
        this->root = new Tree::Node<T>(value);
    }

    Binary(const Tree::Node<T>* const node): Binary() 
    {
        TreeBinary::insertNodes(root, node);
    }

    Binary(const Binary<T>& other): Binary()
    {
        TreeBinary::insertNodes(root, other.root);
    }

    Binary(Binary<T>&& other): Binary()
    {
        this->swap(other);  
    }

    ~Binary()
    {
        TreeBinary::deleteNodes(root);        
    }
    
    void add(const T &value) noexcept
    {
        TreeBinary::insert(this->root, value);
    }
    
    void discard(const T &value) noexcept
    {
        TreeBinary::removeValueWithoutChangeNodes(this->root, value);
    }

    Tree::t_count elevation() const noexcept
    {
        return TreeBinary::height(this->root);
    }

    Tree::t_count size() const noexcept
    {
        return TreeBinary::len(this->root);
    }

    bool in(const T &value) const noexcept
    {
        return TreeBinary::valueInNodes(this->root, value);
    }


//Балансировка дерева
    void balance() noexcept
    {
        TreeBinary::balanceToAVL(this->root);
    }

    bool isBalanced() const noexcept
    {
        return TreeBinary::isBalanced(this->root);
    }


//Основной функционал закончился.
    void swap(Binary<T> binaryTree) noexcept
    {
        Tools::swap(this->root, binaryTree.root);
    }

    Binary<T>& operator+=(const T& value) noexcept
    {
        this->add(value);
        return *this;
    }

    Binary<T>& operator+=(const Binary<T>& binaryTree) noexcept
    {
        TreeBinary::insertNodes(root, binaryTree.root);
        return *this;
    }

    Binary<T>& operator+=(std::initializer_list<T> ls) noexcept
    {
        for(T elem : ls)
            this->add(elem);
        return *this;
    }

    Binary<T>& operator=(const Binary<T>& binaryTree) noexcept
    {   
        TreeBinary::deleteNodes(this->root);
        TreeBinary::insertNodes(this->root, binaryTree.root);
        return *this;
    }

    Binary<T>& operator=(const T& value) noexcept
    {   
        TreeBinary::deleteNodes(this->root);
        this->add(value);
        return *this;
    }

    Binary<T>& operator-=(const T& value) noexcept
    {
        this->discard(value);
        return *this;
    }

    Binary<T>& operator-=(const Binary<T>& binaryTree) noexcept
    {
        TreeBinary::popNodes(root, binaryTree.root);
        return *this;
    }

    Binary<T>& operator-=(std::initializer_list<T> ls) noexcept
    {
        for(T elem : ls)
            this->discard(elem);
        return *this;
    }

    bool operator==(const Binary<T>& binaryTree) noexcept
    {
        return TreeBinary::nodesEqualAboutValue(binaryTree.root, this->root);
    }

    bool operator!=(const Binary<T>& binaryTree) noexcept
    {
        return !TreeBinary::nodesEqualAboutValue(binaryTree.root, this->root);
    }


    T operator[](Tree::t_index index)
    {
        Tree::Node<T> *tmp = TreeBinary::getNodeByMinValues(root, index);

        if(!tmp)
            throw "Пуст сетик";
        return tmp->data;
    }

    //После клонированные узлы надо самостоятельно почистить
    Tree::Node<T>* cloneNodes()
    {
        Tree::Node<T> *clone = nullptr;
        TreeBinary::insertNodes(clone, this->root);
        return clone;
    }
};

template<class T>
Tree::t_count height(const Binary<T>& binaryTree) noexcept 
{
    return binaryTree.elevation();
}

template<class T>
Tree::t_count len(const Binary<T>& binaryTree) noexcept
{
    return binaryTree.size();
}


template<class T>
Binary<T> operator+(const Binary<T>& binaryTree, const T& value) noexcept
{
    Binary<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

template<class T>
Binary<T> operator+(const T& value, const Binary<T>& binaryTree) noexcept
{
    Binary<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

template<class T>
Binary<T> operator+(const Binary<T>& binaryTree1, const Binary<T>& binaryTree2) noexcept
{
    Binary<T> sum(binaryTree1);
    sum += binaryTree1;
    sum += binaryTree2;
    sum.balance();
    return sum;
}

template<class T>
Binary<T> operator-(const Binary<T>& binaryTree, const T& value) noexcept
{
    Binary<T> sum(binaryTree);
    sum.discard(value);
    return sum;
}

template<class T>
Binary<T> operator-(const Binary<T>& binaryTree1, const Binary<T>& binaryTree2) noexcept
{
    Binary<T> sum(binaryTree1);
    sum -= binaryTree2;
    sum.balance();
    return sum;
}

}

#endif