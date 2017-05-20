#include "Arvore.h"
#include "GL/glut.h"

Arvore::Arvore(){
    this->tipo = 7;
}
Arvore::~Arvore(){}

void Arvore::Desenhar_Objeto(bool sombra){
    // Alternado a cor
    float qr,qg,qb;
    float qr2,qg2,qb2;
    if(isSelecionado()){
        qr = 1, qg = 0.34, qb = 1;
        qr2 = 0.34, qg2 = 0.1, qb2 = 0.1;
    }else{
        qr = 0.2, qg = 51, qb = 0;
        qr2 = 0.13, qg2 = 0.8, qb2 = 0.6;
    }

    glPushMatrix();
        Objeto::Desenhar_Objeto();

        // setando a cor do tronco
        this->setCor(qr,qg,qb);
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
//        glColor3b(102,51,0);
        glRotated(-90,1,0,0);
//        glTranslated(-6.5,1,1);
        glutSolidCube(0.6);

        // setando a cor do tronco
        this->setCor(qr2,qg2,qb2);
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
//      glColor3d(0.13, 0.55, 0.13);
           // Segundo cone
        glTranslated(0,0,0.4);
        // setando a cor da parte de cima
        glutSolidCone(1.5, 8, 40, 20);
        if(isDesenhaEixos()){
           Desenha::drawEixos(0.5);
        }
    glPopMatrix();
}
