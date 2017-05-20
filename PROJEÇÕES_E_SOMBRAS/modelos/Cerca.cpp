#include "Cerca.h"
#include "GL/glut.h"

Cerca::Cerca(){
    this->tipo = 4;
}
Cerca::~Cerca(){}

void Cerca::Desenhar_Objeto(bool sombra)
{
    float qr,qv,qb;
    if(isSelecionado()){
        qr = 0.3, qv = 0.3, qb = 0.3;
        //glColor3f(1,0,0);
    }else{
        qr = 0.87, qv = 0.72, qb = 0.53;
    }
    glPushMatrix();
        Objeto::Desenhar_Objeto();

        glScalef(0.6,0.6,0.6);

        glTranslatef(0,1.25,0);

        if (!sombra){
            glColor3f(0.55, 0.34, 0.26);
        }
        glPushMatrix();
        this->setCor(qr,qv,qb);
         if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
         }
            glScalef(0.3, 2.5, 0.3);
            glutSolidCube(1);
            glTranslatef(-6.5, 0, 0);
            glutSolidCube(1);
            glTranslatef(13, 0, 0);
            glutSolidCube(1);
            glTranslatef(14, 0, 0);
            glutSolidCube(1);
            glTranslatef(-41, 0, 0);
            glutSolidCube(1);
       glPopMatrix();

        glPushMatrix();
        this->setCor(qr,qv,qb);
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
            glScalef(16, 0.4, 0.1);
            glTranslatef(0,2,0);
            glutSolidCube(1);
            glTranslatef(0,-2,0);
            glutSolidCube(1);
            glTranslatef(0,-2,0);
            glutSolidCube(1);

        glPopMatrix();

        // Em caso de TRUE, desenha os eixos
        if(isDesenhaEixos()){
           Desenha::drawEixos(0.5);
        }
    glPopMatrix();

}
