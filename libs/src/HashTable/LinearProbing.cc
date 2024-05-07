#ifndef __HashTable_LinearProbing_Class__
#define __HashTable_LinearProbing_Class__

#include "HashFunctions/FunctionModulus.cc"
#include "HashTable/OpenAddressingBase.cc"
#include "HashTable/typeNode/OpenAddressing.cc"

namespace HashTable
{

    template <class Tkey, class Tdata>
    class LinearProbing : public OpenAddressingBase<Tkey, Tdata>
    {
    private:
        HashFunctions::FunctionModulus<Tkey> hashFunction;
        
        consts::t_uIndex hash(const Tkey &key)
        {
            return this->hashFunction.hash(key);
        }

    public:
        LinearProbing(const consts::t_uIndex &capacity, const consts::t_stat loadFactorMin, const consts::t_stat loadFactorMax) : OpenAddressingBase<Tkey, Tdata>(capacity, loadFactorMin, loadFactorMax), hashFunction(HashFunctions::FunctionModulus<Tkey>(capacity)) {}

        LinearProbing(const consts::t_uIndex &capacity) : OpenAddressingBase<Tkey, Tdata>(capacity, consts::DEFAULT_LOAD_FACTOR_MIN, consts::DEFAULT_LOAD_FACTOR_MAX), hashFunction(HashFunctions::FunctionModulus<Tkey>(capacity)) {}

        LinearProbing() : OpenAddressingBase<Tkey, Tdata>(consts::DEFAULT_CAPACITY, consts::DEFAULT_LOAD_FACTOR_MIN, consts::DEFAULT_LOAD_FACTOR_MAX), hashFunction(HashFunctions::FunctionModulus<Tkey>(consts::DEFAULT_CAPACITY)) {}

        LinearProbing(const LinearProbing &other) : OpenAddressingBase<Tkey, Tdata>(other.capacity(), other.getLoadFactorMin(), other.getLoadFactorMax()), hashFunction(other.hashFunction)
        {
            for (consts::t_uIndex i = 0; i < other.capacity(); ++i)
            {
                auto key = other.table[i].getKey();

                if (key)
                    this->insert(*key, *other.table[i].getData());
            }
        }


        bool insert(const Tkey &key, const Tdata &data) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::insert(hashIndex, key, data);
        }

        bool erase(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::erase(hashIndex, key);
        }

        bool add(const Tkey &key, const Tdata &data) noexcept override
        {
            if (!this->goodLoadFactor())
                this->reCapacity();

            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::add(hashIndex, key, data);
        }

        bool remove(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::remove(hashIndex, key);
        }

        Tdata *search(const Tkey &key) noexcept
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::search(hashIndex, key);
        }

        bool containsKey(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return OpenAddressingBase<Tkey, Tdata>::search(hashIndex, key);
        }

        bool contains(const Tdata &data) const 
        {
            if(!this->table) return false;
            
            for (consts::t_uIndex i = 0, j = 0; i < this->capacity(); ++i)
            {
                auto ptr = this->table[i].getData();
                if(ptr && *ptr == data) return true;
            }
            return false;
        }

        bool reCapacity() noexcept override
        {
            consts::t_uIndex newCapacity;

            switch (this->loadFactorStatus())
            {
            case consts::LoadFactorStatus::ZERO_CAPACITY_AND_ZERO_SIZE:

                this->table = new typeNode::OpenAddressing<Tkey, Tdata>[consts::DEFAULT_CAPACITY];
                this->_capacity = consts::DEFAULT_CAPACITY;
                this->hashFunction.resize(consts::DEFAULT_CAPACITY);
                return true;

            case consts::LoadFactorStatus::GREATER_MAX:
                newCapacity = this->size() / this->getLoadFactorMin();
                break;

            case consts::LoadFactorStatus::LESS_MIN:
                newCapacity = this->size() / ((this->getLoadFactorMax() + this->getLoadFactorMin()) / 2);
                break;

            default:
                return false;
            }

            HashTable::LinearProbing<Tkey, Tdata> tmp(newCapacity, this->getLoadFactorMin(), this->getLoadFactorMax());

            for (consts::t_uIndex i = 0; i < this->capacity(); ++i)
            {
                auto key = this->table[i].getKey();

                if (key)
                    tmp.insert(*key, *this->table[i].getData());
            }

            this->hashFunction.resize(newCapacity);
            consts::swap(newCapacity, this->_capacity);
            consts::swap(tmp.table, this->table);

            return true;
        }

        virtual ~LinearProbing() {}
    };
}

#endif