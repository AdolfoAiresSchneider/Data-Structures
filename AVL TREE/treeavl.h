#ifndef TREEAVL_H
#define TREEAVL_H
#include <bits/stdc++.h>
using namespace std;

namespace ASDF{

template <class Tkey,class Type>
class TreeAvl
{
    private:

        struct Node///----------------------------------------------------------------------------------------------------
        {
          Node *    right;
          Node *    left;
          Type      data;
          Tkey      key;
          int       fb;

          Node( const Type & obj, Node * right, Node* left,Tkey key)
              :right(right),left(left),data(obj),key(key), fb(0){}

        };///-------------------------------------------------------------------------------------------------------------

        Node * Root; // Raiz da arvore -----------------------------------------------------------------------------------

        //-----------------------------------------------------------------------------------------------------Utilitarias

        static Type&    Search(Node * Root, Tkey key ,Node ** RootMae); /// Busca que retorna a refarencia para o dado----
        static Node *   Max_Sub_Tree(Node * Root);                      /// Retorna a maxima de uma subarvore-------------

        static bool     Search(Node * Root, Tkey key , Type * data);    /// Busca que retorna bool------------------------
        static bool     Erase_AVL( Tkey key , Node ** Root );           /// Apaga elementos da arvore---------------------
        static bool     Insert_Avl(Node * P,Node ** Root );             /// Insere Elementos da arvore--------------------

        static void     RSD(Node ** Root );                             // Rotações --------------------------------------
        static void     RDD(Node ** Root );
        static void     RSE(Node ** Root );
        static void     RDE(Node ** Root );                                      //<<<<<----------------------------------
                                                                                 //<<<<<----------------------------------
        static void     RD(Node ** Root );
        static void     RE(Node ** Root );
                                                                        //------------------------------------------------
        //----------------------------------------------------------------------------------------------------------------

    public:

        TreeAvl():Root(0){Root = 0;}                                    /// Construtor-----------------------------------------------

        Type & operator []( const Tkey & key );                         /// Operator [], Retorna uma referencia do dado de uma chave-
        Type            Find( Tkey const & key , bool * flag );         /// Busca o elemento e seta true no flag caso bem sucedido---

        bool            Push( const Type & data , const Tkey  & key );  /// Insere um elemento na arvore ----------------------------
        bool            Erase(Tkey const & Key);                        /// Apaga um elemento na arvore------------------------------

};

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RSD(TreeAvl::Node **Root)
{
    Node *b = (*Root);
    Node *a = b->left;
    b->left = a->right;
    a->right = b;
    (*Root)=a;
    if(!a->fb) a->fb  = 1 ;
    else b->fb = a->fb = 0;
}

template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RDD(TreeAvl::Node **Root)
{
    Node * c= (*Root);
    Node *a = c->left;
    Node *b = a->right;
    c->left=b->right;
    a->right=b->left;
    b->left=a;
    b->right=c;

    switch (b->fb){
      case-1:{ a->fb=0; c->fb=1; break;}
      case 0:{ a->fb =0; c->fb=0; break;}
      case 1:{ a->fb= -1; c->fb=0; break;}
    }
    b->fb = 0;
   (*Root)=b;

}

template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RSE(TreeAvl::Node **Root)
{
    Node * a =(*Root);
    Node * b = a->right;
    a->right = b->left;
    b->left = a;
    (*Root)= b;
    if(!b->fb)  b->fb = -1 ;
    else b->fb = a->fb = 0;
}

template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RDE(TreeAvl::Node **Root)
{
    Node *a=(*Root);
    Node *c=a->right;
    Node *b=c->left;
    c->left=b->right;
    a->right=b->left;
    b->left=a;
    b->right=c;
    switch (b->fb)  {
      case-1: {a->fb=0; c->fb=1; break;}
      case 0: {a->fb =0; c->fb=0; break;}
      case 1: {a->fb= -1; c->fb=0; break;}
    }
    b->fb = 0;
   (*Root)=b;
}


template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RD(TreeAvl::Node **Root)
{
    Node * aux = (*Root)->left;
    if(aux->fb != 1)
    {
      ASDF::TreeAvl<Tkey,Type>::RSD(Root); // simples direita
    }
    else
    {
      ASDF::TreeAvl<Tkey,Type>::RDD(Root); /// esquerda direita (Dupla DIREITA)
    }
}

template <class Tkey,class Type>
void TreeAvl<Tkey,Type>::RE(TreeAvl::Node **Root )
{
    Node * aux = (*Root)->right;
    if(aux->fb != -1 )
    {
      ASDF::TreeAvl<Tkey,Type>::RSE(Root); // simples esquerda
    }
    else
    {
      ASDF::TreeAvl<Tkey,Type>::RDE(Root); /// direita esquerda (Dupla esquerda)
    }
}

template <class Tkey,class Type> typename
TreeAvl<Tkey,Type>::Node *TreeAvl<Tkey,Type>::Max_Sub_Tree(TreeAvl::Node *Root)
{
    if(!Root) return 0;
    if(!Root->right) return Root;
    return Max_Sub_Tree(Root->right);
}


template <class Tkey,class Type> bool TreeAvl<Tkey,Type>::Insert_Avl(Node * P, TreeAvl::Node **Root)
{
    if(*Root == NULL)
    {
      *Root = P;
      return true;
    }
    if(P->key < ((*Root)->key)){
        if(ASDF::TreeAvl<Tkey,Type>::Insert_Avl(P,&((*Root)->left))){
            switch ((*Root)->fb)
            {
              case  1:{ (*Root)->fb = 0; return false;}
              case  0:{ (*Root)->fb = -1; return true;}
              case -1:{ ASDF::TreeAvl<Tkey,Type>::RD(Root); return false;}
            }
        }
        return false;
    }
    if(P->key > ((*Root)->key)){
        if(ASDF::TreeAvl<Tkey,Type>::Insert_Avl(P,&((*Root)->right))){
            switch ((*Root)->fb)
            {
              case -1: { (*Root)->fb = 0; return false;}
              case  0: { (*Root)->fb = 1; return true;}
              case  1: {ASDF::TreeAvl<Tkey,Type>::RE(Root); return false;}
            }
        }
        return false;
    }
    return false;
}


template <class Tkey,class Type>
bool TreeAvl<Tkey,Type>::Push(const Type & data , const Tkey  & key)
{
    Node * p = new Node(data,0,0,key); // Aloca o node
    if(!p) // se nao conseguiu alocar deu merda
    {
      return false;
    }
    ASDF::TreeAvl<Tkey,Type>::Insert_Avl(p,&Root);
    return true;
}

template <class Tkey,class Type>
Type TreeAvl<Tkey,Type>::Find (const Tkey & key, bool * flag)
{
    Type AUX;
    if(ASDF::TreeAvl<Tkey,Type>::Search(Root,key,&AUX))
    {
      *flag =1;
       return AUX;
    }
    *flag = 0;
    return AUX;
}


template <class Tkey,class Type>
Type & TreeAvl<Tkey,Type>::operator [](const Tkey & key)
{
    return ASDF::TreeAvl<Tkey,Type>::Search(Root,key,&Root);
}

template <class Tkey,class Type>
bool TreeAvl<Tkey,Type>::Erase(const Tkey &Key)
{
    ASDF::TreeAvl<Tkey,Type>::Erase_AVL(Key,&Root);
    return true;
}


template <class Tkey,class Type>
bool TreeAvl<Tkey,Type>::Search(TreeAvl::Node *Root, Tkey key, Type *data){
// Procura e retorna o data, 1 achou,0 nao achou
    if(!Root)
    {
      return false;
    }
    if(Root->key == key)
    {
      *data = Root->data;
       return true;
    }
    if(key < Root->key)
    {
      return Search(Root->left,key,data);
    }
    return Search(Root->right,key,data);
}

template <class Tkey,class Type>
Type & TreeAvl<Tkey,Type>::Search(TreeAvl::Node *Root, Tkey key , Node ** RootMae){
// procura  e retorna uma referencia, se não achou cria um default e retorna sua referencia
    if(!Root)
    {
      Node * p = new Node(Type(),0,0,key);
      ASDF::TreeAvl<Tkey,Type>::Insert_Avl(p,RootMae);
      return p->data;
    }
    if(Root->key == key)
    {
      return Root->data;
    }
    if(key < Root->key)
    {
      return Search(Root->left,key,RootMae);
    }
    return Search(Root->right,key,RootMae);
}

template <class Tkey,class Type>
bool TreeAvl<Tkey,Type>::Erase_AVL(Tkey key, TreeAvl::Node **Root)
{
    if(!*Root)
    {
      return false;
    }
    if(key < (*Root)->key)
    {
      if(Erase_AVL(key,&(*Root)->left))
      {
          switch ((*Root)->fb)
          {
              case -1: {((*Root)->fb = 0); return true;}
              case  0: {(*Root)->fb = 1; return false;}
              case  1:
          {
                if(((*Root)->right)->fb != -1){
                  RSE(Root);
                  return !(*Root)->fb;
                }
                RDE(Root);
                return true;
              }
          }
      }
      return false;
    }

    if(key > (*Root)->key)
    {
        if(Erase_AVL(key,&(*Root)->right))
        {
            switch ((*Root)->fb){
                case  1: { ((*Root)->fb = 0); return true; }
                case  0: {((*Root)->fb = -1);return false;}
                case -1: {
                  if(((*Root)->left)->fb != 1){
                    RSD(Root);
                    return !(*Root)->fb;
                  }
                  RDD(Root);
                  return true;
                }
            }
        }
        return false;
    }

    if(!(*Root)->left)
    {
      Node * x = (*Root)->right;
      delete (*Root);
      (*Root) = x;
      return true;
    }

    if(!(*Root)->right)
    {
      Node * x = (*Root)->left;
      delete (*Root);
      (*Root) = x;
      return true;
    }

    Node * max = ASDF::TreeAvl<Tkey,Type>::Max_Sub_Tree((*Root)->left);
    swap(max->data,(*Root)->data);
    swap(max->key,(*Root)->key);

    if(Erase_AVL(key,&(*Root)->left))
    {
        switch ((*Root)->fb){
            case -1: {((*Root)->fb = 0); return true;}
            case  0: {(*Root)->fb = 1;   return false;}
            case  1:{
              if(((*Root)->right)->fb != -1){
                RSE(Root);
                return !(*Root)->fb;
              }
              RDE(Root);
              return true;
        }
       }
    }
    return false;
}

}
#endif // TREEAVL_H
