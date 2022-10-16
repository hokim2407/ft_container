#include "map.hpp"
#include "pair.hpp"
#include <iostream>
#include <map>
// #include <deque>
// #include <iterator>
// #include <map>
// #include <stack>
// #include <algorithm>

void printAll(std::map<std::string, int> &std_m, ft::map<std::string, int> &ft_m, std::string header = "")
{

    std::cout << "=====" << header << "=====" << std::endl;

    std::cout << "std === size: " << std_m.size() << ", max_size:" << std_m.max_size() << std::endl;

    std::cout << "ft === size: " << ft_m.size() << ", max_size:" << ft_m.max_size() << std::endl;
    ft::map<std::string, int>::iterator ft_iter = ft_m.begin();
    std::cout << "\tstd\t|\tft\t|"<<std::endl;
    std::cout << "\t---\t|\t---\t|"<<std::endl;
        
    for (std::map<std::string, int>::iterator iter = std_m.begin(); iter != std_m.end(); iter++)
    {
        std::cout << "\t"<< iter->first << ":" << iter->second <<"\t|" ;
        std::cout << "\t"<< ft_iter->first << ":" << ft_iter->second <<"\t|"<<std::endl;
        ft_iter++;
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
int main()
{
    test();
    while(1);
    return 0;
}