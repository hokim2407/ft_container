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

#include "deque.hpp"

namespace ft
{

    template <class T, class Container = deque<T>>
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
        stack() = default;
        ~stack() = default;

        stack(const stack& q) = default;
        stack(stack&& q) = default;

        stack& operator=(const stack& q) = default;
        stack& operator=(stack&& q) = default;

        explicit stack(const container_type& c);
        explicit stack(container_type&& c);
        template <class Alloc> explicit stack(const Alloc& a);
        template <class Alloc> stack(const container_type& c, const Alloc& a);
        template <class Alloc> stack(container_type&& c, const Alloc& a);
        template <class Alloc> stack(const stack& c, const Alloc& a);
        template <class Alloc> stack(stack&& c, const Alloc& a);

        bool empty() const;
        size_type size() const;
        reference top();
        const_reference top() const;

        void push(const value_type& x);
        void push(value_type&& x);
        void pop();

    };

    template<class Container>
    stack(Container) -> stack<typename Container::value_type, Container>;  // C++17

    template<class Container, class Allocator>
    stack(Container, Allocator) -> stack<typename Container::value_type, Container>; // C++17

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

    template <class T, class Container>
    void swap(stack<T, Container>& x, stack<T, Container>& y)
    noexcept(noexcept(x.swap(y)));

}  // std

