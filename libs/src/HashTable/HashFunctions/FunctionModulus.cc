#ifndef __HashFunctions_FunctionModulus_Class__
#define __HashFunctions_FunctionModulus_Class__

#include <string>

#include "HashFunction.cc"

namespace HashFunctions
{
    namespace consts
    {
        using t_uIndex = unsigned int;
    }

    template <class Tkey>
    class FunctionModulus : public HashFunction<Tkey, consts::t_uIndex>
    {

        consts::t_uIndex size;

    public:
        FunctionModulus(const consts::t_uIndex &size) : size(size) {}

        consts::t_uIndex getSize() const noexcept
        {
            return this->size;
        }

        consts::t_uIndex hash(const Tkey &key) const override;

        void resize(const consts::t_uIndex &newSize) noexcept
        {
            this->size = newSize;
        }

        virtual ~FunctionModulus(){};
    };

    template <>
    consts::t_uIndex FunctionModulus<std::string>::hash(const std::string &key) const
    {
        consts::t_uIndex sum = 0;
        consts::t_uIndex index = 1;

        for (char c : key)
            sum += index++ * static_cast<int>(c);

        return sum % this->getSize();
    }

    template <class Tkey>
    consts::t_uIndex FunctionModulus<Tkey>::hash(const Tkey &key) const
    {
        return key % this->getSize();
    }

}

#endif