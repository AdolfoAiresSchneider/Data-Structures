#include "Game_Physics.h"

Game_Physics::Game_Physics()
{
    this->Pedra = -1;
}

void Game_Physics::Read_Map_Players(int numero_jogadores)
{
    int x,y,dano,hp;

    this->Qtd_Players = numero_jogadores;
    this-> HP_Dano_Points = new Status [numero_jogadores]; // aloca dinamicamente o vetor de status
    for(int i = 0 ; i < numero_jogadores ; i++)
    {
      cin>>x>>y>>hp>>dano;
      this->Board[int_Pair(x,y)] = i;               // coloca o jogador no tabuleiro
      this->id_Jogador_Board[i] = int_Pair(x,y);    // relaciona numero do jogador com a sua posição
      this-> HP_Dano_Points[i] = Status(hp,dano);   // inicializ seus status
    }
    cin>>this->Max_X>>this->Max_y;                  // Define os limites do tabuleuro
    cin>>x>>y;
    while(x >= 0 && y >= 0)                         // Le enquanto nao tiver numeros negativos
    {
      this->Board[int_Pair(x,y)] = Pedra;           // coloca as pedras no tabuleiro
      cin>>x>>y;
    }
}

void Game_Physics::Read_Compute_Plays()
{
    int Direcao,Current_Player;
    char Jogada;
    Current_Player  = 0;
    do{
        this->HP_Dano_Points[Current_Player].Points = 5;              /// reseta os pontos por jogada
        do{
           cin>>Jogada>>Direcao;
        }while(this->Play(Jogada,Direcao,Current_Player));

        Current_Player = (Current_Player+1)%Qtd_Players;                /// Passa a vez para o proximo jogador
    while(this->HP_Dano_Points[Current_Player].Hp<=0)               /// Passa a vez para o proximo jogador vivo

      Current_Player = (Current_Player+1)%Qtd_Players;          /// Passa a vez para o proximo jogador vivo
    }while(Jogada != 'F' && Direcao != 0);                        /// ler até achar o flag "F 0"
}

bool Game_Physics::Play(char jogada, int direcao,int jogador)
{
    // responsavel pelas direçoes
    int my[] = {0,0,1,0, 0,0,0,0,-1};
    int mx[] = {0,0,0,0,-1,0,1,0,0};

    switch (jogada)
    {
        case 'M':{ ///////////////////////////////////////////////////////////////////////////////////////////// Movimentar

           if(this->HP_Dano_Points[jogador].Points < 1 ) return false;
           /// se nao possuir pontos de ação sufucientes a ação nao é executada
           int_Pair posicao = this->id_Jogador_Board[jogador];

           int x = posicao.first+mx[direcao];                   /// anda na direcao determinada no eixo x
           int y = posicao.second+my[direcao];                  /// anda na direcao determinada no eixo y

           bool flag;
           this->Board.Find(int_Pair(x,y),&flag);               /// verifica se existe algo na posicao (x,y)

           if(!flag && x>=0 && y>=0 && x < this->Max_X  && y < this->Max_y)
           { // Se não achou nada lá e esta dentro dos limites
              this->Board.Erase(int_Pair( posicao.first , posicao.second )); /// apaga o jogador da posicao antiga
              this->Board[int_Pair(x,y)] = jogador;             /// Coloca o jogador na nova posiçao
              this->id_Jogador_Board[jogador] = int_Pair(x,y);  /// atualiza o indece jogador - Posiçao
           }

           this->HP_Dano_Points[jogador].Points -= 1;            /// retira a quantidade de pontos que custa a ação

           if(HP_Dano_Points[jogador].Points <= 0)
               return false;
           return true;
        }

        case 'C':{ ////////////////////////////////////////////////////////////////////////////////////////////// Construir

            if(this->HP_Dano_Points[jogador].Points < 4) return false;
            /// se nao possuir pontos de ação sufucientes a ação nao é executada
            int_Pair posicao = this->id_Jogador_Board[jogador]; /// pega a posiçao atual do jogador

            int x = posicao.first+mx[direcao];
            int y = posicao.second+my[direcao];

            bool flag;
            Board.Find(int_Pair(x,y),&flag);                    /// olha para a posição (x,y)
            if(!flag && x < this->Max_X  && y < this->Max_y && x>=0 && y>=0)
            { // se não achou nada lá e está dentro dos limites
              this->Board[int_Pair(x,y)] = Pedra;
            }
            this->HP_Dano_Points[jogador].Points  -= 4; /// atualiza os pontos de ação

            if(HP_Dano_Points[jogador].Points <= 0)
              return false;
            return true;
        }
        case 'D':{ ////////////////////////////////////////////////////////////////////////////////////////////// Destruir

            if(this->HP_Dano_Points[jogador].Points < 3) return false;
            /// se nao possuir pontos de ação sufucientes a ação nao é executada

            int_Pair posicao = this->id_Jogador_Board[jogador];
            int x = posicao.first+mx[direcao];
            int y = posicao.second+my[direcao];
            bool flag;
            int elemento = this->Board.Find(int_Pair(x,y),&flag);

            if(flag)// achou um elemento
{
                if(elemento == Pedra){
                //se for uma pedra entao destroi ela
                    this->Board.Erase(int_Pair(x,y));
                }
            }
            this->HP_Dano_Points[jogador].Points -=3;

            if(HP_Dano_Points[jogador].Points <= 0)
              return false;
            return true;
        }

        case 'A':{ //////////////////////////////////////////////////////////////////////////////////// Atacer em uma direção

            if(this->HP_Dano_Points[jogador].Points < 1) return false;
            int_Pair posicao = this->id_Jogador_Board[jogador];

            int x = posicao.first+mx[direcao];
            int y = posicao.second+my[direcao];

            bool flag;
            int elemento = this->Board.Find(int_Pair(x,y),&flag);

            while(!flag && x < this->Max_X  && y < this->Max_y && x>=0 && y>=0){
            // Enquanto nao achar nada e estiver dentro do limite
              x += mx[direcao];
              y += my[direcao];
              elemento = this->Board.Find(int_Pair(x,y),&flag);
            }
            if(flag && elemento != Pedra){
            // Se for um jogador

               int Jogador2 = this->Board[int_Pair(x,y)];
               this-> HP_Dano_Points[Jogador2].Hp -= this-> HP_Dano_Points[jogador].Damage;

               if(this-> HP_Dano_Points[Jogador2].Hp <= 0 )
               {// Apaga o jogador do tabuleiro
                 this->Board.Erase(int_Pair(x,y));
               }
            }
            this->HP_Dano_Points[jogador].Points -=1; /// atualiza os pontos de açao do jogador

            if(HP_Dano_Points[jogador].Points <= 0)
              return false;
            return true;
        }
        default:
            return false;
         break;
    }
}

void Game_Physics::ComputGame(int qtdPlayers)
{
    this->Read_Map_Players(qtdPlayers);
    this->Read_Compute_Plays();
}

void Game_Physics::Print_Result()
{
    for(int i = 0; i <this->Qtd_Players;i++)
    {
        cout<<"Jogador "<<i+1<<": ";
        if(this->HP_Dano_Points[i].Hp<=0)
            cout<<"MORTO"<<endl;
        else
            cout<<"("<<this->id_Jogador_Board[i].first<<
                  ","<<id_Jogador_Board[i].second<<") HP: "<<this->HP_Dano_Points[i].Hp<<endl;
    }
}
