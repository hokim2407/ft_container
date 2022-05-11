// -*- C++ -*-
//===----------------------------- map ------------------------------------===//
//
// Part of the LLVM Project, under the Apache License v2.0 with LLVM Exceptions.
// See https://llvm.org/LICENSE.txt for license information.
// SPDX-License-Identifier: Apache-2.0 WITH LLVM-exception
//
//===----------------------------------------------------------------------===//

#ifndef _LIBCPP_MAP
#define _LIBCPP_MAP

namespace ft
{

    template <class Key, class T, class Compare = less<Key>,
              class Allocator = allocator<pair<const Key, T> > >
    class map
    {
    public:
        // types:
        typedef Key key_type;
        typedef T mapped_type;
        typedef pair<const key_type, mapped_type> value_type;
        typedef Compare key_compare;
        typedef Allocator allocator_type;
        typedef typename allocator_type::reference reference;
        typedef typename allocator_type::const_reference const_reference;
        typedef typename allocator_type::pointer pointer;
        typedef typename allocator_type::const_pointer const_pointer;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

        typedef pointer iterator;
        typedef const_pointer const_iterator;
        typedef ft::reverse_iterator<iterator> reverse_iterator;
        typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
        typedef unspecified node_type;                                      // C++17
        typedef INSERT_RETURN_TYPE<iterator, node_type> insert_return_type; // C++17

        class value_compare
            : public binary_function<value_type, value_type, bool>
        {
            friend class map;

        protected:
            key_compare comp;

            value_compare(key_compare c);

        public:
            bool operator()(const value_type &x, const value_type &y) const;
        };

        // construct/copy/destroy:
        map()
            noexcept(
                is_nothrow_default_constructible<allocator_type>::value &&
                    is_nothrow_default_constructible<key_compare>::value &&
                        is_nothrow_copy_constructible<key_compare>::value);
        explicit map(const key_compare &comp);
        map(const key_compare &comp, const allocator_type &a);
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp = key_compare());
        template <class InputIterator>
        map(InputIterator first, InputIterator last,
            const key_compare &comp, const allocator_type &a);
        map(const map &m);
        map(map &&m)
            noexcept(
                is_nothrow_move_constructible<allocator_type>::value &&
                    is_nothrow_move_constructible<key_compare>::value);
        explicit map(const allocator_type &a);
        map(const map &m, const allocator_type &a);
        map(map &&m, const allocator_type &a);
        map(initializer_list<value_type> il, const key_compare &comp = key_compare());
        map(initializer_list<value_type> il, const key_compare &comp, const allocator_type &a);
        template <class InputIterator>
        map(InputIterator first, InputIterator last, const allocator_type &a)
            : map(first, last, Compare(), a) {} // C++14
        map(initializer_list<value_type> il, const allocator_type &a)
            : map(il, Compare(), a) {} // C++14
        ~map();

        map &operator=(const map &m);
        map &operator=(map &&m)
            noexcept(
                allocator_type::propagate_on_container_move_assignment::value &&
                    is_nothrow_move_assignable<allocator_type>::value &&
                        is_nothrow_move_assignable<key_compare>::value);
        map &operator=(initializer_list<value_type> il);

        // iterators:
        iterator begin() noexcept;
        const_iterator begin() const noexcept;
        iterator end() noexcept;
        const_iterator end() const noexcept;

        reverse_iterator rbegin() noexcept;
        const_reverse_iterator rbegin() const noexcept;
        reverse_iterator rend() noexcept;
        const_reverse_iterator rend() const noexcept;

        // capacity:
        bool empty() const noexcept;
        size_type size() const noexcept;
        size_type max_size() const noexcept;

        // element access:
        mapped_type &operator[](const key_type &k);
        mapped_type &operator[](key_type &&k);

        // modifiers:
        pair<iterator, bool> insert(const value_type &v);
        pair<iterator, bool> insert(value_type &&v); // C++17
        template <class P>
        pair<iterator, bool> insert(P &&p);
        iterator insert(const_iterator position, const value_type &v);
        iterator insert(const_iterator position, value_type &&v); // C++17
        template <class P>
        iterator insert(const_iterator position, P &&p);
        template <class InputIterator>
        void insert(InputIterator first, InputIterator last);
        void insert(initializer_list<value_type> il);

        node_type extract(const_iterator position);           // C++17
        node_type extract(const key_type &x);                 // C++17
        insert_return_type insert(node_type &&nh);            // C++17
        iterator insert(const_iterator hint, node_type &&nh); // C++17

         pair<iterator, bool> insert_or_assign(const key_type &k, M &&obj); // C++17
        template <class M>
        pair<iterator, bool> insert_or_assign(key_type &&k, M &&obj); // C++17
        template <class M>
        iterator insert_or_assign(const_iterator hint, const key_type &k, M &&obj); // C++17
        template <class M>
        iterator insert_or_assign(const_iterator hint, key_type &&k, M &&obj); // C++17

        iterator erase(const_iterator position);
        iterator erase(iterator position); // C++14
        size_type erase(const key_type &k);
        iterator erase(const_iterator first, const_iterator last);
        void clear() noexcept;

        template <class C2>
        void merge(map<Key, T, C2, Allocator> &source); // C++17
        template <class C2>
        void merge(map<Key, T, C2, Allocator> &&source); // C++17
        template <class C2>
        void merge(multimap<Key, T, C2, Allocator> &source); // C++17
        template <class C2>
        void merge(multimap<Key, T, C2, Allocator> &&source); // C++17

        void swap(map &m);

        // observers:
        allocator_type get_allocator() const noexcept;
        key_compare key_comp() const;
        value_compare value_comp() const;

        // map operations:
        iterator find(const key_type &k);
        const_iterator find(const key_type &k) const;
        template <typename K>
        iterator find(const K &x); // C++14
        template <typename K>
        const_iterator find(const K &x) const; // C++14
        template <typename K>
        size_type count(const K &x) const; // C++14
        size_type count(const key_type &k) const;
        bool contains(const key_type &x) const; // C++20
        iterator lower_bound(const key_type &k);
        const_iterator lower_bound(const key_type &k) const;
        template <typename K>
        iterator lower_bound(const K &x); // C++14
        template <typename K>
        const_iterator lower_bound(const K &x) const; // C++14

        iterator upper_bound(const key_type &k);
        const_iterator upper_bound(const key_type &k) const;
        template <typename K>
        iterator upper_bound(const K &x); // C++14
        template <typename K>
        const_iterator upper_bound(const K &x) const; // C++14

        pair<iterator, iterator> equal_range(const key_type &k);
        pair<const_iterator, const_iterator> equal_range(const key_type &k) const;
        template <typename K>
        pair<iterator, iterator> equal_range(const K &x); // C++14
        template <typename K>
        pair<const_iterator, const_iterator> equal_range(const K &x) const; // C++14
    };

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator==(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator<(const map<Key, T, Compare, Allocator> &x,
              const map<Key, T, Compare, Allocator> &y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator!=(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator>(const map<Key, T, Compare, Allocator> &x,
              const map<Key, T, Compare, Allocator> &y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator>=(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y);

    template <class Key, class T, class Compare, class Allocator>
    bool
    operator<=(const map<Key, T, Compare, Allocator> &x,
               const map<Key, T, Compare, Allocator> &y);

    // specialized algorithms:
    template <class Key, class T, class Compare, class Allocator>
    void
    swap(map<Key, T, Compare, Allocator> &x, map<Key, T, Compare, Allocator> &y)
        noexcept(noexcept(x.swap(y)));

    template <class Key, class T, class Compare, class Allocator, class Predicate>
    void erase_if(map<Key, T, Compare, Allocator> &c, Predicate pred); // C++20

    
}

#endif 