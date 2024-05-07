#ifndef __HashFunctions_HashFunction_Interface__
#define __HashFunctions_HashFunction_Interface__

namespace HashFunctions
{
    using t_count = unsigned int;

    template <class Tkey, class Tresult>
    class HashFunction
    {
    public:
        
        virtual Tresult hash(const Tkey &key) const = 0;

        virtual ~HashFunction(){};
    };
}

#endif