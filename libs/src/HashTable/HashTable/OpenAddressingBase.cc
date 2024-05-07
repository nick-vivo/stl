#ifndef __HashTable_OpenAddressingBase_Interface__
#define __HashTable_OpenAddressingBase_Interface__

#include <string>

#include "HashTableInterface.cc"
#include "typeNode/OpenAddressing.cc"

namespace HashTable
{
    template <class Tkey, class Tdata>
    class OpenAddressingBase : public HashTableInterface<Tkey, Tdata>
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
        HashTable::typeNode::OpenAddressing<Tkey, Tdata> *table;

        OpenAddressingBase(const consts::t_uIndex &capacity, const consts::t_stat loadFactorMin, const consts::t_stat loadFactorMax) : HashTableInterface<Tkey, Tdata>(capacity, loadFactorMin, loadFactorMax), table(nullptr)
        {
            if (this->capacity())
            {
                table = new typeNode::OpenAddressing<Tkey, Tdata>[this->capacity()];
            }
        }

        bool insert(const consts::t_uIndex &hashIndex, const Tkey &key, const Tdata &data) noexcept
        {
            if(hashIndex >= this->capacity()) return false;
            
            bool searchNotOccuped = true, notSearchFirstFreeKey = true;
            consts::t_uIndex safeIteratorIndex;
            consts::t_uIndex iteratorIndex = hashIndex;

            do
            {
                if (searchNotOccuped && table[iteratorIndex].nullKey() && table[iteratorIndex].getOccuped())
                {
                    searchNotOccuped = false;
                }

                if (searchNotOccuped && table[iteratorIndex].nullKey())
                {
                    if (this->size() == this->capacity() || !table)
                        return false;

                    table[iteratorIndex].set(key, data);
                    table[iteratorIndex].setOccuped(true);
                    ++this->_size;

                    return true;
                }

                if (table[iteratorIndex].equalKey(key))
                {
                    table[iteratorIndex].setData(data);
                    return true;
                }

                if (notSearchFirstFreeKey && table[iteratorIndex].nullKey())
                {
                    safeIteratorIndex = iteratorIndex;
                    notSearchFirstFreeKey = false;
                }

                iteratorIndex = (iteratorIndex + 1) % this->capacity();

            } while (iteratorIndex != hashIndex);

            if (this->size() == this->capacity() || !table)
                return false;

            table[safeIteratorIndex].set(key, data);
            ++this->_size;

            return true;
        }

        bool erase(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            consts::t_uIndex iteratorIndex = hashIndex;

            do
            {
                if (!table[iteratorIndex].getOccuped())
                    return false;

                if (table[iteratorIndex].equalKey(key))
                {
                    table[iteratorIndex].clear();
                    --this->_size;
                    return true;
                }

                iteratorIndex = (iteratorIndex + 1) % this->capacity();

            } while (iteratorIndex != hashIndex);

            return false;
        }

        bool add(const consts::t_uIndex &hashIndex, const Tkey &key, const Tdata &data) noexcept
        {
            if(hashIndex >= this->capacity()) return false;

            consts::t_uIndex iteratorIndex = hashIndex;
            bool searchNotOccuped = true, notSearchFirstFreeKey = true;
            consts::t_uIndex safeIteratorIndex;

            do
            {
                if (searchNotOccuped && table[iteratorIndex].nullKey() && table[iteratorIndex].getOccuped())
                {
                    searchNotOccuped = false;
                }

                if (searchNotOccuped && table[iteratorIndex].nullKey())
                {

                    table[iteratorIndex].set(key, data);
                    table[iteratorIndex].setOccuped(true);
                    ++this->_size;

                    if (!this->goodLoadFactor())
                        this->reCapacity();

                    return true;
                }

                if (table[iteratorIndex].equalKey(key))
                {
                    return false;
                }

                if (notSearchFirstFreeKey && table[iteratorIndex].nullKey())
                {
                    safeIteratorIndex = iteratorIndex;
                    notSearchFirstFreeKey = false;
                }

                iteratorIndex = (iteratorIndex + 1) % this->capacity();

            } while (iteratorIndex != hashIndex);

            table[safeIteratorIndex].set(key, data);
            ++this->_size;

            if (!this->goodLoadFactor())
                this->reCapacity();

            return true;
        }

        bool remove(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(!this->table || hashIndex >= this->capacity()) return false;

            consts::t_uIndex iteratorIndex = hashIndex;

            do
            {
                if (!table[iteratorIndex].getOccuped())
                    return false;

                if (table[iteratorIndex].equalKey(key))
                {
                    table[iteratorIndex].clear();
                    --this->_size;
                    if (!this->goodLoadFactor())
                        this->reCapacity();
                    return true;
                }

                iteratorIndex = (iteratorIndex + 1) % this->capacity();

            } while (iteratorIndex != hashIndex);

            return false;
        }

        Tdata *search(const consts::t_uIndex &hashIndex, const Tkey &key) noexcept
        {
            if(!this->table || hashIndex >= this->capacity()) return nullptr;
            
            consts::t_uIndex iteratorIndex = hashIndex;

            do
            {
                if (!table[iteratorIndex].getOccuped())
                    return nullptr;

                if (table[iteratorIndex].equalKey(key))
                {
                    return table[iteratorIndex].getData();
                }

                iteratorIndex = (iteratorIndex + 1) % this->capacity();

            } while (iteratorIndex != hashIndex);

            return nullptr;
        }

        virtual ~OpenAddressingBase()
        {
            this->clear();
        }
    };


    template <>
    std::string OpenAddressingBase<std::string, std::string>::toString() const
    {
        std::string result;

        result += "OpenAddressingTable: {\n";

        if (table)
        {
            for (consts::t_uIndex i = 0, j = 0; i < this->capacity(); ++i)
            {
                auto key = table[i].getKey();

                if (key)
                {
                    result += "\t" + *key;

                    result += " : ";

                    result += *table[i].getData();

                    if (j < this->size() - 1)
                    {
                        result += ",\n";
                        ++j;
                    }
                }
            }
        }

        result += "\n};";
        return result;
    }

    template <class Tkey, class Tdata>
    std::string OpenAddressingBase<Tkey, Tdata>::toString() const
    {
        std::string result;

        result += "OpenAddressingTable: {\n";

        if (table)
        {
            for (consts::t_uIndex i = 0, j = 0; i < this->capacity(); ++i)
            {
                auto key = table[i].getKey();

                if (key)
                {
                    result += "\t" + std::to_string(*key);

                    result += " : ";

                    result += std::to_string(*table[i].getData());

                    if (j < this->size() - 1)
                    {
                        result += ",\n";
                        ++j;
                    }
                }
            }
        }

        result += "\n};";
        return result;
    }
}

#endif