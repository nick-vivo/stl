#ifndef __Tools_Module__
#define __Tools_Module__

namespace Tools
{
    template<class T>
    void swap(T& first, T& second)
    {
        T tmp = second;
        first = second;
        second = tmp;
    }
}

namespace Tree
{
    using t_count = unsigned long int;

    using t_index = long int;

    template<class T1>
    T1 max(const T1 &first, const T1 &second)
    {
        return first > second ? first : second;
    }

    t_index abs(t_index value)
    {
        return value > 0 ? value : -value;
    }
}



#endif