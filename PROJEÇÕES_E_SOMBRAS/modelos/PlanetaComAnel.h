#ifndef PLANETACOMANEL_H
#define PLANETACOMANEL_H

#include "Planeta.h"

class PlanetaComAnel : public Planeta
{
public:
    PlanetaComAnel(Coord posicao , double distancia, double raio, double velocidade, Cor cor);
    virtual ~PlanetaComAnel();

    virtual void atualizar(double tempo);
    virtual void Desenhar_Objeto();

};

#endif // PLANETACOMANEL_H
