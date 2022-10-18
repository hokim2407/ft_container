#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include <map>
// #include <deque>
// #include <iterator>
// #include <map>
#include <vector>
// #include <algorithm>

void printAll(std::map<std::string, int> &std_m, ft::map<std::string, int> &ft_m, std::string header = "")
{

    std::cout << "=====" << header << "=====" << std::endl;

    std::cout << "std === size: " << std_m.size() << ", max_size:" << std_m.max_size() << std::endl;

    std::cout << "ft === size: " << ft_m.size() << ", max_size:" << ft_m.max_size() << std::endl;
    ft::map<std::string, int>::iterator ft_iter1 = ft_m.begin();
    std::map<std::string, int>::iterator iter1 = std_m.begin();
    std::cout << "\tstd\t|\tft\t|"<<std::endl;
    std::cout << "\t---\t|\t---\t|"<<std::endl;
        
    for (; ft_iter1 != ft_m.end(); ft_iter1++)
    {
        std::cout << "\t"<< iter1->first << ":" << iter1->second <<"\t|" ;
        std::cout << "\t"<< ft_iter1->first << ":" << ft_iter1->second <<"\t|"<<std::endl;
        iter1++;
    }


    std::map<std::string, int>::reverse_iterator iter = std_m.rbegin();
    std::cout << "\tstd\t|\tft\t|"<<std::endl;
    std::cout << "\t---\t|\t---\t|"<<std::endl;
        
    for (ft::map<std::string, int>::reverse_iterator ft_iter = ft_m.rbegin(); ft_iter != ft_m.rend(); ft_iter++)
    {
        std::cout << "\t"<< iter->first << ":" << iter->second <<"\t|" ;
        std::cout << "\t"<< ft_iter->first << ":" << ft_iter->second <<"\t|"<<std::endl;
        iter++;
    }
    std::cout << "-" << std::endl;
}

void test()
{
    std::map<std::string, int> std_m = std::map<std::string, int>();
    ft::map<std::string, int> ft_m = ft::map<std::string, int>();
    printAll(std_m, ft_m, "create ");

    std_m.insert(std::pair<std::string, int>("b", 2));
    ft_m.insert(ft::pair<std::string, int>("b", 2));
    printAll(std_m, ft_m, "insert (\"b\",2) ");

    std_m.insert(std::pair<std::string, int>("d", 4));
    ft_m.insert(ft::pair<std::string, int>("d", 4));
    printAll(std_m, ft_m, "insert (\"d\",4) ");

    std_m.insert(std::pair<std::string, int>("a", 12));
    ft_m.insert(ft::pair<std::string, int>("a", 12));
    printAll(std_m, ft_m, "insert (\"a\",12) ");

    std_m.insert(std::pair<std::string, int>("c", 10));
    ft_m.insert(ft::pair<std::string, int>("c", 10));
    printAll(std_m, ft_m, "insert (\"c\",10) ");

    std_m.insert(std::pair<std::string, int>("e", 20));
    ft_m.insert(ft::pair<std::string, int>("e", 20));
    printAll(std_m, ft_m, "insert (\"e\",20) ");
    std_m.insert(std::pair<std::string, int>("g", 21));
    ft_m.insert(ft::pair<std::string, int>("g", 21));
    printAll(std_m, ft_m, "insert (\"g\",21) ");
    std_m.insert(std::pair<std::string, int>("f", 8));
    ft_m.insert(ft::pair<std::string, int>("f", 8));
    printAll(std_m, ft_m, "insert (\"f\",8) ");
    std_m.erase("b");
    ft_m.erase("b");
    printAll(std_m, ft_m, "erase (\"b\") ");
    std_m.erase("f");
    ft_m.erase("f");
    printAll(std_m, ft_m, "erase (\"f\") ");
    std::cout << "std: " << std_m.find("g")->first << ", ft: " << ft_m.find("g")->first;
    return;
}
#include <string> 
template <class T>
std::vector<T> copy_constructor_test1() {
    std::map<T, T> mp;
    std::vector<T> v;

    for (int i = 0, j = 10; i < 30 ; ++i, ++j) {
        mp.insert(std::make_pair(std::to_string(i), std::to_string(j)));
    }
    typename std::map<T, T> mp2(mp.begin(), mp.end());
    typename std::map<T, T>::iterator it = mp2.begin();
    for (int i = 0; i < 30 ; ++i, it++) {
        std::cout<< (it->first)<<":"<< (it->second) << std::endl;
        // v.push_back(it->first);
        // v.push_back(it->second);
    }
    return v;
}

template <class T>
std::vector<T> copy_constructor_test2() {
    typedef typename ft::map<T, T>::iterator iterator;
    ft::map<T,T> mp;
    std::vector<T> v;
   iterator it;
    for (int i = 0, j = 10; i < 30 ; ++i, ++j) {
        std::cout<<"in:"<<i<< std::endl;
        ft::pair<T,T> temp =  ft::make_pair(std::to_string(i), std::to_string(j));
        std::cout<< (temp.first)<<":"<< (temp.second) << std::endl;
        ft::pair<iterator ,bool>  result  = mp.insert(temp);
        std::cout<<"last:"<< (result.first->first)<<":"<< (result.second) << std::endl;
   
    }
    typename ft::map<T, T> mp2(mp.begin(), mp.end());
    it = mp2.begin();
    for (int i = 0; i < 30 ; ++i, it++) {
        std::cout<< (it->first)<<":"<< (it->second) << std::endl;
    }
    return v;
}

std::vector<int> copy_constructor_test() {
    ft::map<int, int> mp;
    std::vector<int> v;

    for (int i = 0, j = 10; i < 30 ; ++i, ++j) {
        mp.insert(ft::make_pair(i, j));
    }
    ft::map<int, int> mp2(mp.begin(), mp.end());
    ft::map<int, int>::iterator it = mp2.begin();
    for (int i = 0; i < 30 ; ++i, it++) {
        v.push_back(it->first);
        v.push_back(it->second);
    }
    return v;
}

int main()
{
    //std::vector<std::string > res1 =  copy_constructor_test1<std::string>();
    //     std::cout<< "====" << std::endl;
    //  std::vector<std::string > res2 = copy_constructor_test2<std::string>();

 copy_constructor_test();
    std::cout << 123 << std::endl;
    //std::cout << (res1 ==res2) << std::endl;
    return 0;
}