#ifndef CARTAS_H
#define CARTAS_H


class Cartas
{
private:

    char Naipe;
    char valor;

public:

    void serCarta(char & n, char & p);
    bool operator < (Cartas &d)const;
    bool operator > (Cartas &d)const{ return this->valor > d.valor || (this->valor >= d.valor && this->Naipe < d.Naipe);}
    bool operator == (Cartas const &d) const { return (Naipe == d.Naipe || valor==d.valor); }
    char getNaipe()const {return Naipe;}
    char getValor() const {return valor;}

    Cartas();
    Cartas(char a,char b) :Naipe(b) ,valor(a){}
};
#endif // CARTAS_H
