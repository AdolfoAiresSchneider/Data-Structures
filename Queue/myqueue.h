#ifndef MYQUEUE_H
#define MYQUEUE_H

template<class Type>
class Myqueue
{
    public:

        Myqueue(){ front = back = 0; qtd = 0;}
        bool push(const Type &obj);
        bool pop();
        const Type & Front();
        bool isEmpty();
        int size(){return qtd;}

    private:

        struct Node
        {
                Type Dado_obj;
                Node *Next_obj;
                Node(const Type& newObj, Node *NextNode) : Dado_obj(newObj), Next_obj(NextNode) {}
        };

        Node* back;
        Node* front;
        int qtd;
};

template<class Type>
bool Myqueue<Type>::push(const Type &obj)
{
    if(!front){
        front = back = new Node(obj,0);
        qtd++;
        return front;
    }
    back->Next_obj = new Node(obj,0);
    if(!back->Next_obj) return false;
    back = back->Next_obj;
    qtd++;
    return true;
}
template<class Type>
bool Myqueue<Type>::pop()
{
    if(isEmpty())
        return false;
    Node * aux = front;
    if(front == back) front = back=0;
    else front = front->Next_obj;
    delete aux;
    qtd--;
    return true;
}

template<class Type>
const Type &Myqueue<Type>::Front(){
    return front->Dado_obj;
}

template<class Type>
bool Myqueue<Type>::isEmpty(){
    return !front;
}
#endif // MYQUEUE_H
