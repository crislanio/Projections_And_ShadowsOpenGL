#ifndef BANCO_H
#define BANCO_H
#include "Objeto.h"

class Banco: public Objeto
{
public:
    Banco();
    ~Banco();
    virtual void Desenhar_Objeto(bool sombra = false);
};

#endif // BANCO_H
