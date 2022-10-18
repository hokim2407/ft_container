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
    
    std::cout<<"std === size: " << v.size() << ", capa:" << v.size() << ", max_size:"<< v.max_size()<< std::endl ;
    
    std::cout<<"ft === size: " << vec.size() << ", capa:" << vec.size() << ", max_size:"<< vec.max_size() << std::endl ;

    ft::vector<int>::iterator iter1= vec.begin();
    std::vector<int>::iterator it1= v.begin();
    for(; iter1 !=  vec.end(); iter1++){
            std::cout << "std: "<< *it1;
            std::cout << ", ft: "<< *iter1 << std::endl ;
        it1++;
    }

    std::cout<<"-"<< std::endl ;
    ft::vector<int>::reverse_iterator iter= vec.rbegin();
    std::vector<int>::reverse_iterator it= v.rbegin();
    for(; iter !=  vec.rend(); iter++){
            std::cout << "std: "<< *it;
            std::cout << ", ft: "<< *iter << std::endl ;
        it++;
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
    std::cout<< ". "<<  vec.size()<<std::endl;
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

    
    std::cout<<"ft == ft2: " << (v == v2)<< std::endl ;
    std::cout<<"ft != ft2: " << (v != v2)<< std::endl ;
    std::cout<<"ft < ft2: " << (v < v2)<< std::endl ;
    std::cout<<"ft > s: " << (v > v2)<< std::endl ;
    std::cout<<"ft <= std: " << (v <= v2)<< std::endl ;
    std::cout<<"ft >= std: " << (v >= v2)<< std::endl ;

    return;
}
#include <sstream>

void printStdV (std::vector<int> v){
   typedef typename  std::vector<int>::iterator iterator;
    iterator start = v.begin();
    std::cout<< "===std===" << std::endl;
    for(;start != v.end();start ++)
    std::cout<< *start << std::endl;

}
void printFtV (ft::vector<int> v){
   typedef typename  ft::vector<int>::iterator iterator;
    iterator start = v.begin();
    std::cout<< "===ft===" << std::endl;
    for(;start != v.end();start ++)
    std::cout<< *start << std::endl;

}



std::vector<int> assign_test1() {
 //  typedef typename  std::vector<int>::iterator iterator;
    std::vector<int> vector;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    v.push_back(*(vector.erase(vector.begin() + 8)));
    v.push_back(*(vector.begin() + 4));
    v.push_back(vector.size());
    v.push_back(vector.size());
    std::cout<<"*"<< vector.size() << std::endl;
    printStdV(vector);
    return v;
}

std::vector<int> assign_test2() {
 // typedef typename  ft::vector<int>::iterator iterator;
    ft::vector<int> vector;
    std::vector<int> v;
    for (int i = 0; i < 10; ++i)
        vector.push_back(i);
    v.push_back(*(vector.erase(vector.begin() + 8)));
 
    v.push_back(*(vector.begin() + 4));
    v.push_back(vector.size());
    v.push_back(vector.size());
    std::cout<<"*"<< vector.size() << std::endl;
    printFtV(vector);
    return v;
}
void assign_test3() {
    std::vector<int> vector;
    vector.assign(1000, 1);
    vector.insert(vector.end() - 50, 4200 , 2);    
    std::vector<int>::iterator iter = vector.begin();

    ft::vector<int> v;
    v.assign(1000, 1);
    v.insert(v.end() - 50, 4200 , 2);    
    ft::vector<int>::iterator iter2 = v.begin();


    int count = 1;
    for(; iter!= vector.end(); iter++){
        if(*iter != *iter2)
            std::cout <<count<< " std: " << *iter<< " " << *iter2 << std::endl;
        iter2 ++;
        count ++;
    }
            std::cout <<count<< " std: " << vector.size()<< " " << v.size() << std::endl;
}

int main (){
    //test();
     std::vector<int > res1 =  assign_test1();
     std::vector<int > res2 = assign_test2();


    std::cout << "===" << std::endl;
    std::cout << (res1 ==res2) << std::endl;

    return 0;
}