#include "avl.hpp"

int main (){
    ft::Tree<int, std::string> *mytree = new ft::Tree<int, std::string>(true);
    for (int i = 0; i <20; i++){
    mytree->insert(ft::pair<int,std::string>(i,"abc"));
    }
    std::cout<< (mytree->search(mytree->root, 3))->data.first<<std::endl;
    mytree->remove(9);
    mytree->remove(8);
    mytree->remove(10);
    mytree->remove(0);

    return 0;
}