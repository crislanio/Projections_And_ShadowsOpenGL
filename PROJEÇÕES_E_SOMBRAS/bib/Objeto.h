#ifndef OBJETO_H
#define OBJETO_H

#include <iostream>

#include "model3ds.h"

#include <math.h>
#include <GL/gl.h>
#include <string>
#include <GL/glu.h>
#include<GL/glut.h>

#include "Desenha.h"
#include "Vetor3D.h"
class Objeto{
public:

    float tx;
    float ty;
    float tz;
    float ax;
    float ay;
    float az;
    float sx;
    float sy;
    float sz;
    bool desenharEixos;
    bool selecionado;
    bool visivel;
    Model3DS *modelo_3ds_dog;
    Model3DS *modelo_3ds_aguia;

    float qtd_R, qtd_G, qtd_B; // Cor
    int tipo;

    Objeto();
    ~Objeto();
    // Metodo para desenha o Objeto
    virtual void Desenhar_Objeto();


    // Metodos para alterar dados de possiveis rotacoes, objeto selecionado
    // e desenho dos eixos
    void setRotacao(double x, double y, double z);
    void setTranslacao(double x, double y, double z);
    void setEscala(double x, double y, double z);
    void setSelecionado(bool selecionado);
    void setDesenharEixos(bool desenharEixos);
    void setCor(float qtd_R, float qtd_G, float qtd_B);
    void setVisivel(bool estado);
    bool isSelecionado();
    bool isDesenhaEixos();
    bool isVisivel();

    // Metodos gets
    float getAX();
    float getAY();
    float getAZ();
    float getTX();
    float getTY();
    float getTZ();
    float getSX();
    float getSY();
    float getSZ();
    float getQtd_G();
    float getQtd_R();
    float getQtd_B();
    int getTipo();

};


#endif // OBJETO_H
