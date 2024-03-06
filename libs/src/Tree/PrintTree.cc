#ifndef __Tree_PrintTree_Module__
#define __Tree_PrintTree_Module__
/**
 * @file src/Tree/PrintTree.cc, lib - Tree.
 * 
 * @brief Файл с различными функциями для вывода деревьев.
 * 
 * Файл содержит функции для вывода и просмотра содержимого деревьев, используя
 * стандартные потоки вывода
 * 
 * Используемые стандартные библиотеки:
 * 1.#incldue <iostream>;
 */

#include <iostream>
#include "TreeBinary.cc"
#include "Node.cc"
#include "Tools.cc"



/**
 * @brief - Содержит класс бинарного дерева, класс узлов Node, а также функции вывода 
 * деревьев, если подключили библиотеку Tree
 */
namespace Tree
{
    
    /**
    * @brief Выводит в поток корень дерева узлов node.
    * 
    * Функция выводит в поток корень дерева узлов node и все его подузлы,
    * начиная с самого левого.
    * 
    * Пример: Nodes: {1, 2, 3};
    * 
    * # Используется рекурсия вида: сначала левые значения, потом правые.
    * 
    * @tparam T тип поля данных узлов.
    * 
    * @param node Указатель на корень узлов для вывода.
    * @param stream Поток вывода из библиотеки iostream. По умолчанию std::cout.
    * @param name Параметр для функции по умолчанию. Нужен для вывода слова Nodes.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T>
    std::ostream& print(const Tree::Node<T>* node, std::ostream& stream = std::cout, bool name = true) noexcept
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

    /**
    * @brief Выводит в поток корень дерева и его узлов.
    * 
    * Функция нужна скорее для наглядности узлов. Чтобы в поток красиво
    * отобразить корень и все его узлы и подузлы.
    *
    * # Используется рекурсия вида: сначала левые значения, потом правые.
    *
    * @tparam T тип поля данных узлов.
    * 
    * @param root Указатель на корень узлов для вывода.
    * @param stream Поток вывода из библиотеки iostream. По умолчанию std::cout.
    * @param space Первый отступ от левого края потока вывода. По умолчанию 1.
    * @param plus Отступы для подузлов. Чем больше отступ, тем дальше они будут 
    * находится друг от друга. По умолчанию стоит 4.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T>
    std::ostream& printTree(Tree::Node<T>* root, std::ostream& stream = std::cout, Tree::t_index space = 1, Tree::t_index plus = 4) noexcept
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

    /**
    * @brief Выводит в поток дерево.
    * 
    * Функция нужна скорее для наглядности узлов. Чтобы в поток красиво
    * отобразить корень и все его подузлы.
    * 
    * # Используется рекурсия вида: сначала левые значения, потом правые.
    *
    * @tparam T тип поля данных узлов.
    * 
    * @param tree Дерево.
    * 
    * @param stream Поток вывода из библиотеки iostream. По умолчанию std::cout.
    * @param space Первый отступ от левого края потока вывода. По умолчанию 1.
    * @param plus Отступы для подузлов. Чем больше отступ, тем дальше они будут
    * находится друг от друга. По умолчанию стоит 4.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T>
    std::ostream& printTree(Tree::Binary<T>& tree, std::ostream& stream = std::cout, Tree::t_index space = 1, Tree::t_index plus = 4) noexcept
    {
        Node<T>* clone = tree.cloneNodes();

        printTree(clone, stream, space, plus);

        TreeBinary::deleteNodes(clone);

        return stream;
    }

    /**
    * @brief Выводит в поток дерево целиком.
    * 
    * Функция выводит в поток корень дерева, узлы и все его подузлы, начиная с
    * самого левого.
    * 
    * Пример: Tree: {1, 2, 3};
    * 
    * # Используется рекурсия вида: сначала левые значения, потом правые.
    * 
    * @tparam T Тип данных для дерева поиска.
    * 
    * @param tree Дерево поиска(бинарное).
    * @param stream Поток вывода из библиотеки iostream. По умолчанию std::cout.
    * @param name Параметр для функции по умолчанию. Нужен для вывода слова Nodes.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T>
    std::ostream& print(Tree::Binary<T>& tree, std::ostream& stream = std::cout)  noexcept
    {

        stream << "Tree: {";
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