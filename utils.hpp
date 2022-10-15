

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{

    template <bool B, class T = void>
    struct enable_if
    {
    };

    template <class T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <class>
    struct is_integral
    {
        static const bool value = true;
    };

    template <>
    struct is_integral<int>
    {
        static const bool value = false;
    };
} // namespace ft

#endif