#ifndef CADEIRAPRAIA_H
#define CADEIRAPRAIA_H

#include"Objeto.h"

class CadeiraPraia: public Objeto
{
public:
    CadeiraPraia();
    ~CadeiraPraia();
    virtual void Desenhar_Objeto();
};

#endif // CHAO_H
