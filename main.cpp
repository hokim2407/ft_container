#include "vector.hpp"
#include <iostream>
#include <vector>
// #include <deque>
// #include <iterator>
// #include <map>
// #include <stack>
// #include <algorithm>



void test (){
    std::vector<int> v (5,5);
    std::cout <<"1"<< std::endl ;
    ft::vector<int> vec(v.begin(),v.end());
    vec[4] = 8;
    std::cout <<"2"<< std::endl ;
    std::cout << vec.size() << ", " << vec.capacity() << ", " << vec.max_size() << std::endl ;
    std::cout << vec.empty() << std::endl ;
    vec.push_back(1);
    vec.push_back(2);
    std::cout << vec.size()<<"=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;
    vec.insert(vec.begin()+3,6);

    std::cout << vec.size()<<"=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;
    std::cout <<"val: "<< v[4] <<  ", "<< vec[4] <<std::endl ;
    std::cout <<"after push: "<< vec.back() << std::endl ;
    std::cout << vec.size()<<"val: "<< vec[4] << ", " << vec.capacity() << ", " << vec.max_size() << std::endl ;
    std::cout << vec.size()<<"=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;
    vec.erase(vec.begin()+2,vec.begin()+4);
    std::cout << vec.size()<<"=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;


    vec.resize(3);
    std::cout << vec.size()<<" resize 3=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;

    vec.resize(10);
    std::cout << vec.size()<<" resize 10=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;


    ft::vector<int> vec2(v.begin(), v.end());
    vec2.push_back(7);
    vec2.push_back(8);
    vec.swap(vec2);
    std::cout << vec.size()<<"=====" << std::endl ;
    for(unsigned  long i = 0; i < vec.size(); i++)
        std::cout << vec[i] << std::endl ;
    std::cout << vec2.size()<<": vec2=====" << std::endl ;
    for(unsigned  long i = 0; i < vec2.size(); i++)
        std::cout << vec2[i] << std::endl ;

    return;
}
int main (){
    test();

    return 0;
}