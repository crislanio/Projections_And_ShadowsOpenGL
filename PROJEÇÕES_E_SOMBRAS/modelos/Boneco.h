#ifndef BONECO_H
#define BONECO_H

#include "Objeto.h"

class Boneco: public Objeto
{
public:
    Boneco();
    ~Boneco();
     virtual void Desenhar_Objeto();

};

#endif // BONECO_H
