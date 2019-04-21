#ifndef GAME_PHYSICS_H
#define GAME_PHYSICS_H
#include "treeavl.h"
#include <bits/stdc++.h>
typedef pair<int,int> int_Pair;
using namespace std;


class Game_Physics//-----------------------------------------------------------------------------------
{
    private:

        ASDF::TreeAvl<int_Pair,int> Board;            // Tabuleiro-------------------------------------
        ASDF::TreeAvl<int,int_Pair> id_Jogador_Board; // Indice----------------------------------------

        struct Status
        {
            int Hp;
            int Damage;
            int Points;
            Status(int hp,int damage) : Hp(hp),Damage(damage),Points(5){}
            Status(){}
        };

        Status * HP_Dano_Points;

        int Pedra ;     // Representa a pedra----------------------------------------------------------
        int Max_X;      // Limite x do tabuleiro-------------------------------------------------------
        int Max_y;      // Limite y do tabuleiro-------------------------------------------------------
        int Qtd_Players;// Quantida de jogadores-------------------------------------------------------

    public:

        Game_Physics();

        void Read_Map_Players(int numero_jogadores);        /// Le os jogadores e o tabuleiro----------
        void Read_Compute_Plays();                          /// Le as jogadas--------------------------
        bool Play(char jogada, int direcao, int jogador);   /// Executa as jogadas---------------------
        void ComputGame(int qtdPlayers);                    /// Simula o jogp--------------------------
        void Print_Result();                                /// Imprimi o resultado--------------------

};//---------------------------------------------------------------------------------------------------

#endif // GAME_PHYSICS_
