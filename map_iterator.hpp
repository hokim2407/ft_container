
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
        Node *_ptr;
        T *_tree;

    public:
        map_iterator(){};
        ~map_iterator(){};
        map_iterator(T *tree): _tree(tree)
        {
            this->_ptr = tree->first();
        }
        map_iterator(T *tree,Node *node): _ptr(node), _tree(tree)
        {
        }
        map_iterator(const map_iterator &it)
        {
            *this = it;
        }
        map_iterator &operator=(const map_iterator &it)
        {
            this->_tree = it.tree();
            this->_ptr = it.base();
            return *this;
        }
        T *tree() const { return this->_tree; }
        Node *base() const { return this->_ptr; }
        Node &operator*() { return (this->_ptr->data); }
        value_type *operator->() { return &(this->_ptr->data); }
        bool operator==(const map_iterator &it) { return (this->_ptr == it.base()); }
        bool operator!=(const map_iterator &it) { return (this->_ptr != it.base()); }
        bool operator<(const map_iterator &it) { return (this->_ptr < it.base()); }
        bool operator<=(const map_iterator &it) { return (this->_ptr <= it.base()); }
        bool operator>=(const map_iterator &it) { return (this->_ptr >= it.base()); }
        bool operator>(const map_iterator &it) { return (this->_ptr > it.base()); }

        map_iterator operator++()
        {
            (*this)++;
            return (*this);
        }

        map_iterator operator++(int)
        {
            if(this->_ptr == this->_tree->last())
                this->_ptr = this->_tree->end();
            else
                this->_ptr = this->_ptr->biggerNode();
            return *this;
        }
        map_iterator operator--()
        {
            (*this)--;
            return *this;
        }
        map_iterator operator--(int)
        {

            if(this->_ptr == this->tree->first())
                this->_ptr = this->_tree->end();
            else
                this->_ptr = this->_ptr->smallerNode();
            return *this;
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
        const Node *_ptr;
        T *_tree;

    public:
        const_map_iterator(){};
        ~const_map_iterator(){};
        const_map_iterator(const T *tree) : _tree(tree)
        {
            this->_ptr = tree->first();
        }
        const_map_iterator(const T *tree, const Node *node) : _ptr(node), _tree(tree)
        {
        }
        const_map_iterator(const map_iterator &it) : _ptr(it.base())
        {
            *this = it;
        }
        const_map_iterator &operator=(const const_map_iterator &it)
        {
            this->_tree = it.tree();
            this->_ptr = it.base();
            return *this;
        }
        T *tree() const { return this->_tree; }
        const Node *base() const { return _ptr; }
        Node &operator*() { return (this->_ptr->data); }
        value_type *operator->() { return &(this->_ptr->data); }

        bool operator==(const const_map_iterator &it) { return (this->_ptr == it.base()); }
        bool operator!=(const const_map_iterator &it) { return (this->_ptr != it.base()); }
        bool operator<(const const_map_iterator &it) { return (this->_ptr < it.base()); }
        bool operator<=(const const_map_iterator &it) { return (this->_ptr <= it.base()); }
        bool operator>=(const const_map_iterator &it) { return (this->_ptr >= it.base()); }
        bool operator>(const const_map_iterator &it) { return (this->_ptr > it.base()); }

        const_map_iterator operator++()
        {
            (*this)++;
            return (*this);
        }
        const_map_iterator operator++(int)
        {
            if(this->_ptr == this->_tree->last())
                this->_ptr = this->_tree->end();
            else
                this->_ptr = this->_ptr->biggerNode();
            return *this;
        }
        const_map_iterator operator--()
        {
            _ptr--;
            return (*this);
        }
        const_map_iterator operator--(int)
        {
            if(this->_ptr == this->tree->first())
                this->_ptr = this->_tree->end();
            else
                this->_ptr = this->_ptr->smallerNode();
            return *this;
        }


    };

    template <class IT>
    class reverse_map_iterator
    {
    public:
        typedef IT iterator;

    private:
        iterator current;

    public:
        reverse_map_iterator(){};
        reverse_map_iterator(const IT *v)
        {
            current = iterator(v);
        }
        reverse_map_iterator(iterator &it)
        {
            current = it.base();
        }
        explicit reverse_map_iterator(iterator it)
        {
            current = it;
        }
        iterator base() const
        {
            return (current);
        }
        IT &operator*()
        {
            return (*(current - 1));
        }
        IT *operator->()
        {
            return (current);
        }
        reverse_map_iterator operator+(int n) { return (reverse_map_iterator(base() - n)); }
        reverse_map_iterator operator-(int n) { return (reverse_map_iterator(base() + n)); }
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
        reverse_map_iterator &operator+=(int n)
        {
            current -= n;
            return (*this);
        }
        reverse_map_iterator &operator-=(int n)
        {
            current += n;
            return (*this);
        }
    };
    template <class IT>
    class const_reverse_map_iterator
    {
    public:
        typedef ft::const_map_iterator<IT> const_iterator;
        typedef ft::reverse_map_iterator<IT> reverse_map_iterator;

    private:
        const_iterator current;

    public:
        const_reverse_map_iterator(){};
        const_reverse_map_iterator(const reverse_map_iterator &it) : current(it.base())
        {
            it;
        }
        const_reverse_map_iterator(const IT *v)
        {
            current = const_iterator(v);
        }
        const_reverse_map_iterator &operator=(const const_reverse_map_iterator &it)
        {
            current = it.base();
            return *this;
        }
        explicit const_reverse_map_iterator(const_iterator it)
        {
            current = it;
        }
        const_iterator base() const
        {
            return (current);
        }
        const IT operator*()
        {
            return (*(current - 1));
        }
        const IT *operator->()
        {
            return (current - 1);
        }
        const_reverse_map_iterator operator+(int n) { return (const_reverse_map_iterator(base() - n)); }
        const_reverse_map_iterator operator-(int n) { return (const_reverse_map_iterator(base() + n)); }
        bool operator==(const const_reverse_map_iterator &it) { return (this->ptr == it.base()); }
        bool operator!=(const const_reverse_map_iterator &it) { return (this->ptr != it.base()); }
        bool operator<(const const_reverse_map_iterator &it) { return (this->ptr < it.base()); }
        bool operator<=(const const_reverse_map_iterator &it) { return (this->ptr <= it.base()); }
        bool operator>=(const const_reverse_map_iterator &it) { return (this->ptr >= it.base()); }
        bool operator>(const const_reverse_map_iterator &it) { return (this->ptr > it.base()); }
        const_reverse_map_iterator &operator+=(int n)
        {
            current -= n;
            return (*this);
        }
        const_reverse_map_iterator &operator-=(int n)
        {
            current += n;
            return (*this);
        }
    };



} // namespace ft

#endif