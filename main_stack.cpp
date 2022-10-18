#include "stack.hpp"
#include "vector.hpp"
#include <vector>
#include <stack>



void PrintStack(ft::stack<int> stack, std::stack<int> st)
{
    // If stack is empty then return
    if (stack.empty()){
    std::cout <<"-----" <<std::endl;
        return;
        }
     
 
    int oriStack = stack.top();
    int oriSt = st.top();
 
    // Pop the top element of the stack
    stack.pop();
    st.pop();
 
    // Recursively call the function PrintStack
    PrintStack(stack, st);
 
    // Print the stack element starting
    // from the bottom
    std::cout <<"ft: "<< oriStack << " , std:" << oriSt <<std::endl;
 
    // Push the same element onto the stack
    // to preserve the order
    stack.push(oriStack);
    st.push(oriSt);
}

int test (){
    ft::stack<int> *stack = new ft::stack<int> ();
    std::stack<int> *st = new std::stack<int> ();
    stack->push(1);
    st->push(1);
    PrintStack(*stack, *st);

    stack->push(3);
    st->push(3);
    PrintStack(*stack, *st);

    stack->push(2);
    st->push(2);
    PrintStack(*stack, *st);

    stack->pop();
    st->pop();
    PrintStack(*stack, *st);

    return 0;
}
template <class T>
std::vector<int> constructor_test1() {
    std::stack<T> stk;
	std::vector<int> v;
	std::deque<int> deque;
	for (int i = 0; i < 100; ++i)
		deque.push_back(i);
	for (int i = 100; i < 200; ++i)
		stk.push(i);
	std::stack<int> stack(deque);
	std::stack<int> stack2(stk);
	std::stack<int> stack3;
	stack3 = stack2;
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}


template <class T>
std::vector<int> constructor_test2() {
    ft::stack<T> stk;
	std::vector<int> v;
	ft::vector<int> deque;
	for (int i = 0; i < 100; ++i)
		deque.push_back(i);
	for (int i = 100; i < 200; ++i){
		stk.push(i);
        }
	ft::stack<int> stack(deque);
	ft::stack<int> stack2(stk);
	ft::stack<int> stack3;
	stack3 = stack2;
	while (stack.size() > 0) {
		v.push_back(stack.top());
		stack.pop();
	}
	while (stack2.size() > 0) {
		v.push_back(stack2.top());
		stack2.pop();
	}
	return v;
}

template <class T>
bool constructor_test3() {
	std::vector<int> result, result2;

	    ft::stack<int> st1, st2;
        st2.push(2); 
        st1.push(2);

	return st1 == st2;
}


int main (){
    // std::cout << (constructor_test1<int>() ==
    // constructor_test2<int>())<<std::endl ;
   constructor_test3<int>();
    return 0;
}
