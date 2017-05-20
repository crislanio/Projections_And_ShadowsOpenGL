#include "Planeta.h"

Planeta::Planeta(Coord posicao, double distancia, double raio, double velocidade, Cor cor)
{
    this->posicao = posicao;
    this->distancia = distancia;
    this->raio = raio;
    this->velocidade = velocidade;
    this->cor = cor;
}

void Planeta::atualizar(double tempo)
{
    posicao.x = 2.0d*distancia*cos(velocidade*tempo) + distancia;
    posicao.z = distancia*sin(velocidade*tempo);
}

void Planeta::Desenhar_Objeto()
{
    glTranslated(posicao.x, posicao.y, posicao.z);
    glColor3d(cor.r, cor.g, cor.b);
//    glColor3d(0.3, 0.2, 0.33);
    glutSolidSphere(raio, 25, 25);
}

Planeta::~Planeta()
{

}

double Planeta::getDistancia() const
{
    return distancia;
}


double Planeta::getRaio() const
{
    return raio;
}

void Planeta::setRaio(double value)
{
    raio = value;
}

void Planeta::setDistancia(double value)
{
    distancia = value;
}
