#ifndef __Tree_Node_Class__
#define __Tree_Node_Class__
/**
 * @file src/Tree/Node, lib - Tree.
 * 
 * @brief Файл с классом бинарного узла для различных деревьев.
 * 
 * Файл содержит класс Node с двумя подузлами и полем data, для того, чтобы
 * различные деревья могли их использовать.
 */



/**
 * @brief - Содержит класс бинарного дерева, класс узлов Node, а также функции вывода 
 * деревьев, если подключили библиотеку Tree
 */
namespace Tree
{

/**
 * @class Node
 * 
 * @brief Класс служит узлами различных двоичных деревьев(бинарных).
 * 
 * Это стандартный узел с правым и левым подузлами
 * 
 * @tparam T тип данных и типы указателей на правый и левый узел.
 */
template<class T>
class Node
{
public:
    Node<T> *left;
    Node<T> *right;
    T data;

    /**
     * @brief Конструктор с параметрами для MyClass.
     * 
     * @tparam T тип значений поле data.
     * 
     * @param data: T поле данные класса.
     * @param left: Node<T> левый узел цепи.
     * @param right: Node<T> правый узел цепи.
     */
    explicit Node(const T &data, Node<T> *left = nullptr, Node<T> *right = nullptr): data(data), left(left), right(right) {}
};
}

#endif