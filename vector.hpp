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

        typedef ft::reverse_iterator<T> reverse_iterator;
        typedef ft::const_reverse_iterator<T> const_reverse_iterator;

        private:

            pointer                                             _begin;
            pointer                                             _end;
            size_type                                           _size;
            size_type                                           _capacity;
            allocator_type                                      _alloc;

        void _init(size_type n){
            this->_capacity = n;
            this->_begin = this->_alloc.allocate(capacity());
            this->_end = this->_begin + capacity();
            //*(this->_end) = 0;
            this->_size = 0;
        }

        public:


        // construct/copy/destroy:
        vector(){
            _init(128);
        }
        explicit vector(const allocator_type & alloc){
            this->_alloc = alloc;
            _init(128);
        }

        explicit vector(size_type n){
            _init(n);
        }

        vector(size_type n, const value_type &value, const allocator_type & alloc = allocator_type())
        :  _capacity(n){
            this->_alloc = alloc;
            _init(n);

            for (; size()< capacity(); this->_size++)
                *(this->_begin + size()) = value;
        }

        template <class InputIterator>
        vector(InputIterator first, InputIterator last, const allocator_type & alloc = allocator_type()){
            this->_capacity = 0;
            this->_alloc = alloc;
            assign(first, last);
        }

        vector(const vector &x){
            assign(x.begin(), x.end());
        }

        ~vector(){
            //std::destroy(this->_begin, this->_end);
            // deallocate
            this->_alloc.deallocate(this->_begin, capacity());
        }

        vector &operator=(const vector &x){    
            this->_capacity = x.capacity();
            assign(x.begin(), x.end());
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
            return  iterator(this->_end);
         }
        const_iterator end() const {

            return const_iterator(this->_end);
         }

        reverse_iterator rbegin() {

            return  reverse_iterator(this->_end);
        }
        const_reverse_iterator rbegin() const {
            
            return  const_reverse_iterator(this->_end);
        }
        reverse_iterator rend() {
            
            return  reverse_iterator(this->_end);
        }
        const_reverse_iterator rend() const {
            
            return  const_reverse_iterator(this->_end);
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
            return this->_capacity;
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
            _init(n);

            
            for(;  size() < ori_size; this->_size++ )
                *(this->_begin + size()) = *(ori_begin + size());

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
                return *(this->_end);
            return *(this->_begin + n);
        }
        const_reference at(size_type n) const{
            return at(n);
        }

        reference front(){
            return *(this->_begin);
        }
        const_reference front() const{
            return *(this->_begin);
        }
        reference back(){
            return *(this->_begin + size()-1);
        }
        const_reference back() const{
            return *(this->_begin + size()-1);
        }


        // // modifiers:
        // TODO: enable if
        template <class InputIterator>
        void assign(InputIterator first, InputIterator last){

           size_type idx = 0;
            for (; first + idx < last; idx++);
            
            if(idx > capacity())
                _init(idx);

            for (; first != last; first++){
                *(this->_begin + size()) = *first;
                this->_size ++;
            }
        }
        void assign(size_type n, const value_type &u){
            if(n > capacity())
                _init(n);

            for (; size()<n; this->_size++)
                *(this->_begin + size()) = u;
        }
        void push_back(const value_type &x){
            if(capacity() <= size())
                reserve(capacity() * 2);
                
            *(this->_begin + size()) = x;
            this->_size++;
        }

        void pop_back(){
            if(empty())
                return;
            this->_size--;
        }

        iterator insert(const_iterator position, const value_type &x){
            
            return insert( position, 1, x);
        }
        iterator insert(const_iterator position, size_type n, const value_type &x){
            size_type idx = 0;
            // find iter index
            for (;this->_begin + idx < position.base(); idx ++) ;

            if(size()+n >= capacity())
                reserve(capacity() * 2);

            // move data to back
            for(size_type i = size(); i > idx ; i--){
                *(this->_begin + i + n) = *(this->_begin + i);
            }

            // push noew values
            for(size_type i = idx ; i < idx + n; i++, this->_size++)
                *(this->_begin + i) = x;
            return (this->_begin + idx);
        }

        iterator erase(const_iterator position){
           return erase(position, position + 1);

        }
        iterator erase(const_iterator first, const_iterator last){

            size_type idx = 0;
            for (; this->_begin + idx < first.base(); idx++)
                ;
            size_type len = 0;
            for (; first + len < last; len++)
                ;

            for (; this->_begin + idx < this->_end; idx++)
                *(this->_begin + idx) = *(this->_begin + idx + len);

            this->_size-=len;
            
            return this->_begin + idx;
        }

        void clear(){
            this->_size = 0;
        }

        void resize(size_type sz){
            resize(sz, 0);
        }
        void resize(size_type sz, const value_type &c){
            if(sz > capacity())
                reserve(sz);
                
            for(; size()< sz ; this->_size++){
                *(this->_begin + size()) = c;
            }
            this->_size = sz;
        }

        void swap(vector & v){
            if(v.capacity() < capacity())
                v.reserve(capacity());
            else if(v.capacity() > capacity())
                reserve(v.capacity());

            for(size_type i = 0; i < v.size() || i < size(); i++)
            {
                value_type temp = *(this->_begin + i);
                *(this->_begin + i) = *(v.begin() + i);
                v[i] = temp;
            }
            size_type temp_size =  size();
            resize(v.size());
            v.resize(temp_size);
        }
   
        allocator_type get_allocator() const {
            return this->_alloc;
        }
    };

    // template <class InputIterator, class Allocator = std::allocator<typename iterator_traits<InputIterator>::value_type> >
    // vector(InputIterator, InputIterator, Allocator = Allocator())
    //     -> vector<typename iterator_traits<InputIterator>::value_type, Allocator>;


    // template <class T, class Allocator>
    // bool operator==(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
    // template <class T, class Allocator>
    // bool operator<(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
    // template <class T, class Allocator>
    // bool operator!=(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
    // template <class T, class Allocator>
    // bool operator>(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
    // template <class T, class Allocator>
    // bool operator>=(const vector<T, Allocator> &x, const vector<T, Allocator> &y);
    // template <class T, class Allocator>
    // bool operator<=(const vector<T, Allocator> &x, const vector<T, Allocator> &y);

    // template <class T, class Allocator>
    // void swap(vector<T, Allocator> &x, vector<T, Allocator> &y)
    //     noexcept(noexcept(x.swap(y)));

}

#endif