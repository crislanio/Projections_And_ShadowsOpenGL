#ifndef PONTODEDESCANSO_H
#define PONTODEDESCANSO_H

#include "Objeto.h"

class PontoDeDescanso: public Objeto{
public:
    PontoDeDescanso();
    ~PontoDeDescanso();
   virtual void Desenhar_Objeto(bool sombra =false);
};

#endif // PONTODEDESCANSO_H
