#ifndef __HashTable_typeNode_Chain_Class__
#define __HashTable_typeNode_Chain_Class__

#include <string>

namespace HashTable
{

namespace typeNode
{
    namespace consts
    {
        using t_count = unsigned int;
    }   

template <class Tkey, class Tdata>
class Chain
{
    public:

    struct Node
    {
        Tkey key;
        Tdata data;
        Node *next;
        Node *prev;
        Node(const Tkey& key, const Tdata& data) : key(key), data(data), next(nullptr), prev(nullptr) {}
    };

    private:

    Node *head;
    consts::t_count _size;

    public:
    
    
    Chain() : head(nullptr), _size(0) {}

    consts::t_count size() const
    {
        return this->_size;
    }

    void clear()
    {
        while (head != nullptr)
        {
            Node *temp = head;
            head = head->next;
            delete temp;
        }

        head = nullptr;
    }

    ~Chain()
    {
        this->clear();
    }

    void insert(const Tkey& key, const Tdata& data)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                current->data = data;
                return;
            }
            current = current->next;
        }

        Node *newNode = new Node(key, data);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++this->_size;
    }

    bool add(const Tkey& key, const Tdata& data)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return false;
            }
            current = current->next;
        }

        Node *newNode = new Node(key, data);
        if (head == nullptr)
        {
            head = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
        ++this->_size;
        return true;
    }

    bool remove(const Tkey& key)
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                if (current->prev != nullptr) // Удаляем элемент из середины или конца списка
                {
                    current->prev->next = current->next;
                }
                if (current->next != nullptr) // Удаляем элемент из середины или начала списка
                {
                    current->next->prev = current->prev;
                }
                if (current == head) // Удаляем элемент из начала списка
                {
                    head = current->next;
                }
                delete current;
                --this->_size;
                return true;
            }
            current = current->next;
        }
        return false;
    }

    Node* getByKey(const Tkey& key) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return current;
            }
            current = current->next;
        }
        return nullptr; // Возвращаем nullptr, если элемент с указанным ключом не найден
    }

    bool contains(const Tkey& key) const
    {
        Node *current = head;
        while (current != nullptr)
        {
            if (current->key == key)
            {
                return true;
            }
            current = current->next;
        }
        return false;
    }

    class Iterator
    {
    private:
        Node *current;
    public:
        Iterator(Node *start) : current(start) {}
        
        // Перегрузка оператора * для получения данных текущего элемента
        Node &operator*() const { return *current; }
        
        // Перегрузка оператора ++ для перемещения итератора к следующему элементу
        Iterator &operator++()
        {
            if (current != nullptr)
                current = current->next;
            return *this;
        }

        // Перегрузка оператора != для проверки на неравенство двух итераторов
        bool operator!=(const Iterator &other) const
        {
            return current != other.current;
        }
    };

    Iterator begin() const { return Iterator(head); }
    Iterator end() const { return Iterator(nullptr); }


    std::string toString() const;
};

    template <>
    std::string Chain<std::string, std::string>::toString() const
    {
        std::string result;

        result += "Chain: {\n";

        for (auto iter = begin(); iter != end(); ++iter)
        {
            const Node& item = *iter;
            result += "\tkey:" + item.key + ", data:" + item.data + ";\n";
        }

        result += "};";
        return result;
    }

    template <class Tkey, class Tdata>
    std::string Chain<Tkey, Tdata>::toString() const
    {
        std::string result;

        result += "Chain: {\n";

        for (auto iter = begin(); iter != end(); ++iter)
        {
            const Node& item = *iter;
            result += "\tkey:" + std::to_string(item.key) + ", data:" + std::to_string(item.data) + ",\n";
        }

        result += "};";
        return result;
    }

}
}

#endif
