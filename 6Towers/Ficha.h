#ifndef FICHA_H
#define FICHA_H

class Ficha
{
    private:

        char jogador;
        char cor;
        char Torre;

    public:

        Ficha();
        Ficha(char a,char b,char c);
        char getJogador(){ return jogador;}
        char getCor(){ return cor;}
        char getTorre(){ return Torre;}
};
#endif // FICHA_H
