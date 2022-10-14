
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "utils.hpp"
#include "pair.hpp"
namespace ft
{
    template <class T>
    class Node
    {
    public:
        T data;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        unsigned int height;
        bool isLeft;

    public:
        Node(T &d) : data(d)
        {
            left = NULL;
            right = NULL;
            height = 1;
        }
        Node(Node<T> *n)
        {
            setNode(n);
        }
        bool operator<(const Node<T> &n2)
        {
            return this->data < n2.data;
        };
        bool operator>(const Node<T> &n2)
        {
            return this->data > n2.data;
        };
        bool key(const Node<T> &n2)
        {
            return this->data > n2.data;
        };

        void setNode(Node<T> *n) 
        {
            data = n->data;
            left = n->left;
            right =n->right;
            parent =n->parent;
            height = n->height;
            isLeft = n->isLeft;
        }
        void setHeight()
        {
            unsigned int originalH = height;
            int leftH = left ? left->height : 0;
            int rightH = right ? right->height : 0;
            if (!left && !right)
                height = 1;
            else if (leftH > rightH)
                height = leftH + 1;
            else
                height = rightH + 1;

            if (parent != NULL && originalH != height)
                parent->setHeight();
        };
        void setLeft(Node<T> *n)
        {
            this->left = n;
            if (n)
            {
                n->parent = this;
                n->isLeft = true;
            }
            setHeight();
        };
        void setRight(Node<T> *n)
        {
            this->right = n;
            if (n)
            {
                n->parent = this;
                n->isLeft = false;
            }
            setHeight();
        };
        int bf()
        {
            int leftH = left ? left->height : 0;
            int rightH = right ? right->height : 0;
            return leftH - rightH;
        };
        Node* swap(Node* n)
        {
            //only data stap
            T temp = n->data;
            n->data = data;
            data = temp;

            return n;

        };
    };

    template <class Key,
              class T,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T>>>
    class Tree
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef ft::pair<Key, T> value_type;
        typedef Node<value_type> Node;

    public:
        Node *root;
        bool debugMode;
        Tree(bool debug = false) : root(NULL), debugMode(debug)
        {

            if (debugMode)
                std::cout << "in" << std::endl;
        };
        ~Tree(){};

    private:
        key_compare _compare;
        allocator_type _allocator;
        // typename allocator_type::template rebind<Node>::other _node_allocator;
    public:
        Node *findParent(Node *parentNode, Node *targetNode)
        {
            Node *nextPatent = NULL;
            if (*parentNode > *targetNode)
            {
                nextPatent = parentNode->left;
            }
            else if (*parentNode < *targetNode)
            {
                nextPatent = parentNode->right;
            }
            if (nextPatent == NULL)
                return parentNode;
            return findParent(nextPatent, targetNode);
        }
        void strRepeat(int count, std::string str)
        {
            for (int i = 0; i < count; i++)
                std::cout << str;
        }
        void print(Node *parentNode, std::string prefix = "")
        {
            if (parentNode == NULL)
                return;

            std::cout << prefix;

            std::cout << (parentNode->isLeft ? "└──" : "├──");
            std::string parent = "";
            // print the value of the node
            if(parentNode->parent)
                std::cout  <<"("<<(parentNode->parent->data.first) << "->) ";
            std::cout <<"\033[92m\033[1m"<< parentNode->data.first<< "\033[0m [" << parentNode->height << "]" << (parentNode->isLeft == true ? "L":"R") << std::endl;

            // enter the next tree level - left and right branch
            print(parentNode->right, prefix + (parentNode->isLeft == true ? "    " : "│   "));
            print(parentNode->left, prefix + (parentNode->isLeft == true ? "    " : "│   "));
        }
        void insert(value_type data)
        {
            if (debugMode)
                std::cout << "====== insert " << data.first << " ======" << std::endl;
            Node *newNode = new Node(data);
            if (root == NULL)
            {
                root = newNode;
                return;
            }
            Node *parnetNode = findParent(root, newNode);
            newNode->parent = parnetNode;

            if (*parnetNode > *newNode){
                parnetNode->setLeft(newNode);
                }
            else{
                parnetNode->setRight(newNode);
                }
            balance (parnetNode);
            if (debugMode)
                print(root);
        }
        void balance (Node *parnetNode) {
            while (parnetNode != NULL)
            {
                if (parnetNode->bf() > 1)
                    l_rotation(parnetNode);
                else if (parnetNode->bf() < -1)
                    r_rotation(parnetNode);
                else
                    parnetNode = parnetNode->parent;
            }


        }

        void remove(key_type key)
        {
            Node *target = search(root, key);
            if (debugMode)
                std::cout << "====== delete " << target->data.first << " ======" << std::endl;
            while (target->left != NULL || target->right != NULL)
            {
                if(target->left){
                   target =  target->swap(target->left);
                    }
                else if(target->right){
                     target =  target->swap(target->right);
                    }
                else {
                    break;
                    }
                print(root);
            }
            if(target->isLeft)
                target->parent->left = NULL;
            else
                target->parent->right = NULL;
        
            target->parent->setHeight();

            balance (target->parent);
            
            print(root);
        }
        void l_rotation(Node *target)
        {
            if (target->bf() < 0)
            {
                if (debugMode)
                    std::cout << "## bf less then 0" << std::endl;
                return;
            }
            if (debugMode)
                std::cout << "## l_rotation"  <<  target->data.first << "->" <<target->left->data.first << std::endl;
            Node *newRoot = target->left;
            Node *oldRoot = target;
            if (oldRoot->parent != NULL)
            {
                if (oldRoot->isLeft)
                    oldRoot->parent->setLeft(newRoot);
                else
                    oldRoot->parent->setRight(newRoot);
            }

            oldRoot->setLeft(newRoot->right);
            newRoot->parent = oldRoot->parent;
            oldRoot->parent = newRoot;

            if (newRoot != NULL)
                newRoot->setRight( oldRoot);
            target = newRoot;

            if (oldRoot == root)
                root = newRoot;

            oldRoot->setHeight();
            newRoot->setHeight();
        }
        void r_rotation(Node *target)
        {
            if (target->bf() > 0)
            {
                if (debugMode)
                    std::cout << "## bf bigger then 0" << std::endl;
                return;
            }
            if (debugMode)
                std::cout << "## r_rotation " <<  target->data.first << "->" <<target->right->data.first << std::endl;
            Node *newRoot = target->right;
            Node *oldRoot = target;

            // parant's child set
            if (oldRoot->parent != NULL)
            {
                if (oldRoot->isLeft)
                    oldRoot->parent->setLeft(newRoot);
                else
                    oldRoot->parent->setRight(newRoot);
            }

            oldRoot->setRight(newRoot->left);
            newRoot->parent = oldRoot->parent;
            oldRoot->parent = newRoot;

            if (newRoot != NULL)
                newRoot->setLeft(oldRoot);
            target = newRoot;

            if (oldRoot == root)
                root = newRoot;

            oldRoot->setHeight();
            newRoot->setHeight();
        }

        Node *search(Node * startNode, key_type key)
        {

            if (startNode == NULL)
                return NULL;
            else if (startNode->data.first == key)
                return startNode;
            return search(startNode->data.first > key ? startNode->left: startNode->right, key);
        }
    };
} // namespace ft
#endif