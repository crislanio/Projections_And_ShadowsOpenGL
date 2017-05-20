#ifndef DOG_H
#define DOG_H


#include "Objeto.h"


class Dog: public Objeto
{
public:
    Dog();
    ~Dog();
    void Desenhar_Objeto();
};

#endif // DOG_H
