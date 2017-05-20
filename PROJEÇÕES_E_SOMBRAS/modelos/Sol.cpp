#include "Sol.h"

Sol::Sol(double raio)
{
    this->raio = raio;
}

Sol::~Sol()
{

}

void Sol::atualizar(double tempo)
{

}

void Sol::Desenhar_Objeto()
{
    {
        const GLfloat light_ambient[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
        glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    }


    glColor3d(1.0f, 1.0f, 0.0f);
    glutSolidSphere(raio, 100, 100);


    const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);

}

