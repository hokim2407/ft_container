#include "vector.hpp"
#include <iostream>
#include <vector>
// #include <deque>
// #include <iterator>
// #include <map>
// #include <stack>
// #include <algorithm>

void printAll(std::vector<int>& v ,ft::vector<int> &vec , std::string header = ""){
    
    std::cout<<"=====" << header <<"=====" <<std::endl ;
    
    std::cout<<"std === size: " << v.size() << ", capa:" << v.capacity() << ", max_size:"<< v.max_size()<< std::endl ;
    
    std::cout<<"ft === size: " << vec.size() << ", capa:" << vec.capacity() << ", max_size:"<< vec.max_size() << std::endl ;
    
    for(unsigned  long i = 0; i < v.size(); i++){
            std::cout << "std: "<< v[i];
        if (i < vec.size())
            std::cout << ", ft: "<< vec[i] << std::endl ;
        else 
            std::cout << "ft: - " << std::endl ;
        }
    std::cout<<"-"<< std::endl ;
}


void test (){
    std::vector<int> v (5,5);
    ft::vector<int> vec(v.begin(),v.end());
    printAll(v, vec, "create (5,5)");
    vec[4] = 8;
    v[4] = 8;
    printAll(v, vec, "v[4] = 8");

    vec.push_back(1);
    vec.push_back(2);

    v.push_back(1);
    v.push_back(2);
    printAll(v, vec, "push 1 and 2");

    vec.insert(vec.begin()+3,6);
    v.insert(v.begin()+3,6);
    printAll(v, vec,"insert (v.begin()+3,6)");

    vec.insert(vec.begin()+3,6);
    v.insert(v.begin()+3,6);
    printAll(v, vec,"insert (v.begin()+3,6)");
    vec.insert(vec.begin()+3,6);
    v.insert(v.begin()+3,6);
    printAll(v, vec,"insert (v.begin()+3,6)");
    vec.erase(vec.begin()+2,vec.begin()+4);
    v.erase(v.begin()+2,v.begin()+4);
    printAll(v, vec,"erase(vec.begin()+2,vec.begin()+4)");


    vec.resize(3);
    v.resize(3);
    printAll(v, vec, "resize(3)");

    vec.resize(10);
    v.resize(10);
    printAll(v, vec,"resize(10)" );

    vec.pop_back();
    v.pop_back();
    printAll(v, vec, "pop");

    vec.reserve(12);
    v.reserve(12);
    std::cout<< ". "<<  vec.capacity()<<std::endl;
    printAll(v, vec, "reserve");

    ft::vector<int> vec2(v.begin(), v.end());
    std::vector<int> v2(v.begin(), v.end());
    vec2.push_back(7);
    vec2.push_back(8);
    v2.push_back(7);
    v2.push_back(8);
    printAll(v, vec, "ori vec1");
    printAll(v2, vec2, "ori vec2 = cp vec1 and push 7,8");
    vec.swap(vec2);
    v.swap(v2);
    printAll(v, vec, "swaped vec1");
    printAll(v2,vec2, "swaped vec2");

    return;
}
int main (){
    test();

    return 0;
}