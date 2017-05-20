#include "Casa.h"
#include "GL/glut.h"

Casa::Casa(){
    this->tipo = 1;
}
Casa::~Casa(){}

void Casa::Desenhar_Objeto(bool sombra){

    float qr,qv,qb;
    float qr1,qv1,qb1;
    float qr2,qv2,qb2;
    // Alternar a cor
    if(isSelecionado()){
        qr = 1, qv = 1, qb = 1;
        qr1 = 1,qv1 = 1,qb1 = 1;
        qr2 = 1,qv2 = 1,qb2 = 1;
    }else{
        qr = 1, qv = 2, qb = 28; // Paredes da casa
        qr1 = 0.2,qv1 = 0.3,qb1 = 0.4; // teto
        qr2 = 0.2,qv2 = 0.56,qb2 = 0.7; // chamine
    }
    glPushMatrix();

    Objeto::Desenhar_Objeto();
    /*
     *Casa
    *Paredes da Casa */
    //cor das paredes
    this->setCor(qr,qv,qb);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }
    Desenha::drawBox(0,0,-3.5,5,2.2,0);

    // Laterais de cima da casa
    glBegin(GL_TRIANGLES);
        // Lado esquerdo
        glNormal3f(-1,0,0);
        glVertex3d( 0.0, 2.2, -3.51);
        glVertex3d( 0.0, 2.2, 0.01);
        glVertex3d( 0.0, 3.8, -1.8);

        // Lado Direito
        glNormal3f(1,0,0);
        glVertex3d( 5.0, 2.2, -3.51);
        glVertex3d( 5.0, 2.2, 0.01);
        glVertex3d( 5.0, 3.8, -1.8);

    glEnd();

    /* Portas da Casa */
    // Porta da frente
    glBegin(GL_POLYGON);
      glColor3d(0.55,0,0);
        glVertex3d( 2.2, 0.0, 0.01 );
        glVertex3d( 3.0, 0.0, 0.01 );
        glVertex3d( 3.0, 1.5, 0.01 );
        glVertex3d( 2.2, 1.5, 0.01 );
    glEnd();

    // Porta de tras
    glBegin(GL_POLYGON);
      glColor3d(0.55,0,0);
        glVertex3d( 0.6, 0.0, -3.51);
        glVertex3d( 1.4, 0.0, -3.51 );
        glVertex3d( 1.4, 1.5, -3.51 );
        glVertex3d( 0.6, 1.5, -3.51 );
    glEnd();

    /* Janelas da Casa */
    // Janela lateral lado direito
    glBegin(GL_POLYGON);
      glColor3d(0.55,0,0);
        glVertex3d( 5.01, 1.0, -0.8 );
        glVertex3d( 5, 1.0, -1.4 );
        glVertex3d( 5, 1.5, -1.4 );
        glVertex3d( 5.01, 1.5, -0.8 );
    glEnd();


    glBegin(GL_POLYGON);
        glColor3d(0.55,0,0);
        glVertex3d( 5.01, 1.0, -2.2);
        glVertex3d( 5, 1.0, -2.8 );
        glVertex3d( 5, 1.5, -2.8 );
        glVertex3d( 5.01, 1.5, -2.2);
    glEnd();

    /* Teto da Casa */
    // cor do teto
    this->setCor(qr1,qv1,qb1);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }
    // Parte de cima do teto
    glBegin(GL_POLYGON);
        glVertex3d( 0, 2, 0.23);
        glVertex3d( 0, 3.8, -1.8);
        glVertex3d( 5, 3.8, -1.8);
        glVertex3d( 5, 2, 0.23);
    glEnd();

    glBegin(GL_POLYGON);
        glVertex3d( 0, 2, -3.72);
        glVertex3d( 0, 3.8, -1.8);
        glVertex3d( 5, 3.8, -1.8);
        glVertex3d( 5, 2, -3.72);
    glEnd();

    // Chamine
    this->setCor(qr2,qv2,qb2);
    if (!sombra){
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
    }
    Desenha::drawBox(0.2,3.0,-1.2, 0.6, 4.0, -1.6);
    Desenha::drawBox(0.17,3.9,-1.2, 0.63, 4.0, -1.6);

    // Desenha os eixos na posicao atual do objeto
    if(isDesenhaEixos()){
       Desenha::drawEixos(0.5);
    }

    glPopMatrix();

}
