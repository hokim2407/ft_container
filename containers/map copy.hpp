// -*- C++ -*-
//===----------------------------- map ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef MAP_HPP
#define MAP_HPP

#include <functional>
#include <memory>
#include <new>
#include <iostream>
#include <limits>
#include <initializer_list>
#include "../utils/utils.hpp"
#include "../utils/avl.hpp"
#include "../utils/pair.hpp"
#include "../utils/iterator.hpp"
#include "../utils/map_iterator.hpp"

namespace ft
{

    template <class Key, class T, class Compare = std::less<Key>,
              class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {
    public:
        // types:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef typename ft::Tree<Key, T> Tree;

        typedef typename ft::map_iterator<Tree> iterator;
        typedef typename ft::const_map_iterator<Tree> const_iterator;
        typedef typename ft::reverse_iterator<iterator> reverse_iterator;
        typedef typename ft::const_iterator<const_iterator> const_reverse_iterator;

        class value_compare
            : public std::binary_function<value_type, value_type, bool>
        {
            friend class map;

        public:
            bool operator()(const value_type &x, const value_type &y) const;
        };

    protected:
        Tree _tree;
        allocator_type _alloc;
        key_compare _key_comp;
        value_compare _value_comp;

    public:
        // construct/copy/destroy:
        map(const key_compare &comp = key_compare(), const allocator_type &a = allocator_type()) : _tree(comp, a), _alloc(a), _key_comp(comp)
        {
            this->_value_comp = value_compare();
        }

        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare(), const allocator_type &a = allocator_type(), typename ft::enable_if<ft::is_iterator<Tree, InputIterator>::value, size_type>::type * = 0

            ) : _tree(comp, a), _alloc(a), _key_comp(comp)
        {
            this->_value_comp = value_compare();
            this->insert(first, last);
        }
        map(const map &m)
        {
        this->_tree =  m._tree;
        this->_alloc = m._alloc;
        this->_key_comp = m._key_comp;
        this->_value_comp = m._value_comp;
        }

        ~map(){};

        map &operator=(const map &m)
        {
            if (*this != m)
            {
                this->_tree =  m._tree;
                this->_alloc = m._alloc;
                this->_key_comp = m._key_comp;
                this->_value_comp = m._value_comp;
            }
            return *this;
        }

        // iterators:
        iterator begin()
        {
            return iterator(&(this->_tree));
        }
        const_iterator begin() const
        {
            return const_iterator(&(this->_tree));
        }
        iterator end()
        {
            return iterator(&(this->_tree), this->_tree.end());
        }
        const_iterator end() const
        {
            return const_iterator(&(this->_tree), this->_tree.end());
        }

        reverse_iterator rbegin()
        {
            return reverse_iterator(iterator(&(this->_tree), this->_tree.last()));
        }
        const_reverse_iterator rbegin() const
        {
            return const_reverse_iterator(const_iterator(&(this->_tree), this->_tree.last()));
        }
        reverse_iterator rend()
        {
            return reverse_iterator(iterator(&(this->_tree), this->_tree.end()));
        }
        const_reverse_iterator rend() const
        {
            return const_reverse_iterator(const_iterator(&(this->_tree), this->_tree.end()));
        }

        // capacity:
        bool empty() const
        {
            return this->_tree.size() == 0;
        }
        size_type size() const
        {
            return this->_tree.size();
        }
        size_type max_size() const
        {
            return this->_tree.max_size();
        }

        const size_type count (const key_type& k) const{
            const_iterator elem = this->find(k);
            return elem == NULL? 0 : 1 ;
        };
        // element access:
        mapped_type &operator[]( key_type &k)
        {
            
            return this->_tree.search(this->_tree.base(), k)->data.second;
        }
        mapped_type &operator[](const key_type &k)
        {
            return this->_tree.search(this->_tree.base(), k)->data.second;
        }
        // modifiers:
        // pair<iterator, bool>

        pair<iterator, bool> insert(const value_type &v)
        {
            bool is_new = false;
            if (_tree.search(this->_tree.base(), v.first) == NULL)
            { 
                this->_tree.insert(v);
                is_new = true;
            }
            iterator iter = iterator(&(this->_tree),_tree.search(this->_tree.base(), v.first));
            
            return ft::make_pair<iterator,bool>(iter,is_new);
        }

        iterator insert(const_iterator position, const value_type &v, typename ft::enable_if<!ft::is_iterator<Tree, value_type>::value, size_type>::type * = 0)
        {
            if (_tree.search(this->_tree.base(), v.first) == NULL)
            { 
                this->_tree.insert(v, position.node());
            }
            iterator iter = iterator(&(this->_tree),_tree.search(this->_tree.base(), v.first));

            return iter;
        }
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last, typename ft::enable_if<ft::is_iterator<Tree, InputIterator>::value, size_type>::type * = 0)
        {

            for (InputIterator iter = first; iter != last; iter++)
            {

                if (_tree.search(this->_tree.base(), iter -> first) == NULL)
                { 
                    this->_tree.insert(*iter);
                }
            }
        }

        void erase(const_iterator position)
        {
             this->_tree.remove((*position).first);
        }
        size_type erase(const key_type &k)
        {
            this->_tree.remove(k);
            return this->size();
        }

        void erase(const_iterator first, const_iterator last)
        {
            for (const_iterator iter = first; iter != last; iter++)
            {
                this->_tree.remove((*iter).first);
            }
        }
        void clear()
        {
            this->_tree.clear();
        }

        void swap(map &m)
        {
            this->_tree.swap(m._tree);
        }


        // observers:
        allocator_type get_allocator() const
        {
            return this->_alloc;
        }
        key_compare key_comp() const
        {
            return this->_key_comp;
        }
        value_compare value_comp() const
        {
            return this->_value_comp;
        }

        // map operations:
        iterator find(const key_type &k)
        {

            return iterator(&(this->_tree), this->_tree.search(this->_tree.base(), k));
        }
        const_iterator find(const key_type &k) const
        {
            return iterator(&(this->_tree), this->_tree.search(this->_tree.base(), k));
        };
        iterator lower_bound(const key_type &k);
        const_iterator lower_bound(const key_type &k) const;

        iterator upper_bound(const key_type &k);
        const_iterator upper_bound(const key_type &k) const;

        pair<iterator, iterator> equal_range(const key_type &k);
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
    };

    template <class Key, class T, class Compare, class Allocator>
    bool operator==(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y){
                   return !(x < y) && ! (x > y);
               }

    template <class Key, class T, class Compare, class Allocator>
    bool  operator<(const map<Key, T, Compare, Allocator> &x,
              const map<Key, T, Compare, Allocator> &y){
                   return ft::lexicographical_compare(x.begin(),x.end(), y.begin(),y.end()) ;
               }
    template <class Key, class T, class Compare, class Allocator>
    bool operator>(const map<Key, T, Compare, Allocator> &x,
                   const map<Key, T, Compare, Allocator> &y){
                   return ft::lexicographical_compare( y.begin(),y.end(),x.begin(),x.end()) ;
               }

    template <class Key, class T, class Compare, class Allocator>
    bool  operator!=(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y){
                   return !(x == y);
               }


    template <class Key, class T, class Compare, class Allocator>
    bool operator>=(const map<Key, T, Compare, Allocator> &x,
                    const map<Key, T, Compare, Allocator> &y){
                   return !(x<y);
               }

    template <class Key, class T, class Compare, class Allocator>
    bool operator<=(const map<Key, T, Compare, Allocator> &x,
                    const map<Key, T, Compare, Allocator> &y){
                   return !(x>y);
               }

    // specialized algorithms:
    template <class Key, class T, class Compare, class Allocator>
    void
    swap(map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y)
    {
        x.swap(y);
    };

} // namespace ft

#endif