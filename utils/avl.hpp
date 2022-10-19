
#ifndef AVL_HPP
#define AVL_HPP

#include <iostream>
#include "utils.hpp"
#include "pair.hpp"
namespace ft
{
    template <class T,
              class key_type = typename T::key_type,
              class Compare = std::less<key_type> >
    class Node
    {
        typedef Compare key_compare;
        typedef typename T::value_type value_type;

    public:
        T data;
        Node<T> *left;
        Node<T> *right;
        Node<T> *parent;
        unsigned int height;
        bool isLeft;

    private:
        key_compare _comp;

    public:
        Node()
        {
            this->_comp = key_compare();
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->height = 1;
        }
        Node(T &d) : data(d)
        {
            this->_comp = key_compare();
            this->left = NULL;
            this->right = NULL;
            this->parent = NULL;
            this->height = 1;
        }
        Node(Node<T> *n)
        {
            this->_comp = key_compare();
            *this = n;
        }
        Node &operator=(const Node &n)
        {
            this->data = n.data;
            this->left = n.left;
            this->right = n.right;
            this->parent = n.parent;
            this->height = n.height;
            this->isLeft = n.isLeft;
            return *this;
        }
        Node *biggerNode()
        {
            Node *ptr = this;
            if (ptr->right)
            {
                ptr = ptr->right;
                while (ptr->left != NULL)
                {
                    ptr = ptr->left;
                }
            }
            else if (ptr->parent && ptr->isLeft == true)
            {
                ptr = ptr->parent;
            }
            else if (ptr->parent && ptr->isLeft == false)
            {
                key_type key = ptr->data.first;
                ptr = ptr->parent;
                while (ptr != NULL && ptr->data.first < key)
                {
                    ptr = ptr->parent;
                }
            }
            else
            {
                ptr = NULL;
            }
            return ptr;
        }
        Node *smallerNode()
        {
            Node *ptr = this;
            if (ptr->left)
                ptr = ptr->left;
            else if (ptr->isLeft == false)
                ptr = ptr->parent;
            else
            {
                key_type key = ptr->data.first;
                while (ptr->parent != NULL)
                {
                    ptr = ptr->parent;
                }
            }
            return ptr;
        }
        ~Node()
        {
        }
        bool operator<(const Node<T> &n2)
        {
            return this->_comp(this->data.first, n2.data.first);
        };
        bool operator>(const Node<T> &n2)
        {
            return this->_comp(n2.data.first, this->data.first);
        };
        bool operator<=(const Node<T> &n2)
        {
            return !(this->operator>(n2));
        };
        bool operator>=(const Node<T> &n2)
        {
            return !(this->operator<(n2));
        };
        bool key(const Node<T> &n2)
        {
            return this->data > n2.data;
        };

        void setHeight()
        {
            int leftH = left ? this->left->height : 0;
            int rightH = this->right ? this->right->height : 0;
            if (!this->left && !this->right)
                this->height = 1;
            else if (leftH > rightH)
                this->height = leftH + 1;
            else
                this->height = rightH + 1;

            if (this->parent != NULL)
                this->parent->setHeight();
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
            int leftH = this->left ? left->height : 0;
            int rightH = this->right ? right->height : 0;
            return leftH - rightH;
        };
        Node *swap(Node *n)
        {
            //only data stap
            T temp = n->data;
            n->data = this->data;
            this->data = temp;

            return n;
        };
    };

    template <class Key,
              class T,
              class Compare = std::less<Key>,
              class Alloc = std::allocator<ft::pair<const Key, T> > >
    class Tree
    {
    public:
        typedef Key key_type;
        typedef T mapped_type;
        typedef Compare key_compare;
        typedef Alloc allocator_type;
        typedef ft::pair<Key, T> value_type;
        typedef Node<value_type> Node;
        typedef std::allocator<Node> node_alloc;
        typedef typename allocator_type::size_type size_type;
        typedef typename allocator_type::difference_type difference_type;

    public:
        bool debugMode;

    private:
        Node *_root;
        size_type _size;
        key_compare _key_comp;
        allocator_type _alloc;
        node_alloc _node_alloc;
        Node *_first;
        Node *_last;
        Node *_end;
        // typename allocator_type::template rebind<Node>::other _node_allocator;
    public:
        Tree(const key_compare &key_comp = key_compare(), const allocator_type &alloc = allocator_type(),
             bool debug = false)
            : debugMode(debug), _root(NULL), _size(0), _key_comp(key_comp), _alloc(alloc)
        {
            _node_alloc = node_alloc();
            this->_end = this->_node_alloc.allocate(1);
            this->_end->parent = NULL;
            this->_end->left = NULL;
            this->_end->right = NULL;
            setFirst(this->_end);
            setLast(this->_end);

            if (debugMode)
                std::cout << "in" << std::endl;
        };
        ~Tree(){
            //this->clear();
        };
        Tree(Tree &t, const key_compare &key_comp = key_compare(), const allocator_type &alloc = allocator_type(),
             bool debug = false)
            : _root(NULL), _key_comp(key_comp), _alloc(alloc), debugMode(debug)
        {
            _node_alloc = node_alloc();
            *this = t;
        };
        Tree &operator=(const Tree &t)
        {
            this->clear();
            this->_root = t._root;
            this->_key_comp = t.get_key_comp();
            this->_alloc = t.get_alloc();
            this->_size = t.size();
            setFirst(t.first());
            setLast(t.last());

           // this->_node_alloc.deallocate(this->_end, 1);
            *(this->_end) = *(t.end());
            return *this;
        }
        Node *base()
        {
            return this->_root;
        };
        key_compare get_key_comp() const
        {
            return this->_key_comp;
        };
        allocator_type get_alloc() const
        {
            return this->_alloc;
        };

        Node *findParent(Node *parentNode, Node *targetNode)
        {
            Node *nextPatent = NULL;

            if (*parentNode > *targetNode)
                nextPatent = parentNode->left;

            else if (*parentNode < *targetNode)
                nextPatent = parentNode->right;

            if (nextPatent == NULL)
                return parentNode;

            return findParent(nextPatent, targetNode);
        }

        void print(Node *parentNode, std::string prefix = "")
        {
            if (parentNode == NULL)
                return;

            std::cout << prefix;

            std::cout << (parentNode->isLeft ? "└──" : "├──");
            std::string parent = "";
            //print the value of the node
            // if (parentNode->parent)
            //     std::cout << "p:" << (parentNode->parent->data.first) << ", ";
            // if (parentNode->left)
            //     std::cout << "l:" << (parentNode->left->data.first) << ", ";
            // if (parentNode->right)
            //     std::cout << "r:" << (parentNode->right->data.first) << ", ";

            std::cout << "bf:" << (parentNode->bf()) << ", ";

            std::cout << "\033[92m\033[1m" << parentNode->data.first << "\033[0m [" << parentNode->height << "]" << (parentNode->isLeft == true ? "L" : "R") << std::endl;

            // enter the next tree level - left and right branch
            print(parentNode->right, prefix + (parentNode->isLeft == true ? "    " : "│   "));
            print(parentNode->left, prefix + (parentNode->isLeft == true ? "    " : "│   "));
        }

        void insert(value_type data)
        {
            this->_size++;
            if (debugMode)
                std::cout << "====== insert " << data.first << " ======" << std::endl;
            Node *newNode = this->_node_alloc.allocate(1);

			_node_alloc.construct(newNode, Node(data));

            std::cout<<":"  << std::endl;

            if (_root == NULL)
            {
                _root = newNode;
                setFirst(newNode);
                setLast(newNode);
                return;
            }
            Node *parnetNode = findParent(_root, newNode);
            newNode->parent = parnetNode;

            if (*parnetNode > *newNode)
                parnetNode->setLeft(newNode);
            else
                parnetNode->setRight(newNode);

            if (newNode->data.first < this->_first->data.first)
                setFirst(newNode);
            if (newNode->data.first > this->_last->data.first)
                setLast(newNode);
            newNode->setHeight();
            balance(newNode);

            if (debugMode)
                print(_root);
        }
        void balance(Node *node)
        {
            while (node != NULL)
            {
                Node *l_child = node->left;
                Node *r_child = node->right;
                if (node->bf() > 1)
                {
                    if (l_child && l_child->right && l_child->right == NULL)
                        r_rotation(l_child);
                    if (l_child && r_child && r_child->height < l_child->height)
                    {
                        r_rotation(l_child);
                    }
                    l_rotation(node);
                }
                else if (node->bf() < -1)
                {
                    if (r_child && r_child->left && r_child->right == NULL)
                        l_rotation(r_child);
                    if (r_child && l_child && r_child->height > l_child->height)
                    {
                        l_rotation(r_child);
                    }

                    r_rotation(node);
                }
                else
                    node = node->parent;
            }
        }

        void remove(key_type key)
        {
            this->_size--;
            Node *target = search(_root, key);
            if (debugMode)
                std::cout << "====== delete " << target->data.first << " ======" << std::endl;

            setLast(target->parent);
            while (target->right != NULL || target->left != NULL)
            {
                if (target->right)
                {
                    target = target->swap(target->right);
                }
                else if (target->left)
                {
                    target = target->swap(target->left);
                }
                else
                    break;
            }
       
            if (target->isLeft)
                target->parent->left = NULL;
            else
                target->parent->right = NULL;

            target->parent->setHeight();

            balance(target->parent);
            searchSmallest();
            searchbiggest();

            // this->_node_alloc.deallocate(target, 1);
            // ;

            if (debugMode)
                print(_root);
        }

        void l_rotation(Node *target)
        {
            if (debugMode)
                std::cout << "## l_rotation " << target->data.first << "->" << target->left->data.first << std::endl;
            Node *new_root = target->left;
            Node *old_root = target;
            if (old_root->parent != NULL)
            {
                if (old_root->isLeft)
                    old_root->parent->setLeft(new_root);
                else
                    old_root->parent->setRight(new_root);
            }

            old_root->setLeft(new_root->right);
            new_root->parent = old_root->parent;
            old_root->parent = new_root;

            if (new_root != NULL)
                new_root->setRight(old_root);
            target = new_root;

            if (old_root == _root)
                _root = new_root;

            old_root->setHeight();
            new_root->setHeight();
            if (debugMode)
                print(this->_root);
        }
        void r_rotation(Node *target)
        {
            if (debugMode)
                std::cout << "## r_rotation " << target->data.first << "->" << target->right->data.first << std::endl;
            Node *new_root = target->right;
            Node *old_root = target;

            // parant's child set
            if (old_root->parent != NULL)
            {
                if (old_root->isLeft)
                    old_root->parent->setLeft(new_root);
                else
                    old_root->parent->setRight(new_root);
            }

            old_root->setRight(new_root->left);
            new_root->parent = old_root->parent;
            old_root->parent = new_root;

            if (new_root != NULL)
                new_root->setLeft(old_root);
            target = new_root;

            if (old_root == _root)
                _root = new_root;

            old_root->setHeight();
            new_root->setHeight();
            if (debugMode)
                print(this->_root);
        }

        Node *search(Node *startNode, key_type key)
        {

            if (startNode == NULL)
                return NULL;
            else if (startNode->data.first == key)
                return startNode;
            return search(startNode->data.first > key ? startNode->left : startNode->right, key);
        }

        Node *searchSmallest()
        {
            Node *result = this->_root;
            while (result->left)
            {
                result = result->left;
            }

            setFirst(result);
            return result;
        }

        Node *searchbiggest()
        {
            Node *result = this->_root;
            while (result->right)
            {
                result = result->right;
            }
            setLast(result);
            return result;
        }

        size_type size() const
        {
            return this->_size;
        }
        size_type max_size() const
        {
            return (this->_alloc.max_size() < (unsigned long)std::numeric_limits<difference_type>::max()) ? this->_alloc.max_size() : (unsigned long)std::numeric_limits<difference_type>::max();
        }
        void clear()
        {
            Node *start = this->_first;
            while (start != NULL)
            {
               // Node *temp = start;
                start = start->biggerNode();

                // this->_node_alloc.deallocate(temp, 1);
            }
            this->_root = NULL;
            this->_size = 0;
        }
        void swap(Tree &t)
        {
            Tree *temp = new Tree(*this);
            *this = t;
            t.clear();
            t = *temp;
        }
        bool operator==(const Tree &t)
        {
            if ((this->_root == t.base()) && (this->_size == t.size()))
                return true;
            return false;
        }

        Node *first() const
        {
            return this->_first;
        }
        Node *last() const
        {
            return this->_last;
        }
        Node *end() const
        {
            return (this->_end);
        }

        Node *setFirst(Node *first)
        {
            // _rend ++ = _first
            // _end -- = _first
            this->_first = first;
            this->_end->left = this->_first;
            return this->_first;
        }
        Node *setLast(Node *last)
        {
            // _end ++ = _last
            this->_last = last;
            this->_end->right = this->_last;
            return this->_last;
        }
    };

} // namespace ft
#endif