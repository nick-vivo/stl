#ifndef __HashTable_ChainMethodBase_Interface__
#define __HashTable_ChainMethodBase_Interface__

#include <string>

#include "HashTableInterface.cc"
#include "typeNode/Chain.cc"

namespace HashTable
{
    template <class Tkey, class Tdata>
    class ChainMethodBase : public HashTableInterface<Tkey, Tdata>
    {
    public:
        void clear() noexcept override
        {
            if (table)
            {
                delete[] table;

                table = nullptr;
            }
        }

        std::string toString() const override;

    protected:

        HashTable::typeNode::Chain<Tkey, Tdata> *table;
        
        ChainMethodBase(const consts::t_uIndex &capacity, const consts::t_stat loadFactorMin, const consts::t_stat loadFactorMax) : HashTableInterface<Tkey, Tdata>(capacity, loadFactorMin, loadFactorMax), table(nullptr)
        {
            if (this->capacity())
            {
                table = new typeNode::Chain<Tkey, Tdata>[this->capacity()];
            }
        }

        bool insert(const consts::t_uIndex &hashIndex, const Tkey &key, const Tdata &data) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            if(table[hashIndex].size() == 0)
                ++this->_size;

            table[hashIndex].insert(key, data);
            return true;
        }

        bool erase(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            return table[hashIndex].remove(key);
        }

        bool add(const consts::t_uIndex &hashIndex, const Tkey &key, const Tdata &data) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            if(table[hashIndex].size() == 0)
                ++this->_size;

            return table[hashIndex].add(key, data);
        }

        bool remove(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            return table[hashIndex].remove(key);
        }

        typename typeNode::Chain<Tkey, Tdata>::Node* search(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(hashIndex >= this->capacity()) return nullptr;

            return table[hashIndex].getByKey(key);
        }

        virtual ~ChainMethodBase()
        {
            this->clear();
        }
    };

    template <class Tkey, class Tdata>
    std::string ChainMethodBase<Tkey, Tdata>::toString() const
    {
        std::string result;

        result += "ChainMethodTable: {\n\n";

        if (table)
        {
            for (consts::t_uIndex i = 0; i < this->capacity(); ++i)
            {
                    result += std::to_string(i) + "." + table[i].toString() + "\n\n";
            }
        }

        result += "\n};";
        return result;
    }
}

#endif