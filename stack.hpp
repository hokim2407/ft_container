// -*- C++ -*-
//===---------------------------- stack -----------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_STACK
#define _LIBCPP_STACK

#include "vector.hpp"

namespace ft
{

    template <class T, class Container = vector<T>>
    class stack
    {
    public:
        typedef Container                                container_type;
        typedef typename container_type::value_type      value_type;
        typedef typename container_type::reference       reference;
        typedef typename container_type::const_reference const_reference;
        typedef typename container_type::size_type       size_type;

    protected:
        container_type c;

    public:
        stack(){
            c = container_type();
        };
        ~stack(){};

        stack(const stack& q){
            *this = q;
        }

        explicit stack(container_type&& c){
            this->c = c;
        }

        stack& operator=(const stack& q) {
            this->c = q.c;
            return *this;
        };

        bool empty() const{
            return this->c.empty();
        }
        size_type size() const{
            return this->c.size();
        }
        reference top(){
            return this->c.back();
        }
        const_reference top() const{
            return this->c.back();
        }

        void push(const value_type& x){
            return this->c.push_back(x);
        }
        void push(value_type&& x){
            return this->c.push_back(x);
        }
        void pop()
        {
            c.pop_back();
        };

    };


    template <class T, class Container>
    bool operator==(const stack<T, Container>& x, const stack<T, Container>& y);
    template <class T, class Container>
    bool operator< (const stack<T, Container>& x, const stack<T, Container>& y);
    template <class T, class Container>
    bool operator!=(const stack<T, Container>& x, const stack<T, Container>& y);
    template <class T, class Container>
    bool operator> (const stack<T, Container>& x, const stack<T, Container>& y);
    template <class T, class Container>
    bool operator>=(const stack<T, Container>& x, const stack<T, Container>& y);
    template <class T, class Container>
    bool operator<=(const stack<T, Container>& x, const stack<T, Container>& y);


} 

#endif 
