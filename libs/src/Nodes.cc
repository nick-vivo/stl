#ifndef __Tree_Nodes_Class__
#define __Tree_Nodes_Class__


namespace Tree
{
/**
 * @brief Node класс служит узлом для различных дереьвев
 */
template<class T>
class Node
{
public:
    Node<T> *left;
    Node<T> *right;
    T data;

    /**
     * Конструктор с параметрами для MyClass.
     * 
     * @param data: T поле данные класса.
     * @param left: Node<T> левый узел цепи.
     * @param right: Node<T> правый узел цепи.
     */
    // Node(const T &data, Node<T> *left = nullptr, Node<T> *right = nullptr): data(data), left(left), right(right) {}

    explicit Node(const T &data, Node<T> *left = nullptr, Node<T> *right = nullptr): data(data), left(left), right(right) {}
};
}

#endif