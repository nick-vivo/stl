#ifndef __Tree_Binary_Class__
#define __Tree_Binary_Class__
/**
 * @file src/Tree/TreeBinary.cc, lib - Tree.
 * 
 * @brief Бинарное дерево поиска
 * 
 * Файл с бинарным деревом поиска и функиями для работы с бинарными
 * узлами поиска.
 * 
 * @warning
 * Используемые стандартные библиотеки:
 * 1.#incldue <initializer_list>;
 */

#include "Node.cc"
#include "Tools.cc"
#include <initializer_list>


/**
* @brief Содержит функции для работы с узлами, построенными по бинарному дереву.
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
    * после надо удалить с помощью функций очистки). Если 
    * nodeForIntersection = nullptr, то структура nodeFromWhichToCopy 
    * будет в nodeForIntersection.
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
    * nodeFromDelete. В результате в узле nodeForInsertion не будут присутствовать
    * значения из nodeFromWhichToCopy. (присходит очистка памяти, удалённые
    * узлы = nullptr).
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
    * в nodeValues.
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
    * @brief Удаление узла целиком из памяти.
    * 
    * Функция рекурсивно удаляет элементы из памяти и заменяет node на
    * nullptr(присходит очистка памяти, удалённые узлы = nullptr)
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node Ссылка на узел для очистки.
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
    
    /**
    * @brief Определение высоты дерева
    * 
    * Функция рекурсивно вычисляет высоту дерева(насколько далеко от корня
    * находится самое нижнее значение)
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел
    * 
    * @return Высота узла.
    */
    template<class T>
    Tree::t_count height(const Tree::Node<T>* const node) noexcept 
    {
        if(node)
            return 1 + Tools::max(height(node->left), height(node->right));
        return 0;

    }

    /**
    * @brief Вычисление количества значений в корне.
    * 
    * Функция рекурсивно вычисляет количество значений в корне.
    * 
    * Пример: Значения узла Node: {1, 2, 3} -> 3;
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел.
    * 
    * @return Количество значений в узле.
    */
    template<class T>
    Tree::t_count len(const Tree::Node<T>* const node) noexcept
    {
        if (node)
            return len(node->right) + len(node->left) + 1;
        else 
            return 0;
    }

    /**
    * @brief Проверяет есть ли значение в корне или узлах, подузлах дерева.
    * 
    * Функция рекурсивно проверяет наличие значения value в узле root.
    * 
    * Пример: Значения узла Node: {1, 2, 3, 4, 5, 6}; value: 3 -> true;
    * 
    * Пример: Значения узла Node: {1, 2, 3}; value: 4 -> false;
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param root указатель на узел.
    * @param value значение поиска.
    * 
    * @return true если значение в узлах root, false если его нету в узлах root.
    */
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


    /**
    * @brief Проверяет сбалансирован ли корень(если разница высот между левым
    * узлом > 1, то дерево не сбаласировано. И так для всех узлов)
    * 
    * Если абсолютная разница высот между левым и правым узлом > 1, то дерево не
    * сбаласировано. Итак для всех узлов. Подробнее читай деревья AVL.
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param root указатель на узел.
    * 
    * @return true если дерево сбалансировано, false в противном случае.
    */
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

    /**
    * @brief Посмотреть баланс фактор для узла.
    * 
    * Если высота правого дерева больше левого, то значение будет положительным,
    * это значит, что высота правого дерева больше левого на возвращаемое значение.
    * 
    * Если высота левого дерева больше правого, то значение будет отрицательным,
    * это значит, что высота левого дерева больше левого на возвращаемое значение.
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param root указатель на узел.
    * 
    * @return Разница между высотой правого и левого дерева. 
    */
    template<class T>
    Tree::t_index checkBalanceFactor(const Tree::Node<T>* const root)
    {
        if(root)
            return height(root->right) - height(root->left);
        
        return 0;
    }

//Переброс левого витка на право

    /**
    * @brief Перемещение левого витка на верх.
    * 
    * Функция перемещает правое значение узла вверх заменяя node, а node
    * перемещается влево вниз. После node->правое->левое перебрасывает в
    * node->левое->правое.
    * 
    *                    5
    *                 4{
    *                /   3
    * Пример: Было: 2    
    *                \
    *                 1
    * 
    * 
    *              
    *                  5
    *                 /   
    * Пример: Стало: 4     
    *                 \   3
    *                  2{
    *                    1
    * 
    * @throws Если node пуст или пуст правый узел, так как в таком случае
    * невозможно совершить поворот влево
    *                  
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param root указатель на узел.
    * 
    * @return void. 
    */
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

    /**
    * @brief Перемещение правого витка на верх.
    * 
    * Функция перемещает левое значение узла вверх заменяя node, а node
    * перемещается влево вниз. После node->левое->правое перебрасывает в
    * node->правое->левое.
    * 
    *                  5
    *                 /   
    * Пример: Было: 4     
    *                 \   3
    *                  2{
    *                    1
    * 
    * 
    * 
    *                    5
    *                 4{
    *                /   3
    * Пример: Стало: 2    
    *                \
    *                 1
    * 
    *              
    * 
    * @throws Если node пуст или пуст левый узел, так как в таком случае
    * невозможно совершить поворот влево
    *                  
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param root указатель на узел.
    * 
    * @return void. 
    */
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


    /**
    * @brief Балансировка узла -> превращение его в AVL.
    * 
    * Функция переводит узел в узел AVL, в котором разница высот в каждом узле
    * между левым и правым < 2.
    *
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел.
    * 
    * @return void. 
    */
    template<class T>
    void balanceToAVL(Tree::Node<T>*& node)
    {
        if(!node)
            return;
            
        balanceToAVL(node->right);
        balanceToAVL(node->left);

        Tree::t_index balanceFactor = checkBalanceFactor(node);

        if (balanceFactor > 1)
        {
            if(checkBalanceFactor(node->right) < 0)
                rightRotate(node->right);
            leftRotate(node);

            if(balanceFactor  > 3)
                balanceToAVL(node->left);
        }
        else if (balanceFactor < -1)
        {
            if (checkBalanceFactor(node->left) > 0)
                leftRotate(node->left);
            rightRotate(node);
            
            if(balanceFactor < -3)
                balanceToAVL(node->right);
        }
        else if(balanceFactor  > 3)
            balanceToAVL(node->left);
        else if(balanceFactor < -3)
                balanceToAVL(node->right);

    }
    
// Обход по дереву

    /**
    * @brief Получение узла по индексу в линейном обходе.
    * 
    * Функция получает узел по индексу, начиная с верха дерева, проходя сначала
    * с лева, а потом вправо. Если индекс больше или равен количеству значений
    * в узле, то вернём nullptr. Если index < 0, то обход будет справа.
    *
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел.
    * @param index индекс для получения узла.
    * 
    * @return указатель на узел по индексу.
    */
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

    /**
    * @brief Получение узла по индексу в обходе(помощник).
    * 
    * Функция получает узел по индексу, начиная с минимального значения. count
    * это смещение относительно нуля. Этот параметр надо настраивать для получения
    * правильного значения. Эмпирическим путём было выяснено, чтобы получить по
    * индексу 0 минимальное значени, изначально count нужно указывать -1. Также 
    * доступна и отрицательная индексация, но индекс не должен превышать количество 
    * элементов в узле, иначе получим nullptr
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел.
    * @param count параметр смещения
    * @param index индекс для получения узла.
    * 
    * @return указатель на узел по индексу.
    */
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

    /**
    * @brief Получение узла по индексу в обходе начиная с минимального значения.
    * 
    * Читай функцию getNodeByIndexHelper(). Для этой функции подобрано значение count
    * 
    * @tparam T Тип поля data узлов.
    * 
    * @param node указатель на узел.
    * @param index индекс для получения узла.
    * 
    * @return указатель на узел. 
    */
    template<class T>
    Tree::Node<T>* getNodeByMinValues(Tree::Node<T>* const root, int index) 
    {
        int count;
        index >= 0 ? count = -1 : count = 0;
        return getNodeByIndexHelper(root, count, index);
    }
}

/**
 * @brief - Содержит класс бинарного дерева, класс узлов Node, а также функции вывода 
 * деревьев, если подключили библиотеку Tree
 */
namespace Tree
{

/**
 * @class Binary
 * 
 * @brief Бинарное дерево поиска. 
 * 
 * Его преимущество заключается в быстром поиске и получении значений - log(N). 
 * 
 * Все методы, операторы, конструкторы и деструкторы используют функционал 
 * функций из TreeBinary.
 * 
 * @warning
 * Нужны стандартные библиотеки:
 * 1.#include <initializer_list>
 *
 * @tparam T тип данных для контейнера.
 */
template<class T>
class Binary
{
private:
    Tree::Node<T> *root;

public:

    /**
     * @brief Конструктор по умолчанию.
     * 
     * Дерево пустое.
     * 
     * @tparam T тип значений дерева.
     */
    Binary(): root(nullptr) {}

    /**
     * @brief Конструктор принимающий контейнер вида <int>{1, 2, 3};
     * 
     * Все значения из {} будут в дереве
     * 
     * @warning
     * Нужны стандартные библиотеки:
     * #include <initializer_list>
     * 
     * @tparam T тип значений дерева.
     * 
     * @param ls std::initializer_list<T>. Из стандартной библиотеки
     */
    Binary(std::initializer_list<T> ls): Binary()
    {
        for(T elem : ls)
            this->add(elem);
    }

    /**
     * @brief Конструктор принимающий одно значение, которое станет корнем дерева.
     * 
     * @tparam T тип значений поле data.
     * 
     * @param value : T
     */
    Binary(const T& value): Binary() 
    {
        this->root = new Tree::Node<T>(value);
    }

    /**
     * @brief Конструктор принимающий узел из класса Tree::Node<T>.
     * 
     * Конструктор копирует значения из узла, а не перемещает указатель,
     * так как узел может быть ошибочно бинарным деревом(см. функцию 
     * TreeBinary::insertNodes)
     * 
     * @tparam T тип значений дерева.
     * 
     * @param node узел значений.
     */
    Binary(const Tree::Node<T>* const node): Binary() 
    {
        TreeBinary::insertNodes(root, node);
    }

    /**
     * @brief Конструктор копирования.
     * 
     * Конструктор копирует значения из дерева other и создаёт новое дерево.
     * (см. функцию TreeBinary::insertNodes)
     * 
     * @tparam T тип значений дерева.
     * 
     * @param other дерево значения для копирования.
     */
    Binary(const Binary<T>& other): Binary()
    {
        TreeBinary::insertNodes(root, other.root);
    }

    /**
     * @brief Конструктор перемещения.
     * 
     * Конструктор для ключевого слова return. Чтобы не создавать новое дерево
     * с помощью конструктора копирования, а переместить указатель.
     * 
     * @tparam T тип значений дерева.
     * 
     * @param other дерево для перемещения указателя.
     */
    Binary(Binary<T>&& other): Binary()
    {
        this->swap(other);  
    }

    /**
     * @brief Деструктор.
     * 
     * Очищает память от дерева рекурсивным методом(см. функцию TreeBinary::deleteNodes).
     */
    ~Binary()
    {
        TreeBinary::deleteNodes(root);        
    }
    
    /**
    * @brief Добавление значения в дерево.
    * 
    * Функция рекурсивно проходится по узлам и вставляет значение в зависимости
    * от параметра value.(выделяется память)(см. функцию TreeBinary::insert).
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @param value Значение для вставки.
    *
    *  @return void.
    */
    void add(const T &value) noexcept
    {
        TreeBinary::insert(this->root, value);
    }
    
    /**
    * @brief Удаление значения из дерева.
    * 
    * Функция рекурсивно проходится по элементам и удаляет нужный, меняя только
    * два значения в структуре дерева(само значение и максимальное из левого
    * подузла), то есть структура дерева не страдает.(присходит очистка памяти)
    * (см. функцию TreeBinary::removeValueWithoutChangeNodes).
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @param value Значение которое нужно удалить.
    * 
    * @return void.
    */
    void discard(const T &value) noexcept
    {
        TreeBinary::removeValueWithoutChangeNodes(this->root, value);
    }

    /**
    * @brief Определение высоты дерева.
    * 
    * Функция рекурсивно вычисляет высоту дерева(насколько далеко от корня
    * находится самое нижнее значение)(см. функцию TreeBinary::height)
    * 
    * @return Высота дерева.
    */
    Tree::t_count elevation() const noexcept
    {
        return TreeBinary::height(this->root);
    }

    /**
    * @brief Вычисление количества значений в корне.
    * 
    * Функция рекурсивно вычисляет количество значений в корне.
    * (см. функцию TreeBinary::len)
    * Пример: Дерево Tree: {1, 2, 3} -> 3;
    * 
    * 
    * @return Количество значений в узле.
    */
    Tree::t_count size() const noexcept
    {
        return TreeBinary::len(this->root);
    }

    /**
    * @brief Проверяет есть ли значение в дереве.
    * 
    * Функция рекурсивно проверяет наличие значения value в дереве.
    * 
    * Пример: Значения узла Node: {1, 2, 3, 4, 5, 6}; value: 3 -> true;
    * 
    * Пример: Значения узла Node: {1, 2, 3}; value: 4 -> false;
    * 
    * (см. функцию TreeBinary::valueInNodes)
    * 
    * @param value значение поиска.
    * 
    * @return true если значение в дереве, false если его нету в дереве.
    */
    bool in(const T &value) const noexcept
    {
        return TreeBinary::valueInNodes(this->root, value);
    }


//Балансировка дерева
    /**
    * @brief Балансировка дерева -> превращение его в AVL.
    * 
    * Функция переводит дерево в AVL, в котором разница высот в каждом узле
    * между левым и правым < 2.(см. функцию TreeBinary::balanceToAVL)
    *
    * @return void. 
    */
    void balance() noexcept
    {
        TreeBinary::balanceToAVL(this->root);
    }

    /**
    * @brief Проверяет сбалансировано ли дерево(если разница высот между левым
    * узлом > 1, то дерево не сбаласировано. И так для всех узлов)(см. функцию
    * TreeBinary::isBalanced)
    * 
    * Если абсолютная разница высот между левым и правым узлом > 1, то дерево не
    * сбаласировано. Итак для всех узлов. Подробнее читай деревья AVL.
    * 
    * @return true если дерево сбалансировано, false в противном случае.
    */
    bool isBalanced() const noexcept
    {
        return TreeBinary::isBalanced(this->root);
    }


//Основной функционал закончился.
    
    /**
    * @brief Меняет местами два дерева.
    * 
    * Функция меняет местами указатели на деревья.
    * 
    * Пример: a = 3, b = 2; -> a = 2, b = 3;
    * 
    * @param binaryTree дерево для замены
    * 
    * @return void.
    */
    void swap(Binary<T> binaryTree) noexcept
    {
        Tools::swap(this->root, binaryTree.root);
    }

    /**
    * @brief Добавление значения в дерево.
    * 
    * Оператор рекурсивно проходится по узлам и вставляет значение в зависимости
    * от параметра value.(выделяется память)(см. функцию TreeBinary::insert).
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @param value Значение для вставки.
    *
    *  @return Наше дерево.
    */
    Binary<T>& operator+=(const T& value) noexcept
    {
        this->add(value);
        return *this;
    }

    /**
    * @brief Вставка значений из одного дерева в другое.
    * 
    * Оператор рекурсивно вставляет элементы из binaryTree в
    * наше дерево. В результате в нашем дереве будут
    * присутствовать значения из binaryTree. Если 
    * nodeForIntersection = nullptr, то структура nodeFromWhichToCopy 
    * сохранится
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @param binaryTree дерево для вставки.
    * 
    * @return Наше дерево.
    */
    Binary<T>& operator+=(const Binary<T>& binaryTree) noexcept
    {
        TreeBinary::insertNodes(root, binaryTree.root);
        return *this;
    }

    /**
    * @brief Из нашего дерева делает binaryTree, сохраняя структуру binaryTree.
    * 
    * @param binaryTree дерево для копирования.
    * 
    * @return Наше дерево.
    */
    Binary<T>& operator=(const Binary<T>& binaryTree) noexcept
    {   
        TreeBinary::deleteNodes(this->root);
        TreeBinary::insertNodes(this->root, binaryTree.root);
        return *this;
    }

    /**
    * @brief Из нашего дерева делает дерево с корнем value, удавил предварительно
    * вспе значения
    * 
    * @param  value значения для корня.
    * 
    * @return Наше дерево.
    */
    Binary<T>& operator=(const T& value) noexcept
    {   
        TreeBinary::deleteNodes(this->root);
        this->add(value);
        return *this;
    }

    /**
    * @brief Удаление значения из дерева.
    * 
    * Оператор рекурсивно проходится по элементам и удаляет нужный, меняя только
    * два значения в структуре дерева(само значение и максимальное из левого
    * подузла), то есть структура дерева не страдает.(присходит очистка памяти)
    * (см. функцию TreeBinary::removeValueWithoutChangeNodes).
    * 
    * # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
    * 
    * @param value Значение которое нужно удалить.
    * 
    * @return Наше дерево.
    */
    Binary<T>& operator-=(const T& value) noexcept
    {
        this->discard(value);
        return *this;
    }

     /**
    * @brief Удаление значений из одного дерева, взяв значения для удаления из другого.
    * 
    * Функция рекурсивно удаляет элементы binaryTree из нашего дерева.
    * В результате в нашем не будут присутствовать значения из binaryTree.
    * (см. функцию TreeBinary::popNodes)
    * 
    * @param binaryTree дерево значений.
    * 
    * @return Наше дерево.
    */
    Binary<T>& operator-=(const Binary<T>& binaryTree) noexcept
    {
        TreeBinary::popNodes(root, binaryTree.root);
        return *this;
    }

    /**
    * @brief Равны ли деревья по значениям.
    * 
    * Функция рекурсивно проверяет все ли значения из node<1,2>находятся в
    * node<2,1>. (см. функцию TreeBinary::nodesEqualAboutValue)
    * 
    * @param binaryTree Дерево для проверки.
    * 
    * @return true если их значения равны. false если значения разные.
    */
    bool operator==(const Binary<T>& binaryTree) noexcept
    {
        return TreeBinary::nodesEqualAboutValue(binaryTree.root, this->root);
    }

    /**
    * @brief Равны ли деревья по значениям.
    * 
    * Функция рекурсивно проверяет все ли значения из node<1,2>находятся в
    * node<2,1>.(см. функцию TreeBinary::nodesEqualAboutValue)
    * 
    * @param binaryTree Дерево для проверки.
    * 
    * @return false если их значения равны. true если значения разные.
    */
    bool operator!=(const Binary<T>& binaryTree) noexcept
    {
        return !TreeBinary::nodesEqualAboutValue(binaryTree.root, this->root);
    }

    /**
    * @brief Получение узла по индексу в обходе начиная с минимального значения.
    * 
    * Читай функцию TreeBinary::getNodeByMinValues.
    * 
    * @param index индекс для получения значения.
    * 
    * @return Значение узла по индексу.
    */
    T operator[](Tree::t_index index)
    {
        Tree::Node<T> *tmp = TreeBinary::getNodeByMinValues(root, index);

        if(!tmp)
            throw "Пуст сетик";
        return tmp->data;
    }

    /**
    * @brief Получение копии дерева в формате узлов. 
    * 
    * После требуется их удалить с помощью функции TreeBinary::deleteNodes,
    * иначе память не очистится
    * 
    * @return Копия дерева в узлах.
    */
    Tree::Node<T>* cloneNodes()
    {
        Tree::Node<T> *clone = nullptr;
        TreeBinary::insertNodes(clone, this->root);
        return clone;
    }
};

/**
* @brief Определение высоты дерева.
* 
* Функция рекурсивно вычисляет высоту дерева(насколько далеко от корня
* находится самое нижнее значение)
* 
* @tparam T Тип поля data узлов.
* 
* @param binaryTree Бинарное дерево.
* 
* @return Высота дерева.
*/
template<class T>
Tree::t_count height(const Binary<T>& binaryTree) noexcept 
{
    return binaryTree.elevation();
}

/**
* @brief Вычисление количества значений в дереве.
* 
* Функция рекурсивно вычисляет количество значений в дереве.
* 
* Пример: Значения узла Node: {1, 2, 3} -> 3;
* 
* @tparam T Тип поля data узлов.
* 
* @param binaryTree Бинарное дерево.
* 
* @return Количество значений в узле.
*/
template<class T>
Tree::t_count len(const Binary<T>& binaryTree) noexcept
{
    return binaryTree.size();
}


/**
* @brief Добавление значения в новое дерево и его возврат.
* 
* Оператор рекурсивно проходится по дереву и вставляет значение в копию в зависимости
* от параметра value.(выделяется память)(см. функцию TreeBinary::insert и конструктор копирования).
* 
* # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
* 
* @param value Значение для вставки.
* @param binaryTree дерево для копирования
* 
* @return Новое дерево.
*/
template<class T>
Binary<T> operator+(const Binary<T>& binaryTree, const T& value) noexcept
{
    Binary<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

/**
* @brief Добавление значения в новое дерево и его возврат.
* 
* Оператор рекурсивно проходится по дереву и вставляет значение в копию в зависимости
* от параметра value. Структура созраняется(выделяется память)(см. функцию 
* TreeBinary::insert и конструктор копирования).
* 
* # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
* 
* @param value Значение для вставки.
* @param binaryTree дерево для копирования
*
* @return Новое дерево.
*/
template<class T>
Binary<T> operator+(const T& value, const Binary<T>& binaryTree) noexcept
{
    Binary<T> sum(binaryTree);
    sum.add(value);
    return sum;
}

/**
* @brief Создание копии дерева на основе их суммы.
* 
* Оператор рекурсивно проходится по деревьям и вставляет значения в копию. Также
* отбалансирует итоговое дерево.
* 
* # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
* 
* @param binaeryTree1 первое дерево.
* @param binaryTree2 второе дерево
*
* @return Новое дерево.
*/
template<class T>
Binary<T> operator+(const Binary<T>& binaryTree1, const Binary<T>& binaryTree2) noexcept
{
    Binary<T> sum(binaryTree1);
    sum += binaryTree1;
    sum += binaryTree2;
    sum.balance();
    return sum;
}


/**
* @brief Удаление значения из нового дерева и его возврат.
* 
* Оператор рекурсивно проходится по дереву и удаляет значение из копии 
* основанного на старом дереве.(выделяется память)(см. функцию 
* Binary::discard и конструктор копирования).
* 
* # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
* 
* @param value Значение для вставки.
* @param binaryTree дерево для копирования
* 
* @return Новое дерево.
*/
template<class T>
Binary<T> operator-(const Binary<T>& binaryTree, const T& value) noexcept
{
    Binary<T> sum(binaryTree);
    sum.discard(value);
    return sum;
}

/**
* @brief Удаление значений из нового дерева и его возврат.
* 
* Оператор рекурсивно проходится по дереву и удаляет значения из копии 
* основанного на первом дереве.(выделяется память)(см. функцию 
* Binary::discard и конструктор копирования).
* 
* # Рекурсия: Значение больше - идём вправо, меньше - идём влево.
* 
* @param binaeryTree1 первое дерево.
* @param binaryTree2 второе дерево
* 
* @return Новое дерево.
*/
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