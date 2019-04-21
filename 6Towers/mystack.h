#ifndef _STACK_H_
#define _STACK_H_
#include <iostream>

template <class Type>
class Stack
{
    public:

        Stack() { top =0, qtd = 0; }
        bool push (const T &obj);
        void pop();
        const T& Top();
        bool isEmpty();
        int size(){ return qtd; }

    private:

        struct Node
        {
            private:
                Type Dado_obj;
                Node *Next_obj;
                Node(const Type& newObj, Node *NextNode) : obj(newObj), next(NextNode) {}
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
    Node *aux = top;
    top = top->next;
    delete aux;
    qtd--;
}

template <class Type>
const Type& Stack<Type>::Top()
{
    return top->obj;
}

template <class Type>
bool Stack<Type>::isEmpty()
{
    if (!top)
        return true;
    else
        return false;
}
#endif
