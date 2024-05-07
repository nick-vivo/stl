#ifndef __HashTable_LinearProbingChainMethod_Class__
#define __HashTable_LinearProbingChainMethod_Class__

#include "HashFunctions/FunctionModulus.cc"
#include "HashTable/ChainMethodBase.cc"

namespace HashTable
{

    template <class Tkey, class Tdata>
    class LinearProbingChainMethod : public ChainMethodBase<Tkey, Tdata>
    {
    private:
        HashFunctions::FunctionModulus<Tkey> hashFunction;
        
        consts::t_uIndex hash(const Tkey &key)
        {
            return this->hashFunction.hash(key);
        }

    public:
        LinearProbingChainMethod(const consts::t_uIndex &capacity, const consts::t_stat loadFactorMin, const consts::t_stat loadFactorMax) : ChainMethodBase<Tkey, Tdata>(capacity, loadFactorMin, loadFactorMax), hashFunction(HashFunctions::FunctionModulus<Tkey>(capacity)) {}

        LinearProbingChainMethod(const consts::t_uIndex &capacity) : ChainMethodBase<Tkey, Tdata>(capacity, consts::DEFAULT_LOAD_FACTOR_MIN, consts::DEFAULT_LOAD_FACTOR_MAX), hashFunction(HashFunctions::FunctionModulus<Tkey>(capacity)) {}

        LinearProbingChainMethod() : ChainMethodBase<Tkey, Tdata>(consts::DEFAULT_CAPACITY, consts::DEFAULT_LOAD_FACTOR_MIN, consts::DEFAULT_LOAD_FACTOR_MAX), hashFunction(HashFunctions::FunctionModulus<Tkey>(consts::DEFAULT_CAPACITY)) {}

        LinearProbingChainMethod(const LinearProbingChainMethod &other) : ChainMethodBase<Tkey, Tdata>(other.capacity(), other.getLoadFactorMin(), other.getLoadFactorMax()), hashFunction(other.hashFunction)
        {
            for (consts::t_uIndex i = 0; i < other.capacity(); ++i)
            {
                for (auto& item : other.table[i])
                {
                    this->insert(item.key, item.data);
                }
            }
        }

        bool insert(const Tkey &key, const Tdata &data) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::insert(hashIndex, key, data);
        }

        bool erase(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::erase(hashIndex, key);
        }

        bool add(const Tkey &key, const Tdata &data) noexcept override
        {
            if (!this->goodLoadFactor())
                this->reCapacity();

            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::add(hashIndex, key, data);
        }

        bool remove(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::remove(hashIndex, key);
        }

        typename typeNode::Chain<Tkey, Tdata>::Node* search(const Tkey &key) noexcept
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::search(hashIndex, key);
        }

        bool containsKey(const Tkey &key) noexcept override
        {
            consts::t_uIndex hashIndex = this->hash(key);

            return ChainMethodBase<Tkey, Tdata>::search(hashIndex, key);
        }

        bool contains(const Tdata &data) const override
        {
            if(!this->table) return false;
            
            for (consts::t_uIndex i = 0; i < this->capacity(); ++i)
            {
                for (auto& item : this->table[i])
                {
                    if(item.data == data)
                        return true;
                }
            }
            return false;
        }

        bool reCapacity() noexcept override
        {
            consts::t_uIndex newCapacity;

            switch (this->loadFactorStatus())
            {
            case consts::LoadFactorStatus::ZERO_CAPACITY_AND_ZERO_SIZE:

                this->table = new typeNode::Chain<Tkey, Tdata>[consts::DEFAULT_CAPACITY];
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

            HashTable::LinearProbingChainMethod<Tkey, Tdata> tmp(newCapacity, this->getLoadFactorMin(), this->getLoadFactorMax());

            for (consts::t_uIndex i = 0; i < this->capacity(); ++i)
            {
                for (auto& item : this->table[i])
                {
                    tmp.insert(item.key, item.data);
                }
            }

            this->hashFunction.resize(newCapacity);
            consts::swap(newCapacity, this->_capacity);
            consts::swap(tmp.table, this->table);

            return true;
        }

        virtual ~LinearProbingChainMethod() {}
    };
}

#endif