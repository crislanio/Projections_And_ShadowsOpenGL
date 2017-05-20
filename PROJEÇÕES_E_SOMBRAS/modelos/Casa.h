#ifndef CASA_H
#define CASA_H

#include "Objeto.h"

class Casa: public Objeto{

public:
    Casa();
    ~Casa();
    void Desenhar_Objeto(bool sombra = false);
};

#endif // CASA_H
