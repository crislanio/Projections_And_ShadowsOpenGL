#include "Placa.h"
#include "GL/glut.h"

Placa::Placa(){
    this->tipo = 5;
}
Placa::~Placa(){}

void Placa::Desenhar_Objeto(bool sombra){

    float qr,qv,qb;
    if(isSelecionado()){
        qr = 1, qv = 1, qb = 1;
    }else{
        qr = 0.87, qv = 0.72, qb = 0.53;
    }
    glPushMatrix();
        Objeto::Desenhar_Objeto();

        // setando a cor...
        this->setCor(qr,qv,qb);
        // Cor do objeto
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
        glScalef(1.5,1.5,1.5);
        glTranslatef(0,1,0);

        glPushMatrix();
            glScalef(0.1, 2, 0.1);
            glutSolidCube(1);
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0, 0.8, 0.05);
        glPushMatrix();
            glScalef(0.5, 0.3, 0.04);
            glutSolidCube(1);
        glPopMatrix();

        glBegin(GL_TRIANGLES);
            glNormal3f(0, 0, 1);
            glVertex3d(-0.25, 0.15, 0.02);
            glVertex3f(-0.4, 0, 0.02);
            glVertex3d(-0.25, -0.15, 0.02);
            glNormal3f(0, 0, -1);
            glVertex3d(-0.25, -0.15, -0.02);
            glVertex3f(-0.4, 0, -0.02);
            glVertex3d(-0.25, 0.15, -0.02);
        glEnd();

        glBegin(GL_QUADS);
            glNormal3f(1, -1, 0);
            glVertex3d(-0.25, -0.15, 0.02);
            glVertex3d(-0.25, -0.15, -0.02);
            glVertex3f(-0.4, 0, -0.02);
            glVertex3f(-0.4, 0, 0.02);
        glEnd();

        glBegin(GL_QUADS);
            glNormal3f(1, 1, 0);
            glVertex3f(-0.4, 0, -0.02);
            glVertex3f(-0.4, 0, 0.02);
            glVertex3d(-0.25, 0.15, 0.02);
            glVertex3d(-0.25, 0.15, -0.02);
        glEnd();
        glPopMatrix();

        glPopMatrix();

        glPopMatrix();

        // Em caso de TRUE, desenha os eixos
        if(isDesenhaEixos()){
           Desenha::drawEixos(0.5);
        }

    glPopMatrix();



}
