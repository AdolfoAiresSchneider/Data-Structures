#include "maumau.h"

MauMau::MauMau(int CurrentQtdPlayers)
{
    for(int i =0 ; i<CurrentQtdPlayers ; i++) this->Players.push(i);
     Hands = new Adolfo::Sorted_list<Cartas>[CurrentQtdPlayers];
     MaxPlayers = CurrentQtdPlayers = CurrentQtdPlayers;
     memset(Points,0,sizeof(Points));
     MaxPoints = Winner=-1;
}

void MauMau::ReadCards()                                                     /// Le e distribui as cartas
{
    Adolfo::Cyclo_list<int>::iterator it = this->Players.Begin();
    char a,b,c = this->Players.Size();
    int r = 104 ;
    while(c--)
    {
        for(int j = 0 ; j<5 ; j++ )
        {
            r--;
            cin>>a>>b ;
            this->Hands[*it].push( Cartas( a , b ) );

        }
        ++ it;
    }

    while(r--)
    {
        cin>>a>>b ;
        this->Monte.push( Cartas( a , b ) );
    }

}


void MauMau::RemontMont()                                                    /// Remonta o monte caso esteja vazio
{
    Cartas aux = trash.Top( );
    trash.pop( );
    while( !trash.isEmpty( ) )
    {
        Monte.push( trash.Top( ) );
        trash.pop( );
    }
    trash.push( aux );
}


char MauMau::choseCard(int n) /// escolhe a melhor carta se possivel
{
    for( Adolfo::Sorted_list<Cartas>::iterator it = Hands[n].rBegin() ; it != Hands[n].rEnd() ; --it )
    {
        if( (*it) == trash.Top() )
        {
            trash.push((*it));
            Hands[n].Erase(it);
            return trash.Top().getValor();
        }
    }
    return '@';
}


char MauMau::Move(int n)  /// Simula a jogada de um player
{
    if(trash.isEmpty())
    {
        trash.push( Hands[n].Back( ) );
        Hands[ n ].PopBack( );
        return trash.Top( ).getValor( );
    }
    char C = this->choseCard(n);
    if(C != '@') return C;
    this->buyCard(n,1);
    C = this->choseCard(n);
    if(C != '@') return C;
    return '@';
}

void MauMau::ClearRemains()
{
    this->Monte.clear();
    this->trash.clear();
}

void MauMau::buyCard( int player , int n )                                               /// Player compra N cartas
{
    while( n-- )
    {
        if( Monte.isEmpty( ) )                                                          /// Caso nao tenha cartas para comprar
        {
            n++;
            this->RemontMont( );
        }
        else
        {
            this->Hands[player].push( Monte.Top() );
            Monte.pop( );
        }
    }
}

int MauMau::getPoints(int n)   /// Retorna a quantidade de pontos de uma carta
{
    return n-64;
}


void MauMau::Turn( )
{
    int Sentido = 1;  /// Responsavel pelo sentido
    char C  ;
    for( Adolfo::Cyclo_list<int>::iterator it = Players.Begin() ; true ; it = it + Sentido ) /// Percorre a lista circular
    {
        C = Move( (*it) );                      /// Escolher se e qual carta o jogador *it utilizará
        if( Hands[ (*it) ].IsEmpty() ) return;  /// Acabou a rodada
        if( C != '@' )
        {
            switch ( C )
            {
                case 'L': Sentido *= -1; break;                                 /// inverte sentido
                case 'A': it = it + Sentido; break;                             /// pula o proximo jogador
                case 'G': buyCard( *( it + Sentido ) , 2 ); break;              /// proximo compra duas cartas
                case 'I': buyCard( *( it + ( Sentido * (-1) ) ) , 3 ) ; break;  /// anterior compra 3 cartas
                default : break;
            }
        }
    }
}


void MauMau::RemovePlayer()
{
    int i;
    memset(Points,0,sizeof(Points));
    MaxPoints = -1;
    for(int i = 0; i < this->MaxPlayers ; i++)                         /// Contas os pontos de cada jogador
    {
        while(!Hands[i].IsEmpty())
        {
            Points[i] += getPoints(Hands[i].Front().getValor());
            Hands[i].PopFront();
        }
        this->MaxPoints = max(MaxPoints,Points[i]);                    /// Define a chave para encontrar o maior jogador
    }
    for( i = 0;i<MaxPlayers && Points[i] != MaxPoints;i++ );           /// Define o jogador que deve sair
    for(Adolfo::Cyclo_list<int>::iterator it = Players.Begin();;++it)  /// Procura e apaga o jogador de acordo com seu  numero
    {
        if( (*it) == i )
        {
            this->Players.Erase(it);                                    /// Remove o jogador da partida
            this->CurrentQtdPlayers--;                                  ///   ||   ||   ||   ||    ||
            return;
        }
    }
}

int MauMau::ComputGame()                                                     /// Simula o jogo
{
    try{
        while(this->Players.Size() != 1)                                    /// Verifica se o jogo acabou
        {
            this->ReadCards();                                              /// Lê as cartas de cada rodada
            this->Turn();                                                   /// Simula cada rodada
            this->RemovePlayer();                                           /// Remove o jogador de maior pontuação da rodada
            this->ClearRemains();
        }
        Winner = Players.Front()+1;                                         /// Declara o vencedor
        return Winner;                                                      //  Retorna quem venceu a partida
    }catch(string & ERRO)
    {
        throw ERRO;
    }
}

int MauMau::getWinner()
{
    return this->Winner;
}

MauMau::~MauMau()
{
        Hands->clear();
        Players.clear();
}
