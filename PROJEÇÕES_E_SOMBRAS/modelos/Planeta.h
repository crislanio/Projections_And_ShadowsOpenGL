#ifndef PLANETA_H
#define PLANETA_H

#include "Objeto.h"
#include <cmath>

class Planeta : public Objeto
{
protected:
    double raio;
    double distancia;
    double velocidade;

public:

    Planeta(Coord, double, double, double, Cor);
    virtual ~Planeta();

    virtual void atualizar(double);
    virtual void Desenhar_Objeto();

    double getRaio() const;
    void setRaio(double value);
    double getDistancia() const;
    void setDistancia(double value);

};

#endif // PLANETA_H
