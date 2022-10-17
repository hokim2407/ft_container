#include "stack.hpp"
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

int main (){
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