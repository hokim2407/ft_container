
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

namespace ft
{
    template <class T> //tree
    class map_iterator
    {
    public:
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
         explicit map_iterator(T *tree): _tree(tree)
        {
            this->_ptr = tree->first();
        }
        explicit map_iterator(T *tree,Node *node): _ptr(node), _tree(tree)
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
        value_type &operator*() { return (this->_ptr->data); }
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

            if(this->_ptr == this->_tree->first())
                this->_ptr = this->_tree->end();
            else
                this->_ptr = this->_ptr->smallerNode();
            return *this;
        }

    };

} // namespace ft

#endif