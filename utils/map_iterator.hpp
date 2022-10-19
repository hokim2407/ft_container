
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
        Node *_end;

    public:
        map_iterator(){};
        ~map_iterator(){};
         explicit map_iterator(T *tree)
        {
            this->_ptr = tree->first();
            this->_end = tree->end();
        }
        explicit map_iterator(Node *node,Node *end)
        {    
            this->_ptr = node;
            this->_end = end; 
     

        }
        map_iterator(const map_iterator &it)
        {
            *this = it;
        }
        map_iterator &operator=(const map_iterator &it)
        {
            this->_ptr = it.end();
            this->_end = it.base();
            return *this;
        }
        void setEnd(Node *end) const { this->_end=end; }
        void setBase( Node *base) const { this->_ptr=base; }
        Node *end() const { return this->_end; }
        Node *base() const { return this->_ptr; }
        value_type &operator*() {
            return (this->_ptr->data); }
        value_type *operator->() { 
            return &(this->_ptr->data); }
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
            this->_ptr = this->_ptr->biggerNode();
            if(this->_ptr == NULL)
                this->_ptr = this->_end;
            return *this;
        }
        map_iterator operator--()
        {
            (*this)--;
            return *this;
        }
        map_iterator operator--(int)
        {     
                
            this->_ptr = this->_ptr->smallerNode();
            if(this->_ptr == NULL)
                this->_ptr = this->_end;
            return *this;
        }

    };

} // namespace ft

#endif