#ifndef MAUMAU_H
#define MAUMAU_H
#include <bits/stdc++.h>
#include "cartas.h"
#include <list.h>
#include "pilha.h"

using namespace std;

/// falta fazer o clear e consertar os pontos
class MauMau
{
    private:///---------------------------------------------------------------------------------------------------------------

        Adolfo::Sorted_list<Cartas>  *Hands;                      //  Mão dos jogadores ( Vetor de Lista Orndenados )
        Adolfo::Cyclo_list<int>       Players;                    //  Jogadores (Lista Circular)
        Stack<Cartas>                 Monte;                      //  Monte (Pilha)
        Stack<Cartas>                 trash;                      /// Lixo (Pilha)
        int                           CurrentQtdPlayers;          /// Quantidade de jogadores
        int                           Winner;                     /// Vencedor
        int                           Points[10];                 /// Tabela de pontos
        int                           MaxPoints;                  /// Maior numero de pontos
        int                           MaxPlayers;                 /// Numero Maximo de Jogadores

        //+++++++++++++++++++++++++++++++++++++++++++++++++++++++++++ Funçoes utilitarias ++++++++++++++++++++++++++++++++++++

        void                          buyCard(int player, int n); /// Player compra n cartas do monte
        void                          RemontMont();               /// Refaz o monte
        void                          Turn();                     /// Simula cada Turno
        void                          RemovePlayer();             /// Remove um jogador da partida
        int                           getPoints(int n);           /// Retorna a quantidade de pontos de uma carta
        char                          choseCard(int n);           /// Define a melhor opçao de carta ou se é possivel usar uma
        char                          Move(int n);                /// Simula a jogada do jogador n
        void                          ClearRemains();             /// Limpa os resquicios de um turno
        void                          ReadCards();                /// Lê e distribui as cartas

    public:///----------------------------------------------------------------------------------------------------------------

        int                           ComputGame();               /// Simula o jogo
        int                           getWinner();                /// Retorna o vencedor

       ~MauMau();                                                 /// DestruCtor
        MauMau(int CurrentQtdPlayers);                            /// CosntruCtor

};//--------------------------------------------------------------------------------------------------------------------------

#endif // MAUMAU_H
