

#ifndef UTILS_HPP
#define UTILS_HPP

namespace ft
{
    template <bool Cond, class T = void>
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
        static const bool value = false;
    };

    template <>
    struct is_integral<int>
    {
        static const bool value = true;
    };
    template <>
    struct is_integral<size_t>
    {
        static const bool value = true;
    };
} // namespace ft

#endif