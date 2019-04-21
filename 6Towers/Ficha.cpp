#include "Ficha.h"

Ficha::Ficha()
{
    jogador = cor = Torre = '@';
}

Ficha::Ficha(char a, char b, char c)
{
    this->cor = b;
    this->jogador = a;
    this->Torre = c;
}
