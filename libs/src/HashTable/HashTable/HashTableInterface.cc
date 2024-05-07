#ifndef __HashTable_HashTableInterface_Interface__
#define __HashTable_HashTableInterface_Interface__

#include <stdexcept>
#include <string>

namespace HashTable
{
    namespace consts
    {
        using t_stat = float;
        using t_uIndex = unsigned int;

        const t_stat DEFAULT_LOAD_FACTOR_MIN = 0.25;
        const t_stat DEFAULT_LOAD_FACTOR_MAX = 0.75;
        const t_uIndex DEFAULT_CAPACITY = 3;

        enum LoadFactorStatus
        {
            GREATER_MAX,
            LESS_MIN,
            ZERO_CAPACITY_AND_ZERO_SIZE,
            NOT_ZERO_CAPACITY_AND_ZERO_SIZE,
            ALL_GOOD
        };

        template <class T>
        void swap(T &arg1, T &arg2)
        {
            T tmp = arg1;
            arg1 = arg2;
            arg2 = tmp;
        }
    }

    template <class Tkey, class Tdata>
    class HashTableInterface
    {
    public:
        consts::t_uIndex size() const noexcept
        {
            return _size;
        }

        consts::t_uIndex capacity() const noexcept
        {
            return _capacity;
        }

        consts::t_stat getLoadFactorMin() const noexcept
        {
            return _loadFactorMin;
        }

        consts::t_stat getLoadFactorMax() const noexcept
        {
            return _loadFactorMax;
        }

        consts::t_stat setLoadFactorMin(consts::t_stat newLoadFactorMin) noexcept(false)
        {
            if (newLoadFactorMin >= 1 || newLoadFactorMin < 0)
                throw std::out_of_range("LoadFactorMax must be less than 1, greater than or equal to 0");

            if (this->_loadFactorMax == newLoadFactorMin)
                throw std::invalid_argument("LoadFactorMin must be cannot be equal or greater LoadFactorMax");

            this->_loadFactorMin = newLoadFactorMin;
        }

        consts::t_stat setLoadFactorMax(consts::t_stat newLoadFactorMax) noexcept(false)
        {
            if (newLoadFactorMax > 1 || newLoadFactorMax <= 0)
                throw std::out_of_range("LoadFactorMax must be less than or equal to 1, greater than 0");

            if (this->_loadFactorMin >= newLoadFactorMax)
                throw std::invalid_argument("LoadFactorMax must be cannot be equal or greater LoadFactorMin");

            this->_loadFactorMax = newLoadFactorMax;
        }

        consts::t_stat loadFactor() const
        {
            if (this->_capacity == 0)
                return 1;
            return static_cast<consts::t_stat>(_size) / static_cast<consts::t_stat>(_capacity);
        }

        bool goodLoadFactor() const noexcept
        {
            if (this->_size == 0)
                return this->_capacity;

            consts::t_stat loadFact = this->loadFactor();
            return loadFact <= this->_loadFactorMax && loadFact >= this->_loadFactorMin;
        }

        consts::LoadFactorStatus loadFactorStatus() const noexcept
        {
            if (this->_size == 0)
                if (this->_capacity == 0)
                    return consts::LoadFactorStatus::ZERO_CAPACITY_AND_ZERO_SIZE;
                else
                    return consts::LoadFactorStatus::NOT_ZERO_CAPACITY_AND_ZERO_SIZE;

            else if (this->loadFactor() > this->_loadFactorMax)
                return consts::LoadFactorStatus::GREATER_MAX;
            else if (this->loadFactor() < this->_loadFactorMin)
                return consts::LoadFactorStatus::LESS_MIN;

            return consts::LoadFactorStatus::ALL_GOOD;
        }

        virtual void clear() noexcept = 0;
        virtual bool reCapacity() noexcept = 0;

        virtual bool insert(const Tkey &key, const Tdata &data) noexcept = 0;
        virtual bool erase(const Tkey &key) noexcept = 0;

        virtual bool add(const Tkey &key, const Tdata &data) noexcept = 0;
        virtual bool remove(const Tkey &key) noexcept = 0;

        virtual bool containsKey(const Tkey &key) noexcept = 0;
        virtual bool contains(const Tdata &data) const = 0;

        virtual std::string toString() const = 0;

    protected:
        consts::t_uIndex _size;
        consts::t_uIndex _capacity;
        consts::t_stat _loadFactorMax;
        consts::t_stat _loadFactorMin;

        HashTableInterface(const consts::t_uIndex &capacity, const consts::t_stat loadFactorMin, const consts::t_stat loadFactorMax) : _size(0), _capacity(capacity)
        {
            if (loadFactorMax >= 1 || loadFactorMax <= 0)
                throw std::out_of_range("LoadFactorMax must be less than or equal to 1, greater than or equal to 0");

            if (loadFactorMin >= 1 || loadFactorMin <= 0)
                throw std::out_of_range("LoadFactorMin must be less than or equal to 1, greater than or equal to 0");

            else if (loadFactorMin == loadFactorMax)
                throw std::invalid_argument("Factors cannot be equal");

            if (loadFactorMin > loadFactorMax)
            {
                this->_loadFactorMax = loadFactorMin;
                this->_loadFactorMin = loadFactorMax;
            }
            else
            {
                this->_loadFactorMin = loadFactorMin;
                this->_loadFactorMax = loadFactorMax;
            }
        }

        virtual ~HashTableInterface() {}
    };
}

#endif