

#ifndef PAIR_HPP
#define PAIR_HPP
#include "../containers/vector.hpp"

namespace ft
{

    template <class T1, class T2>
    struct pair
    {
        typedef T1 key_type;
        typedef T2 value_type;
        T1 first;
        T2 second;
        pair() : first(), second() {}
        pair(const pair<T1, T2> &p) : first(p.first), second(p.second) {}
        pair(const T1 &v1, const T2 &v2) : first(v1), second(v2) {}
        pair &operator=(const pair &p)
        {
            this->first = p.first;
            this->second = p.second;
            return *this;
        }
        ~pair() {}
    };
    template <class T1, class T2>
    bool operator==(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return ((p1.first == p2.first) && (p1.second == p2.second));
    }
    template <class T1, class T2>
    bool operator!=(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return !((p1.first == p2.first) && (p1.second == p2.second));
    }
    template <class T1, class T2>
    bool operator<(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return (p1.first < p2.first);
    }

    template <class T1, class T2>
    bool operator>(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return (p1.first > p2.first);
    }

    template <class T1, class T2>
    bool operator<=(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return (p1.first <= p2.first);
    }
    template <class T1, class T2>
    bool operator>=(const pair<T1, T2> &p1, const pair<T1, T2> &p2)
    {
        return (p1.first >= p2.first);
    }

    template <class T1, class T2>
    pair<T1, T2> make_pair(T1 x, T2 y)
    {
        return (ft::pair<T1, T2>(x, y));
    }

}

#endif