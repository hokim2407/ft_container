
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

namespace ft
{
    template <class T> //tree
    class map_iterator
    {
        typedef typename T::Node Node;
        typedef typename T::key_type key_type;
        typedef typename T::value_type value_type;

        typedef typename T::key_compare key_compare;
        typedef typename T::mapped_type mapped_type;

    private:
        Node *ptr;

    public:
        map_iterator(){};
        ~map_iterator(){};
        map_iterator(T *tree)
        {
            this->ptr = tree->first();
        }
        map_iterator(Node *node)
        {
            this->ptr = node;
        }
        map_iterator(const map_iterator &it)
        {
            *this = it;
        }
        map_iterator &operator=(const map_iterator &it)
        {
            this->ptr = it.base();
            return *this;
        }
        Node *base() const { return this->ptr; }
        Node &operator*() { return (this->ptr->data); }
        value_type *operator->() { return &(this->ptr->data); }
        bool operator==(const map_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const map_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const map_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const map_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const map_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const map_iterator &it) { return (this->ptr > it.base()); }

        map_iterator operator++()
        {
            (*this)++;
            return (*this);
        }

        map_iterator operator++(int)
        {
            this->ptr = this->ptr->biggerNode();
            return *this;
        }
        map_iterator operator--()
        {
            (*this)--;
            return *this;
        }
        map_iterator operator--(int)
        {

            this->ptr = this->ptr->smallerNode();
            return *this;
        }
        // map_iterator operator+(int n)
        // {
        //     return (map_iterator(this->base() + n));
        // }
        // map_iterator &operator+=(int n)
        // {
        //     ptr += n;
        //     return (*this);
        // }
        // int operator-(map_iterator &it)
        // {
        //     return (*this->ptr - it.base());
        // }
        // map_iterator operator-(int n)
        // {
        //     return (map_iterator(this->base() - n));
        // }
        // map_iterator &operator-=(int n)
        // {
        //     ptr -= n;
        //     return (*this);
        // }
        T &operator[](key_type key)
        {
            Node *tmp = this->ptr;
            while (tmp->parent == NULL)
                tmp = tmp->parent;
            while (tmp && tmp->data.first != key)
            {
                if (key < tmp->data.first)
                    tmp = tmp->left;
                else if (key > tmp->data.first)
                    tmp = tmp->left;
                else
                    return tmp;
            }
            return NULL;
        }
    };

    template <class T>
    class const_map_iterator
    {
    public:
        typedef ft::map_iterator<T> map_iterator;
        typedef typename T::Node Node;
        typedef typename T::key_type key_type;
        typedef typename T::value_type value_type;

        typedef typename T::key_compare key_compare;
        typedef typename T::mapped_type mapped_type;

    private:
        const Node *ptr;

    public:
        const_map_iterator(){};
        ~const_map_iterator(){};
        const_map_iterator(const T *tree) 
        {
            this->ptr = tree->first();
        }
        const_map_iterator(const Node *v) : ptr(v)
        {
        }
        const_map_iterator(const map_iterator &it) : ptr(it.base())
        {
        }
        const_map_iterator &operator=(const const_map_iterator &it)
        {
            ptr = it.base();
            return *this;
        }
        const Node *base() const { return ptr; }
        Node &operator*() { return (this->ptr->data); }
        value_type *operator->() { return &(this->ptr->data); }

        bool operator==(const const_map_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const const_map_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const const_map_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const const_map_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const const_map_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const const_map_iterator &it) { return (this->ptr > it.base()); }

        const_map_iterator operator++()
        {
            (*this)++;
            return (*this);
        }
        const_map_iterator operator++(int)
        {
            (*this)--;
            return *this;
        }
        const_map_iterator operator--()
        {
            ptr--;
            return (*this);
        }
        const_map_iterator operator--(int)
        {
            this->ptr = this->ptr->smallerNode();
            return *this;
        }

        T &operator[](key_type key)
        {
            Node *tmp = this->ptr;
            while (tmp->parent == NULL)
                tmp = tmp->parent;
            while (tmp && tmp->data.first != key)
            {
                if (key < tmp->data.first)
                    tmp = tmp->left;
                else if (key > tmp->data.first)
                    tmp = tmp->left;
                else
                    return tmp;
            }
            return NULL;
        }
    };
    template <class T>
    class reverse_map_iterator
    {
    public:
        typedef ft::map_iterator<T> map_iterator;

    private:
        map_iterator current;

    public:
        reverse_map_iterator(){};
        reverse_map_iterator(const T *tree)
        {
            current = map_iterator(tree->last());
        }
        reverse_map_iterator(map_iterator &it)
        {
            current = it.base();
        }
        explicit reverse_map_iterator(map_iterator it)
        {
            current = it;
        }
        map_iterator base() const
        {
            return (current);
        }
        T &operator*()
        {
            return (current.base()->data);
        }
        T *operator->()
        {
            return (current.base()->data);
        }

        reverse_map_iterator operator++() { return (reverse_map_iterator(--current)); }
        reverse_map_iterator operator++(int) { return (reverse_map_iterator(--current)); }
        reverse_map_iterator operator--() { return (reverse_map_iterator(++current)); }
        reverse_map_iterator operator--(int) { return (reverse_map_iterator(++current)); }

        bool operator==(const reverse_map_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const reverse_map_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const reverse_map_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const reverse_map_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const reverse_map_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const reverse_map_iterator &it) { return (this->ptr > it.base()); }

    };
    template <class T>
    class const_reverse_map_iterator
    {
    public:
        typedef ft::const_map_iterator<T> const_map_iterator;
        typedef ft::reverse_map_iterator<T> reverse_map_iterator;

    private:
        const_map_iterator current;

    public:
        const_reverse_map_iterator(){};
        const_reverse_map_iterator(const reverse_map_iterator &it) : current(it.base())
        {
            it;
        }
        const_reverse_map_iterator(const T *tree)
        {
            current = const_map_iterator(tree->last());
        }
        const_reverse_map_iterator &operator=(const const_reverse_map_iterator &it)
        {
            current = it.base();
            return *this;
        }
        explicit const_reverse_map_iterator(const_map_iterator it)
        {
            current = it;
        }
        const_map_iterator base() const
        {
            return (current);
        }
        T &operator*()
        {
            return (current.base()->data);
        }
        T *operator->()
        {
            return (current.base()->data);
        }
        
        const_reverse_map_iterator operator++() { return (const_reverse_map_iterator(--current)); }
        const_reverse_map_iterator operator++(int) { return (const_reverse_map_iterator(--current)); }
        const_reverse_map_iterator operator--() { return (const_reverse_map_iterator(++current)); }
        const_reverse_map_iterator operator--(int) { return (const_reverse_map_iterator(++current)); }

        bool operator==(const const_reverse_map_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const const_reverse_map_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const const_reverse_map_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const const_reverse_map_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const const_reverse_map_iterator &it) { return (this->ptr >= it.base()); }

    };
} // namespace ft

#endif