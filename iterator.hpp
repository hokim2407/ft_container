
#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
    template <class T>
    class iterator
    {
    public:
    typedef T value_type;
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
        value_type &operator*() { return *ptr; }
        value_type *operator->() { return ptr; }
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
        typedef T value_type;

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
        value_type &operator*() { return *ptr; }
        value_type *operator->() { return ptr; }

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
        typedef typename iterator::value_type value_type;

    private:
        iterator current;

    public:
        reverse_iterator(){};
        reverse_iterator(const T *v)
        {
            this->current = iterator(v);
        }
        reverse_iterator(iterator &it)
        {
            this->current = it.base();
        }
        explicit reverse_iterator(iterator it)
        {
            this->current = it;
        }
        iterator base() const
        {
            return (this->current);
        }
        value_type &operator*()
        {
            return (this->current).operator*();
        }
        value_type *operator->()
        {
            return (this->current).operator->();
        }
        reverse_iterator operator+(int n) { return (reverse_iterator(base() - n)); }
        reverse_iterator operator-(int n) { return (reverse_iterator(base() + n)); }
        reverse_iterator operator++() { return (reverse_iterator(--(this->current))); }
        reverse_iterator operator++(int) { return (reverse_iterator(--(this->current))); }
        reverse_iterator operator--() { return (reverse_iterator(++(this->current))); }
        reverse_iterator operator--(int) { return (reverse_iterator(++(this->current))); }
        bool operator==(const reverse_iterator &it) { return (this->current == it.base()); }
        bool operator!=(const reverse_iterator &it) { return (this->current != it.base()); }
        bool operator<(const reverse_iterator &it) { return (this->current < it.base()); }
        bool operator<=(const reverse_iterator &it) { return (this->current <= it.base()); }
        bool operator>=(const reverse_iterator &it) { return (this->current >= it.base()); }
        bool operator>(const reverse_iterator &it) { return (this->current > it.base()); }
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
        typedef typename const_iterator::value_type value_type;


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
            this->current = const_iterator(v);
        }
        const_reverse_iterator &operator=(const const_reverse_iterator &it)
        {
            this->current = it.base();
            return *this;
        }
        explicit const_reverse_iterator(const_iterator it)
        {
            this->current = it;
        }
        const_iterator base() const
        {
            return (this->current);
        }
        value_type &operator*()
        {
            return (this->current).operator*();
        }
        value_type *operator->()
        {
            return (this->current).operator->();
        }

        const_reverse_iterator operator+(int n) { return (const_reverse_iterator(base() - n)); }
        const_reverse_iterator operator-(int n) { return (const_reverse_iterator(base() + n)); }
        const_reverse_iterator operator++() { return (const_reverse_iterator(--(this->current))); }
        const_reverse_iterator operator++(int) { return (const_reverse_iterator(--(this->current))); }
        const_reverse_iterator operator--() { return (const_reverse_iterator(++(this->current))); }
        const_reverse_iterator operator--(int) { return (const_reverse_iterator(++(this->current))); }
        bool operator==(const const_reverse_iterator &it) { return (this->current == it.base()); }
        bool operator!=(const const_reverse_iterator &it) { return (this->current != it.base()); }
        bool operator<(const const_reverse_iterator &it) { return (this->current < it.base()); }
        bool operator<=(const const_reverse_iterator &it) { return (this->current <= it.base()); }
        bool operator>=(const const_reverse_iterator &it) { return (this->current >= it.base()); }
        bool operator>(const const_reverse_iterator &it) { return (this->current > it.base()); }
        
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