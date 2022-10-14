
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
    template <class T>
    class iterator
    {
    private:
        T *ptr;

    public:
        iterator(){};
        ~iterator(){};
        iterator(T *v)
        {
            ptr = v;
        }
        iterator(const iterator &it)
        {
            *this = it;
        }
        iterator &operator=(const iterator &it)
        {
            ptr = it.base();
            return *this;
        }
        T *base() const { return ptr; }
        T &operator*() { return *ptr; }
        T *operator->() { return ptr; }
        bool operator==(const iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const iterator &it) { return (this->ptr > it.base()); }

        iterator operator++()
        {
            ptr++;
            return (*this);
        }

        iterator operator++(int)
        {
            ptr++;
            return (*this);
        }
        iterator operator--()
        {
            ptr--;
            return (*this);
        }
        iterator operator--(int)
        {
            ptr--;
            return (*this);
        }
        iterator operator+(int n)
        {
            return (iterator(this->base() + n));
        }
        iterator &operator+=(int n)
        {
            ptr += n;
            return (*this);
        }
        int operator-(iterator &it)
        {
            return (*this->ptr - it.base());
        }
        iterator operator-(int n)
        {
            return (iterator(this->base() - n));
        }
        iterator &operator-=(int n)
        {
            ptr -= n;
            return (*this);
        }
        T &operator[](int n) { return ptr[n]; }
    };

    template <class T>
    class const_iterator
    {
    public:
        typedef ft::iterator<T> iterator;

    private:
        const T *ptr;

    public:
        const_iterator(){};
        ~const_iterator(){};
        const_iterator(const T *v) : ptr(v)
        {
        }
        const_iterator(const iterator &it) : ptr(it.base())
        {
        }
        const_iterator &operator=(const const_iterator &it)
        {
            ptr = it.base();
            return *this;
        }
        const T *base() const { return ptr; }
        const T operator*() { return *ptr; }
        const T *operator->() { return ptr; }

        bool operator==(const const_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const const_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const const_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const const_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const const_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const const_iterator &it) { return (this->ptr > it.base()); }

        const_iterator operator++()
        {
            ptr++;
            return (*this);
        }
        const_iterator operator++(int)
        {
            ptr++;
            return (*this);
        }
        const_iterator operator--()
        {
            ptr--;
            return (*this);
        }
        const_iterator operator--(int)
        {
            ptr--;
            return (*this);
        }
        const_iterator operator+(int n)
        {
            return (const_iterator(this->base() + n));
        }
        const_iterator &operator+=(int n)
        {
            ptr += n;
            return (*this);
        }
        int operator-(const_iterator &it)
        {
            return (this->ptr - it.base());
        }
        const_iterator operator-(int n)
        {
            return (const_iterator((this->base() - n)));
        }
        const_iterator &operator-=(int n)
        {
            ptr -= n;
            return (*this);
        }
        T &operator[](int n) { return ptr[n]; }
    };
    template <class T>
    class reverse_iterator
    {
    public:
        typedef ft::iterator<T> iterator;

    private:
        iterator current;

    public:
        reverse_iterator(){};
        reverse_iterator(const T *v)
        {
            current = iterator(v);
        }
        reverse_iterator(iterator &it)
        {
            current = it.base();
        }
        explicit reverse_iterator(iterator it)
        {
            current = it;
        }
        iterator base() const
        {
            return (current);
        }
        T &operator*()
        {
            return (*(current - 1));
        }
        T *operator->()
        {
            return (current);
        }
        reverse_iterator operator+(int n) { return (reverse_iterator(base() - n)); }
        reverse_iterator operator-(int n) { return (reverse_iterator(base() + n)); }
        bool operator==(const reverse_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const reverse_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const reverse_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const reverse_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const reverse_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const reverse_iterator &it) { return (this->ptr > it.base()); }
        reverse_iterator &operator+=(int n)
        {
            current -= n;
            return (*this);
        }
        reverse_iterator &operator-=(int n)
        {
            current += n;
            return (*this);
        }
    };
    template <class T>
    class const_reverse_iterator
    {
    public:
        typedef ft::const_iterator<T> const_iterator;
        typedef ft::reverse_iterator<T> reverse_iterator;

    private:
        const_iterator current;

    public:
        const_reverse_iterator(){};
        const_reverse_iterator(const reverse_iterator &it) : current(it.base())
        {
            it;
        }
        const_reverse_iterator(const T *v)
        {
            current = const_iterator(v);
        }
        const_reverse_iterator &operator=(const const_reverse_iterator &it)
        {
            current = it.base();
            return *this;
        }
        explicit const_reverse_iterator(const_iterator it)
        {
            current = it;
        }
        const_iterator base() const
        {
            return (current);
        }
        const T operator*()
        {
            return (*(current - 1));
        }
        const T *operator->()
        {
            return (current - 1);
        }
        const_reverse_iterator operator+(int n) { return (const_reverse_iterator(base() - n)); }
        const_reverse_iterator operator-(int n) { return (const_reverse_iterator(base() + n)); }
        bool operator==(const const_reverse_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const const_reverse_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const const_reverse_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const const_reverse_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const const_reverse_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const const_reverse_iterator &it) { return (this->ptr > it.base()); }
        const_reverse_iterator &operator+=(int n)
        {
            current -= n;
            return (*this);
        }
        const_reverse_iterator &operator-=(int n)
        {
            current += n;
            return (*this);
        }
    };
} // namespace ft

#endif