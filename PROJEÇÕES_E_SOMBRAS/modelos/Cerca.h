#ifndef CERCA_H
#define CERCA_H
#include "Objeto.h"


class Cerca: public Objeto
{
public:
    Cerca();
    ~Cerca();
    virtual void Desenhar_Objeto(bool sombra = false);
};

#endif // CERCA_H
