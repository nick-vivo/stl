#ifndef __Tools_Module__
#define __Tools_Module__
/**
 * @file src/Tree/Tools.cc, lib - Tree.
 * 
 * @brief Файл с различными 
 * 
 * Файл содержит класс Node с двумя подузлами и полем data, для того, чтобы
 * различные деревья могли их использовать.
 */

/**
 * @brief Стандартные функции для работы. Помогают при работе с деревом.
 */
namespace Tools
{   
    /**
    * @brief Меняет местами два объекта.
    * 
    * Функция меняет местами два объекта. Нужно иметь оператор.
    * присваивания и конструктор копирования. Стандартный swap(a, b);
    * 
    * Пример: a = 3, b = 2; -> a = 2, b = 3;
    * 
    * @tparam T Тип объектов first и second.
    * 
    * @param first Первый объект. Станет second.
    * @param second Второй объект. Станет first.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T>
    void swap(T& first, T& second) noexcept
    {
        T tmp = second;
        first = second;
        second = tmp;
    }

    /**
    * @brief Ищет макисмальный объект из двух.
    * 
    * Функция находит маскимальный объект из двух, используя оператор > и
    * возвращает копию на максимальное из этих двух значений. Должен быть
    * перегружен оператор > и конструктор копирования.
    * 
    * Пример: a = 2, b = 3; -> return c = 3.
    * 
    * @tparam T Тип объектов.
    * 
    * @param first Первое значение.
    * @param second Второе значение.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    template<class T1>
    T1 max(const T1 &first, const T1 &second) noexcept
    {
        return first > second ? first : second;
    }
}

/**
 * @brief Функции, типы для корреткной работы классов деревьев.
 */
namespace Tree
{
    /**
    * @tparam Тип данных для количественных параметров по типу высоту и длинны.
    * */
    using t_count = unsigned long int;

    /**
    * @tparam Тип данных для индексов. Могут быть отрицательными.
    * */
    using t_index = long int;

    /**
    * @brief Абсолютное значение(модуль).
    * 
    * Функция возвращает копию абсолютного значения параметра value.
    * 
    * Пример: a = -2; -> return c = 2.
    *         a = 2; -> return c = 2.
    * 
    * @tparam t_index тип из Tree::t_index.
    * 
    * @param value Значение.
    * 
    * @return Возвращает поток stream(по умолчанию std::cout).
    */
    t_index abs(t_index value) noexcept
    {
        return value > 0 ? value : -value;
    }
}



#endif