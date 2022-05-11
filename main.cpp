#include "vector.hpp"
#include <iostream>
// #include <deque>
// #include <iterator>
// #include <map>
// #include <stack>
// #include <algorithm>
void test (){
    ft::vector<int> *vec = new ft::vector<int>(5,5);
    vec->reserve(7);
    std::cout << vec->size() << ", " << vec->capacity() << ", " << vec->max_size() << std::endl ;
    std::cout << vec->empty() << std::endl ;
    vec->push_back(1);
    vec->push_back(2);
    std::cout <<"after push: "<< vec->empty() << std::endl ;
    std::cout <<"after push: "<< vec->back() << std::endl ;
    delete (vec);
    return;
}
int main (){
    test();
    return 0;
}