#include<pilha.h>
#include "myqueue.h"
#include "Ficha.h"
#include <iostream>
#include<bits/stdc++.h>
#include <bits/stdc++.h>
using namespace std;

int chartToint(char aux){
    return aux - '0' - 1;
}
int putFicha(Ficha * F,Stack<Ficha> * torres){

    int T =  chartToint(F->getTorre());
    if(F->getCor() == 'P'){
        if(!torres[T].isEmpty()) torres[T].pop();
        return 1;
    }
    for(int i = T;i<7;i++,T = (T+1)%6){
        if(torres[T].size() < 6){
           torres[T].push(*F);
           return 1;
        }
    }return 0;
}
int getId(char aux){
    if(aux == 'A') return 0;
    if(aux == 'V') return 1;
    if(aux == 'R') return 2;
    return 3;
}

string getCor(int c)
{
    if(c== 1) return "(Azul)\t";
    if(c== 2) return "(Vermelho)\t";
    if(c== 3) return "(Roxo)\t";
    return "(Branco)\t";
}

int main(){
   freopen ("test.txt","r",stdin);
   char leitura[4];
   int result[4] = {0}, indice[4];
   Myqueue<Ficha> filasDosJogadores[4];
   Stack<Ficha> torres[6];
   Ficha aux;
   while(scanf(" %3s",leitura)!=EOF){
       filasDosJogadores[chartToint(leitura[0])].push(Ficha(leitura[0],leitura[1],leitura[2]));
       if(leitura[1]!='P')
           indice[getId(leitura[1])] = chartToint(leitura[0]);
   }
   int flag = 1;
   for(int i = 0; flag != 0 ; i=(i+1)%4){
       if(!filasDosJogadores[indice[i]].isEmpty()){
           aux = filasDosJogadores[indice[i]].Front();
           if((flag = putFicha(&aux,torres))) filasDosJogadores[indice[i]].pop();
       }
   }
   int maximo=-1,vencedor;
   cout<<"\t\tTorres--------------------------------------"<<endl<<endl;
   for(int i=0;i<6;i++){
       cout<<"\t";
       for(int j=0;j<6;j++){
               aux = torres[j].Top(); torres[j].pop();
               if(i==j){
                   result[chartToint(aux.getJogador())]++;
                   maximo = max(result[chartToint(aux.getJogador())],maximo);
                   cout <<"\t("<< aux.getJogador()<<aux.getCor()<<aux.getTorre()<<") ";
               }
               else  cout <<"\t "<< aux.getJogador()<<aux.getCor()<<aux.getTorre()<<' ';
       }cout<<endl;
   }
   cout<<"\t\t---------------------------------------------"<<endl<<endl;
   cout<<"\t\tPlacar:\n"<<endl;
   flag = 0;///controle de empate ou nao
   for(int i=0;i<4;i++){
       cout<<"\t\t--> Jogador "<<indice[i]+1<<getCor(i+1)<<"\t\t  "<<result[indice[i]]<<"P"<<endl;
       if(result[i] == maximo){
           flag++;
           vencedor = i+1;}
   }
   cout<<"\n"<<endl;
   if(flag>1){
       cout<<"\t\tJogo empatado entre #########################\n"<<endl;
       for(int i=0;i<4;i++)
          if(result[i]==maximo)
                cout<<"\t\t--> Jogador "<<i+1<<endl;
   }else cout<<"\t\t######### O vencendor é o jogador "<<vencedor<<" #########"<<"\n\n\n\n";

   cout<<"\n\t\tElementos Restantes #########################\n"<<endl;
   for(int i=0;i<4;i++){
       cout<<"\t\tJogador "<<i+1<<" : ";
       while(!filasDosJogadores[i].isEmpty()){
           aux = filasDosJogadores[i].Front(); filasDosJogadores[i].pop();
           cout<<aux.getJogador()<<aux.getCor()<<aux.getTorre()<<" ";
        }cout<<endl;
   }cout<<"\n\n";
}
