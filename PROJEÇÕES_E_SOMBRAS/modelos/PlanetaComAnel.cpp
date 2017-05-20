#include "PlanetaComAnel.h"


PlanetaComAnel::PlanetaComAnel(Coord posicao, double distancia, double raio, double velocidade, Cor cor)
              : Planeta(posicao, distancia, raio, velocidade, cor)
{

}

PlanetaComAnel::~PlanetaComAnel()
{

}

void PlanetaComAnel::atualizar(double tempo)
{
    posicao.x = 2.0d*distancia*cos(velocidade*tempo) + distancia;
    posicao.z = distancia*sin(velocidade*tempo);
}

void PlanetaComAnel::Desenhar_Objeto()
{

    glTranslated(posicao.x, posicao.y, posicao.z);
    glRotated(45, 1,0,0);
    glColor3d(cor.r, cor.g, cor.b);
    glutSolidTorus(0.1*raio,1.5f*raio, 25, 25);
    glutSolidSphere(raio, 25, 25);
}

