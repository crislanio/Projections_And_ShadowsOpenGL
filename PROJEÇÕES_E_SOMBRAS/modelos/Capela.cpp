#include "Capela.h"
#include "GL/glut.h"

Capela::Capela(){
    this->tipo = 3;
}
Capela::~Capela(){}

void Capela::Desenhar_Objeto(bool sombra){
    float qr,qv,qb;
    float qr1,qv1,qb1;
    float qr2,qv2,qb2;
    float qr3,qv3,qb3;
    // Alternar a cor
    if(isSelecionado()){
        qr = 1, qv = 1, qb = 1;
        qr1 = 1,qv1 = 1,qb1 = 1;
        qr2 = 1,qv2 = 1,qb2 = 1;
    }else{
        qr = 0.55, qv = 0.34, qb = 0.26;
        qr1 = 0.35,qv1 = 0.25,qb1 = 0.77;
        qr2 = 0.65,qv2 = 0.16,qb2 = 0.16;
        qr3 = 0.88,qv3 = 0.164,qb3 = 0.164;

    }
glPushMatrix();
    Objeto::Desenhar_Objeto();
    glTranslatef(0,2.5,0);
    glScalef(2.5,2.5,2.5);

    //base
    this->setCor(qr2,qv2,qb2);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }

    glPushMatrix();
        glScalef(2.5, 2, 4);
        glutSolidCube(1);
    glPopMatrix();

    //teto
    this->setCor(qr,qv,qb);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }

    glPushMatrix();
        glTranslatef(-0.7,1.6,0);
        glRotatef(-40, 0,0,1);
        glScalef(0.1,2.26,3.99);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.7,1.6,0);
        glRotatef(40, 0,0,1);
        glScalef(0.1,2.26,3.99);
        glutSolidCube(1);
    glPopMatrix();


    this->setCor(qr1,qv1,qb1);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }
    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,1);
        glVertex3f(1.25,1,2.01);
        glVertex3f(-1.25,1,2.01);
        glVertex3f(0,2.4,2.01);
    glEnd();

    glBegin(GL_TRIANGLES);
        glNormal3f(0,0,-1);
        glVertex3f(1.25,1,-2.01);
        glVertex3f(-1.25,1,-2.01);
        glVertex3f(0,2.4,-2.01);
    glEnd();

    glPushMatrix();
        glTranslatef(0, 2, -1);
        glPushMatrix();
            this->setCor(qr3,qv3,qb3);
            if (!sombra){
                glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
            }

            glTranslatef(0, 1, 0);
            glRotatef(-90, 1, 0, 0);
            glRotatef(-45*3, 0,0,1);
            glBegin(GL_POLYGON);
                glutSolidCone(0.6, 2, 4, 4);
            glEnd();
        glPopMatrix();
        this->setCor(qr,qv,qb);
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
         glScalef(0.8, 2, 0.8);
        glutSolidCube(1);
    glPopMatrix();

    // porta
    glBegin(GL_QUADS);
        glNormal3f(0,0,1);
        glVertex3f(0.6, -1, 2.01);
        glVertex3f(0.6, 0.5, 2.01);
        glVertex3f(-0.6, 0.5, 2.01);
        glVertex3f(-0.6, -1, 2.01);
    glEnd();
    glPushMatrix();
        glTranslatef(0,-0.25,2.01);
        glPushMatrix();
            glTranslatef(-0.6, 0,0);
            glScalef(0.08, 1.5, 0.08);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0.6, 0,0);
            glScalef(0.08, 1.5, 0.08);
            glutSolidCube(1);
        glPopMatrix();
        glPushMatrix();
            glTranslatef(0,0.71,0);
            glRotatef(90, 0,0,1);
            glScalef(0.08, 1.2, 0.08);
            glutSolidCube(1);
        glPopMatrix();
    glPopMatrix();

glPopMatrix();
}

