#ifndef PLACA_H
#define PLACA_H

#include "Objeto.h"

class Placa: public Objeto
{
public:
    Placa();
    ~Placa();
    void Desenhar_Objeto(bool sombra = false);
};

#endif // PLACA_H
