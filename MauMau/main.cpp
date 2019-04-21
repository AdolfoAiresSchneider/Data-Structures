#include <bits/stdc++.h>
#include "maumau.h"
using namespace std;

int main(){
    freopen("testes.txt","r",stdin);
    freopen("saida.txt","w",stdout);
    int QtdPartidas,NumeroDeJogadores,u=1;
    cin>>QtdPartidas;
    try{
        while(QtdPartidas--)
        {
            cin>>NumeroDeJogadores;
            MauMau game(NumeroDeJogadores);
            game.ComputGame();
            cout<<"Vencedor da partida "<<u++<<": Jogador "<<game.getWinner()<<'.'<<endl;
        }
    }catch(string & ERRO){
        cout<<ERRO<<endl;
    }
}
