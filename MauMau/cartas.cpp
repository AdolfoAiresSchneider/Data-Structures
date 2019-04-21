#include "cartas.h"

bool Cartas::operator<(Cartas &d) const
{
    return this->valor < d.valor || (!(this->valor < d.valor)&& this->Naipe<d.Naipe);
}

Cartas::Cartas()
{

}
