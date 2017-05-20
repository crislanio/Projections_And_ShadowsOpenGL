#ifndef SOL_H
#define SOL_H

#include "Objeto.h"

class Sol : public Objeto
{

    double raio;

public:

    Sol(double raio);
    virtual ~Sol();

    virtual void atualizar(double tempo);
    virtual void Desenhar_Objeto();
};

#endif // SOL_H
