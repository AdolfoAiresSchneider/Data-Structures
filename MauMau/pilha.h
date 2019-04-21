#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

template <class Type>
class Stack
{
    public:

        Stack() { top =0, qtd = 0; }
        bool push (const Type &obj);
        void pop();
        const Type & Top();
        bool isEmpty();
        int size(){ return qtd; }
        void clear();

    private:

        struct Node
        {
                Type Dado_obj;
                Node *Next_obj;
                Node(const Type& newObj, Node *NextNode) : Dado_obj(newObj), Next_obj(NextNode) {}
        };

        Node *top;
        int qtd;
};

template <class Type>
bool Stack<Type>::push(const Type & obj)
{
    Node * aux = top;
    top = new Node(obj,top);
    if(!top)
    {
        top = aux;
        return false;
    }
    qtd++;
    return true;
}

template <class Type>
void Stack<Type>::pop()
{
    qtd--;
    Node *aux = top;
    top = top->Next_obj;
    delete aux;
}

template <class Type>
const Type &Stack<Type>::Top()
{
    return top->Dado_obj;
}


template <class Type>
bool Stack<Type>::isEmpty()
{
    return !top;
}

template <class Type> void Stack<Type>::clear()
{
    while(!this->isEmpty()) this->pop();
}
#endif
