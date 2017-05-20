#include "Objeto.h"

Objeto::Objeto(){

    // translação
    this->tx = 0.0;
    this->ty = 0.0;
    this->tz = 0.0;
    // escala
    this->sx = 1.0;
    this->sy = 1.0;
    this->sz = 1.0;

    // rotação
    this->ax = 0.0;
    this->ay = 0.0;
    this->az = 0.0;

    this->desenharEixos = this->selecionado = false;
    this->qtd_R = this->qtd_G = this->qtd_B = 0;
    this->visivel = true;

}

Objeto::~Objeto(){
}


void Objeto::Desenhar_Objeto(){

    // Aplicando translacao, passando os valores de tx,t e tz.
    glTranslated(tx, ty, tz);
    // Aplicando rotacoes para os valores ax, ay, az
    glRotated(ax, 1,0,0);
    glRotated(ay, 0,1,0);
    glRotated(az, 0,0,1);
    // Aplicando escala passando os valores sx, sy, sz
    glScaled(sx,sy,sz);

}

void Objeto::setRotacao(double x, double y, double z){
    this->ax = x;
    this->ay = y;
    this->az = z;
}

void Objeto::setTranslacao(double x, double y, double z){
    this->tx = x;
    this->ty = y;
    this->tz = z;
}

void Objeto::setEscala(double x, double y, double z){
    this->sx = x;
    this->sy = y;
    this->sz = z;
}

void Objeto::setSelecionado(bool selecionado){
    this->selecionado = selecionado;
}

void Objeto::setDesenharEixos(bool desenharEixos){
    this->desenharEixos = desenharEixos;
}

void Objeto::setCor(float qtd_R, float qtd_G, float qtd_B){
    this->qtd_R = qtd_R;
    this->qtd_G = qtd_G;
    this->qtd_B = qtd_B;
}
void Objeto::setVisivel(bool estado){
    this->visivel = estado;
}

bool Objeto::isSelecionado(){
    return this->selecionado;
}

bool Objeto::isDesenhaEixos(){
    return this->desenharEixos;
}

bool Objeto::isVisivel(){
    return this->visivel;
}

float Objeto::getAX(){
    return this->ax;
}

float Objeto::getAY(){
    return this->ay;
}

float Objeto::getAZ(){
    return this->az;
}

float Objeto::getTX(){
    return this->tx;
}

float Objeto::getTY(){
    return this->ty;
}

float Objeto::getTZ(){
    return this->tz;
}

float Objeto::getSX(){
    return this->sx;
}

float Objeto::getSY(){
    return this->sy;
}

float Objeto::getSZ(){
    return this->sz;
}

float Objeto::getQtd_R(){
    return this->qtd_R;
}

float Objeto::getQtd_G(){
    return this->qtd_G;
}

float Objeto::getQtd_B(){
    return this->qtd_B;
}

int Objeto::getTipo(){
    return this->tipo;
}
