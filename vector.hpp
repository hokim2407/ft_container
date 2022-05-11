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
        typedef pointer iterator;
        typedef const_pointer const_iterator;
        // typedef ft::reverse_iterator<iterator> reverse_iterator;
        // typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

        private:

            pointer                                             _begin;
            pointer                                             _end;
            size_type                                           _size;
            size_type                                           _capacity;
            allocator_type                                      _alloc;

        public:
        // construct/copy/destroy:
        vector():_capacity(128){

            this->_begin = this->_alloc.allocate(capacity());
            this->_end = this->_begin + capacity();
            std::cout<< "work"<<std::endl;
        }
        explicit vector(const allocator_type & alloc):_capacity(128){
            this->_begin = alloc.allocate(capacity());
            this->_end = this->_begin + capacity();
            std::cout<< "work"<<std::endl;
        }

        explicit vector(size_type n): _capacity(n){
            this->_begin = this->_alloc.allocate(capacity());
            this->_end = this->_begin + capacity();
            std::cout<< "work"<<std::endl;
        }

        vector(size_type n, const value_type &value, const allocator_type & alloc = allocator_type())
        :  _capacity(n){
            this->_alloc = allocator_type(alloc);
            this->_begin = _alloc.allocate(capacity());
            this->_end = this->_begin + capacity();
            std::cout<< "work"<<std::endl;

            for (; size()< capacity(); this->_size++){
                pointer p = this->_begin + size();
                *p = value;
            }

        }
        // template <class InputIterator>
        // vector(InputIterator first, InputIterator last, const allocator_type & = allocator_type());
        // vector(const vector &x);
        // vector(vector &&x)
        //     noexcept(is_nothrow_move_constructible<allocator_type>::value);
        // vector(initializer_list<value_type> il);
        // vector(initializer_list<value_type> il, const allocator_type &a);
        ~vector(){
            //std::destroy(this->_begin, this->_end);
            // deallocate
            this->_alloc.deallocate(this->_begin, capacity());
        }

        // vector &operator=(const vector &x);
        // vector &operator=(vector &&x)
        //     noexcept(
        //         allocator_type::propagate_on_container_move_assignment::value ||
        //         allocator_type::is_always_equal::value); // C++17
        // vector &operator=(initializer_list<value_type> il);


        // // iterators:
        // iterator begin() ;
        // const_iterator begin() const ;
        // iterator end() ;
        // const_iterator end() const ;

        // // reverse_iterator rbegin() ;
        // // const_reverse_iterator rbegin() const ;
        // // reverse_iterator rend() ;
        // // const_reverse_iterator rend() const ;

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
            this->_capacity = n;
            this->_begin = this->_alloc.allocate(capacity());
            this->_end = this->_begin + capacity();

            for(unsigned long i = 0; i < size(); i++ )
                {
                    pointer p = this->_begin + i;
                    *p = *(ori_begin + i);
                }

            this->_alloc.deallocate(ori_begin, capacity());
            
        }

        // // element access:
        // reference operator[](size_type n);
        // const_reference operator[](size_type n) const;
        // reference at(size_type n);
        // const_reference at(size_type n) const;

        reference front(){

            reference temp = *(this->_begin);
            return temp;
        }
        const_reference front() const{
            reference temp = *(this->_begin);
            return temp;
        }
        reference back(){
            reference temp = *(this->_begin + size()-1);
            return temp;
        }
        const_reference back() const{
            reference temp = *(this->_begin + size()-1);
            return temp;
        }


        // // modifiers:
        // template <class InputIterator>
        // void assign(InputIterator first, InputIterator last);
        // void assign(size_type n, const value_type &u);
        // void assign(initializer_list<value_type> il);

        void push_back(const value_type &x){
            if(capacity() <= size())
                return;//todo : 용량 두배로 늘려서 복사
                
            pointer p = this->_begin + size();
            *p = x;
            this->_size++;
        }
        // void push_back(value_type &&x);
        void pop_back(){
            if(empty())
                return;//todo : 용량 두배로 늘려서 복사
            this->_size--;
        }

        // iterator insert(const_iterator position, const value_type &x);
        // iterator insert(const_iterator position, value_type &&x);
        // iterator insert(const_iterator position, size_type n, const value_type &x);
        // template <class InputIterator>
        // iterator insert(const_iterator position, InputIterator first, InputIterator last);
        // iterator insert(const_iterator position, initializer_list<value_type> il);

        // iterator erase(const_iterator position);
        // iterator erase(const_iterator first, const_iterator last);

        // void clear() ;

        // void resize(size_type sz);
        // void resize(size_type sz, const value_type &c);

        // void swap(vector &);
   
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