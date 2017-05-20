#ifndef SAPO_H
#define SAPO_H
#include "Objeto.h"

class Sapo: public Objeto
{
public:
    Sapo();
    ~Sapo();
    virtual void Desenhar_Objeto();
};

#endif // SAPO_H
