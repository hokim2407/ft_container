
#ifndef MAP_ITERATOR_HPP
#define MAP_ITERATOR_HPP

#include "avl.hpp"
namespace ft
{
    template <class T> //pair
    class map_iterator
    {
    public:
        typedef T value_type;
        typedef typename T::key_type key_type;
        typedef typename T::mapped_type mapped_type;

        typedef typename ft::Node<value_type> Node;
        typedef typename ft::Tree<key_type, mapped_type> Tree;

        typedef typename Tree::key_compare key_compare;

    private:
        Node *_ptr;
        Node *_end;
        Node *_first;
        Node *_last;

    public:
        map_iterator(){};
        ~map_iterator(){};
        map_iterator(T *tree):
        {
            this->_ptr = tree->first();
            this->_end = tree->end();
            this->_first = tree->first();
            this->_last = tree->last();
        }
        map_iterator(T *tree,Node *node): _ptr(node)
        {
            this->_end = tree->end();
            this->_first = tree->first();
            this->_last = tree->last();
        }
        map_iterator(const map_iterator &it)
        {
            this->_ptr = tree->first();
            this->_end = it->end();
            this->_first = it->first();
            this->_last = it->last();
        }
        map_iterator &operator=(const map_iterator &it)
        {
            this->_ptr = tree->first();
            this->_end = it->end();
            this->_first = it->first();
            this->_last = it->last();
            return *this;
        }
        Node *end() const { return this->_end; }
        Node *first() const { return this->_first; }
        Node *last() const { return this->_last; }
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
            if(this->_ptr == this->last())
                this->_ptr = this->end();
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

            if(this->_ptr == this->first())
                this->_ptr = this->end();
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
        Node *_ptr;
        T *_tree;

    public:
        const_map_iterator(){};
        ~const_map_iterator(){};
        const_map_iterator(const T *tree)
        {
           this-> _tree = new T();
            this->_ptr = tree->first();
        }
        const_map_iterator(const T *tree,  Node *node) : _ptr(node)
        {
            *(this->_tree) = *(tree);
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
        Node *node() { return _ptr; }
         Node *base() const { return _ptr; }
        const value_type &operator*()const { return (this->_ptr->data); }
        const value_type *operator->() const{ return &(this->_ptr->data); }

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


} // namespace ft

#endif