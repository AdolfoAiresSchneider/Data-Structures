#include "treeavl.h"
#include <bits/stdc++.h>
#include "Game_Physics.h"

using namespace std;
typedef pair<int,int> ii;


int main()
{
    freopen("in","r",stdin);
    freopen("out","w",stdout);
    try{
        int Numero_De_Jogadores;
        while(cin>>Numero_De_Jogadores && Numero_De_Jogadores != 0){
          Game_Physics Game;
          Game.ComputGame(Numero_De_Jogadores);
          Game.Print_Result();
          cout<<endl;
        }
    }catch(string & erro)
    {
      cout<<erro<<endl;
    }
}
