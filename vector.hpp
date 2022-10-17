// -*- C++ -*-
//===------------------------------ vector --------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <memory>
#include <new>
#include <iostream>
#include <limits>
#include <initializer_list>
#include "iterator_traits.hpp"
#include "iterator.hpp"
#include "compare.hpp"
#include "utils.hpp"
namespace ft
{

    template <class T, class Allocator = std::allocator<T> >
    class vector{
    public:
        // types:
        typedef T value_type;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;

        typedef ft::iterator<T> iterator;
        typedef ft::const_iterator<T> const_iterator;

        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::const_reverse_iterator<const_iterator> const_reverse_iterator;

        private:

            pointer                                             _begin;
            size_type                                           _size;
            size_type                                           _capa;
            allocator_type                                      _alloc;


        public:


        // construct/copy/destroy:
        vector(const allocator_type& __alloc = allocator_type()): _alloc(__alloc), _size(0), _capa(0) {
            this->_begin = this->_alloc.allocate(0);
        }

        vector(size_type n, const value_type &value = value_type(), const allocator_type &alloc = allocator_type()
       , typename ft::enable_if<ft::is_integral<size_type>::value, size_type>::type * = 0
        )
            : _alloc(alloc), _size(0), _capa(n)
        {
            this->_begin = this->_alloc.allocate(n);
            for (; size() < capacity(); this->_size++)
                this->_alloc.construct(&this->_begin[ this->_size], value);
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type()
         , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0
        )
         :  _size(0), _capa(0), _alloc(alloc)
        {
            this->_capa= last.base()-first.base();
            this->_size=this->_capa;
            this->_begin = this->_alloc.allocate(this->_capa);
            int i = 0;
            for (InputIterator iter = first; iter != last; i++,iter++) {
                this->_alloc.construct(&this->_begin[i], *iter);
            }
        }

        vector(const vector &v):  _size(0),_capa(v._size), _alloc(v._alloc){
            this->_begin = this->_alloc.allocate(this->_capa);
            for (; size() < v._size; this->_size++) {
                this->_alloc.construct(&this->_begin[_size], v._begin[_size]);
            }
            
        }

        ~vector(){
            //std::destroy(this->_begin, this->_end);
            // deallocate
            this->clear();
            this->_alloc.deallocate(this->_begin, capacity());
        }

        vector &operator=(const vector &v)
        {
            if (this == v)
                return (*this);

            // remove all
            this->clear();

            this->_alloc=  v._alloc;
            // remove alloc if capa is smaller
            if (this->_capa < v._size) {
                this->_alloc.deallocate(this->_data, this->_capa);
                this->_begin = this->_alloc.allocate(v._size);
                this->_capa = v._size;
            }

            for (; size() < v._size; this->_size++) {
                this->_alloc.construct(&this->_begin[_size], v._begin[_size]);
            }
            return *this;
        }

        // // iterators:
        iterator begin() {
            return iterator(this->_begin);
        }
        const_iterator begin() const  {
            return const_iterator(this->_begin);
        }
         iterator end() {
            return  iterator(this->_begin)+ this->_size;
         }
        const_iterator end() const {

            return const_iterator(this->_begin)+ this->_size;
         }

        reverse_iterator rbegin() {
              return reverse_iterator(iterator(this->end()-1));
        }
        const_reverse_iterator rbegin() const {
            return  const_reverse_iterator(iterator(this->end()-1));
        }
        reverse_iterator rend() {
            
            return  reverse_iterator(this->begin() - 1);
        }
        const_reverse_iterator rend() const {
            
            return  const_reverse_iterator(this->begin() - 1);
        }

        // // capacity:
        size_type size() const{
             return this->_size;
         }
        size_type max_size() const {
            return (this->_alloc.max_size() < (unsigned long)std::numeric_limits<difference_type>::max()) ?
                this->_alloc.max_size() :
                (unsigned long)std::numeric_limits<difference_type>::max();
        }
        size_type capacity() const {
            return this->_capa;
        }
        bool empty() const {
            return size() == 0;
        }
        void reserve(size_type n){
            if(n < capacity())
                return;

            pointer ori_begin = this->_begin;
            size_type ori_size = size();
            size_type ori_capacity = capacity();

            this->_begin = this->_alloc.allocate(n);
            this->_capa = n;
            this->_size = 0;

            for (; size() < ori_size; this->_size++)
            {
                this->_alloc.construct(&this->_begin[this->_size], ori_begin[this->_size]);
                this->_alloc.destroy(&ori_begin[this->_size]);
            }

            this->_alloc.deallocate(ori_begin, ori_capacity);

        }

        // element access:
        reference operator[](size_type n){
            return at(n);
        }
        const_reference operator[](size_type n) const{
            return at(n);

        }
        reference at(size_type n){
            if(capacity()< n)
                return *(this->end());
            return this->_begin[n];
        }
        const_reference at(size_type n) const{
            return at(n);
        }

        reference front(){
            return this->_begin[0];
        }
        const_reference front() const{
            return this->_begin[0];
        }
        reference back(){
            return this->_begin[size()-1];
        }
        const_reference back() const{
            return this->_begin[size()-1];
        }

        // // modifiers:
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last,
         typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0)
        {
            this->clear();
            if (this->_capa < last - first)
                this->reserve(last - first);
            for (; first != last; ++first)
            {
                this->push_back(*first);
            }
        }
        void assign(size_type n, const value_type &u
          , typename ft::enable_if<ft::is_integral<size_type>::value, size_type>::type * = 0){
            if (this->_capa < n)
                this->reserve(n);

            for (int i = 0; i < n; i++)
                this->_alloc.construct(&this->_begin[this->_size], u);
                
        }
        void push_back(const value_type &x){
            if(capacity() <= size())
                reserve(capacity() * 2);

            this->_alloc.construct(&this->_begin[this->_size], x);
            this->_size++;
        }

        void pop_back(){
            if(empty())
                return;
            this->_size--;
            this->_alloc.destroy(&this->_begin[this->_size - 1]);
        }

        iterator insert(iterator position, const value_type &x){
            // find iter index
            insert( position, 1, x);
            return position;
        }
        void insert(iterator position, size_type n, const value_type &x
          , typename ft::enable_if<ft::is_integral<size_type>::value, size_type>::type * = 0
          )
        {
            // find iter index
            size_type start = position.base() - this->_begin;

            if (size() + n >= capacity())
                reserve(capacity() + n);

            // move data to back
            for (size_type i = size() - 1; i >= start; i--)
            {
                this->_alloc.destroy(&this->_begin[i + n]);
                this->_alloc.construct(&this->_begin[i + n], this->_begin[i]);
            }

            // push new values
            for (size_type i = start; i < start + n; i++)
            {
                this->_alloc.destroy(&this->_begin[i]);
                this->_alloc.construct(&this->_begin[i], x);
            }
            this->_size += n;
        }
        // TODO: enable if 추가
        template <class InputIterator>    
        void insert (iterator position, InputIterator first, InputIterator last
                      , typename ft::enable_if<!ft::is_integral<InputIterator>::value>::type * = 0
        
        ){
            size_type n = last - first;
            // find iter index
            size_type start = position.base() - this->_begin;
            
            if (size() + n >= capacity())
                reserve(capacity() + n);

            // move data to back
            for (size_type i = size() - 1; i >= start; i--)
            {
                this->_alloc.destroy(&this->_begin[i + n]);
                this->_alloc.construct(&this->_begin[i + n], this->_begin[i]);
            }

            // push new values
            for (size_type i = start; i < start + n; i++, first++)
            {
                this->_alloc.destroy(&this->_begin[i]);
                this->_alloc.construct(&this->_begin[i], *first);
            }
            this->_size += n;
        };

        iterator erase(const_iterator position){
           return erase(position, position + 1);

        }
        iterator erase(const_iterator first, const_iterator last){

            size_type idx = first.base() - this->_begin;
            size_type len = last.base()  - first.base() ;

            for (; this->_begin  + len + idx < this->end().base(); idx++)
                *(this->_begin + idx) = *(this->_begin + idx + len);

            for (; len > 0; len--) {
                this->pop_back();
            }
            
            return this->_begin + idx;
        }
        void clear(){
            for (size_type i = 0; i < this->_size; i++)
                this->_alloc.destroy(&this->_begin[i]);
            this->_size = 0;
        }

        void resize(size_type sz, const value_type &c = value_type()){
            if(sz > capacity())
                reserve(sz);
                
            for(; size()< sz ; this->_size++){
                this->_alloc.destroy(&this->_begin[size()]);
                this->_alloc.construct(&this->_begin[size()],c);
            }
            this->_size = sz;
        }

        void swap(vector &v)
        {
            pointer tmpBegin = this->_begin;
            allocator_type tmpAlloc = this->_alloc;
            size_type tmpSize = this->_size;
            size_type tmpCapa = this->_capa;

            this->_begin = v._begin;
            this->_alloc = v._alloc;
            this->_size = v._size;
            this->_capa = v._capa;

            v._begin = tmpBegin;
            v._alloc = tmpAlloc;
            v._size = tmpSize;
            v._capa = tmpCapa;
        }
        allocator_type get_allocator() const{
            return this->_alloc;
        };


    };

    // template <class InputIterator, class Allocator = std::allocator<typename iterator_traits<InputIterator>::value_type> >
    // vector(InputIterator, InputIterator, Allocator = Allocator())
    //     -> vector<typename iterator_traits<InputIterator>::value_type, Allocator>;


    template <class T, class Allocator>
    bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y){
        if (x._size != y._size) 
            return (false);
        
        for (typename vector<T, Allocator>::size_type i = 0; i < x._size; i++) {
            if (x[i] != y[i]) 
                return (false);
        }

        return (true);

    }
    template <class T, class Allocator>
    bool operator<(const vector<T, Allocator> &x, const vector<T, Allocator> &y){

        return ft::lexicographical_compare(x.begin(), x.end(), y.begin(), y.end());
    }
    template <class T, class Allocator>
    bool operator!=(const vector<T, Allocator> &x, const vector<T, Allocator> &y){
        return !(x == y);
    }
    template <class T, class Allocator>
    bool operator>(const vector<T, Allocator> &x, const vector<T, Allocator> &y){
        return ft::lexicographical_compare(y.begin(), y.end(), x.begin(), x.end());
    }
    template <class T, class Allocator>
    bool operator>=(const vector<T, Allocator> &x, const vector<T, Allocator> &y){
        return !(x < y);
    }
    template <class T, class Allocator>
    bool operator<=(const vector<T, Allocator> &x, const vector<T, Allocator> &y){
        return !(x > y);
    }

    template <class T, class Allocator>
    void swap(vector<T, Allocator> &x, vector<T, Allocator> &y){
        x.swap(y);
    }
}

#endif