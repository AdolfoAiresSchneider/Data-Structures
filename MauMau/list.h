#ifndef LIST_H 
#define LIST_H
#include <bits/stdc++.h>
#include "cartas.h"

using namespace std;

namespace Adolfo{

///---------------------------------------------------------------------------------------------------- Classes  Summary
    template<class type>
    class List;
    template<class type>
    class Lists;
    template<class type>
    struct node;
    template<class type>
    class Iterator;
    template <class type>
    class Cyclo_list;
    template <class type>
    class Sorted_list;
///--------------------------------------------------------------------------------------------------------------------

template<class type> /// Elements Link
struct node
{
    node(const type& newObj, node<type> *next,node<type> * prev) : dado(newObj) , next(next), prev(prev) {} ///constructor
    type     dado;
    node   * next;
    node   * prev;
};

template<class type>
class Iterator      // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Iterator List Class
{
    private:

        friend class    Lists<type> ;
        friend class    List<type>;
        friend class    Cyclo_list<type>;
        node<type> *    currentNode;

    public:

        Iterator( node<type> * id ) : currentNode(id) {} /// constructor
        Iterator(){ currentNode = 0 ; }                  /// constructor

        /// Operators
        Iterator    operator +  ( int n );
        Iterator    operator -  ( int n );
        type &      operator *  ( ){ return currentNode->dado;}
        void        operator =  ( node<type> id ) { currentNode = id;}
        void        operator ++ () { currentNode = currentNode->next; }
        void        operator -- ( ){ currentNode = currentNode->prev; }
        bool        operator != ( Iterator it ){ return currentNode != it.currentNode ;}
};

template<class type>
class Lists // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Abstract list class
{
    protected:

        node<type>      * Nfront;                                                   /// Pontier to the first element
        node<type>      * Nback;                                                    /// Pontier to the last element
        node<type>      * iteratorFlag;                                             /// fake End() && fake Begin
        int               qtd;                                                      /// Size of the list

    public:

        Lists(){ Nfront = Nback = iteratorFlag = new node<type>(type(),0,0); qtd=0;} /// constructor
       ~Lists();

        Iterator<type>   Begin(){ return Iterator<type>(Nfront); }                  /// Return a iterator that points to the end
        Iterator<type>   rBegin(){ return Iterator<type>(Nback); }                  /// Return a iterator that points to the end
        Iterator<type>   End() { return Iterator<type>(iteratorFlag); }             /// Return a iterator that points to the fake end
        Iterator<type>   rEnd() { return Iterator<type>(iteratorFlag); }            /// Return a iterator that points to the begin

        virtual void     push(const type & dado ) = 0;                              /// Commun function to all lists bellow
        virtual void     Erase( Iterator<type> itr );                               /// Delete a element in the iterator position
        const type&      Front();                                                   /// Return the first elemente if it exist
        const type&      Back();                                                    /// Return the first elemente if it exist
        void             clear();                                                   /// Restar the list
        void             PopBack(){ Erase(End());}                                  /// Remove the last element if it exist
        void             PopFront(){ Erase(Begin()); }                              /// Remove the first element if it exist
        bool             IsEmpty(){ return !qtd ||Nfront == iteratorFlag ; }        /// Return 1 if the list is empty
        int              Size() { return qtd; }                                     /// Return the qtd of the elements

        typedef          Iterator<type> iterator;                                   //  iterator list
};

template<class type>
class List : public Lists<type> // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Double linked list Class
{
    public:

        void            Insert(const type &dado, Iterator<type> itr);               /// Insert at iterator position
        void            push(const type &dado){this->PushFront(dado);}              /// Insert at the begin
        void            PushBack(const type &dado){ Insert(dado,this->End()); }     /// insert at the back
        void            PushFront(const type &dado){ Insert(dado,this->Begin()); }  /// Insert at the back
        void            PopFront(){ this->Erase(this->Begin()); }                   /// Remove at the front
        void            PopBack(){ this->Erase(this->End()); }                      /// Remove at the back

};

template <class type>
class Sorted_list : public Lists<type> // ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Sorted list class
{
    public :

        void            push(const type  & dado) ;                                  /// Insert puting in order
        void            PopFront(){ this->Erase(this->Begin()); }                   /// Remove at the front
        void            PopBack(){ this->Erase(this->End()); }                      /// Remove at the begin

};

template <class type>
class Cyclo_list : public List<type> // +++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Cyclo list class
{
    public :

        void             push(const type & dado);                                   /// Push at the front
        void             Erase( Iterator<type> itr );                               /// Remove at the iterator position
};



///+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++  Functions Implementation

template <class type> void Sorted_list<type>::push(const type &dado)
{
    try{
        node<type> *p,*aux= new node<type>(dado,this->iteratorFlag,this->iteratorFlag);
        this->qtd++;
        if(this->IsEmpty()){///in Empty case
            this->Nfront = this->Nback = aux;
            return;
        }
        p = this->Nfront;
        while( p && dado > (*p).dado){ p = p->next;}/// search for the right place
        if(p == this->Nfront){///int the begin
            aux->next = this->Nfront;
            this->Nfront = this->Nfront->prev = aux;
            return;
        }
        if(!p || p == this->iteratorFlag){///in the end
            aux->prev = this->Nback;
            this->Nback = this->Nback->next = aux;
            return;
        }
        aux->prev = p->prev;
        aux->next = p;
        p->prev = p->prev->next  = aux;/// in any other place
        return ;
    }
    catch(std::bad_alloc& ba)
    {
        throw string("Erro de Memória");
    }
}

template <class type> void Cyclo_list<type>::push(const type &dado){
    this->PushBack(dado);
    this->Nback->next = this->Nfront;
    this->Nfront->prev = this->Nback;
}

template<class type>  void Cyclo_list<type>::Erase(Iterator<type> itr)
{
    node<type> * currentNode = itr.currentNode;
    if(this->IsEmpty()) throw "Não existem elementos para serem Removidosr";
    this->qtd--;
    if(this->Nfront == this->Nback)  this->Nfront = this->Nback = this->iteratorFlag;// one element
    else{
        if( this->Nfront == currentNode )// First element
        {
            this->Nfront = this->Nfront->next;
            this->Nfront->prev = this->Nfront->prev->prev;
        }
        else
            if( currentNode == this->iteratorFlag || currentNode == this->Nback )// last element
            {
                currentNode = this->Nback;
                this->Nback = this->Nback->prev;
                this->Nback->next = this->Nback->next->next;
            }
        else// any other element
        {
           currentNode->prev->next = currentNode->next;
           currentNode->next->prev = currentNode->prev;
        }
    }
    delete currentNode;
    this->Nfront->prev = this->Nback;
    this->Nback->next = this->Nfront;
}


template<class type> const type &Lists<type>::Front(){
    if(IsEmpty()) throw "Não existe nada na lista";
    return this->Nfront->dado;
}

template<class type> const type &Lists<type>::Back(){
    if(IsEmpty()) throw "Não existe nada na lista";
    return Nback->dado;
}

template<class type> Lists<type>::~Lists()
{
    this->clear();
}

template<class type> void Lists<type>::Erase(Iterator<type> itr) /// erase a elemente in a iterator position
{
    node<type> * currentNode = itr.currentNode;
    if(IsEmpty()) throw "Não existem elementos para serem Removidosr";
    qtd--;
    if(Nfront == Nback)  Nfront = Nback = iteratorFlag;/// one element
    else{
        if( Nfront == currentNode )/// First element
        {
            Nfront = Nfront->next;
            Nfront->prev = Nfront->prev->prev;
        }
        else
            if( currentNode == iteratorFlag || currentNode == Nback )/// last element
            {
                currentNode = Nback;
                Nback = Nback->prev;
                Nback->next = Nback->next->next;
            }
        else/// any other element
        {
           currentNode->prev->next = currentNode->next;
           currentNode->next->prev = currentNode->prev;
        }
    }
    delete currentNode;
}

template <class type>  void Lists<type>::clear()
{
    while(!this->IsEmpty())
        this->PopBack();
}

template<class type> Iterator<type> Iterator<type>::operator +(int n) /// go foward N times
{
    Iterator<type> aux;
    aux.currentNode = this->currentNode;
    if(n>=0)
    {
        while(aux.currentNode->next&&n--)
            aux.currentNode = aux.currentNode->next;
        return aux;
    }
    while(aux.currentNode->next&&n++)
        aux.currentNode = aux.currentNode->prev;
    return aux;
}

template<class type> Iterator<type> Iterator<type>::operator -(int n) /// go back N times
{
    while(currentNode->prev&&n--)
        currentNode = currentNode->prev;
    return *this;
}


template <class type>   void List<type>::Insert(const type &dado, Iterator<type> itr) /// Push using itertor
{
    try{
        node<type> * currentNode = itr.currentNode, * aux = new node<type>(dado,this->iteratorFlag,this->iteratorFlag) ;
        this->qtd++;
        if( this->IsEmpty( ) ){                                                      /// will be the first in the list
            this->Nfront = this->Nback = aux;
            return;
        }
        aux->next = currentNode;                                                     /// common step by bellow
        if( currentNode == this->iteratorFlag ){                                     /// push after the last one
            aux->prev = this->Nback;
            this->Nback = this->Nback->next = aux;
            return ;
        }
        aux->prev = currentNode->prev;                                               /// common step by bellow
        if( currentNode == this->Nfront ) { this->Nfront = this->Nfront->prev = aux; } /// push before the first one
        else { currentNode->prev = currentNode->prev->next = aux; };                 /// push in any other place
        return ;
    }
    catch(std::bad_alloc& ba)
    {
        throw string("Erro de Memória");
    }
}

} // Namespace end
#endif // LIST_H
