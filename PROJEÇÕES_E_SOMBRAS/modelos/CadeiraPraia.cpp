#include "CadeiraPraia.h"
#include <GL/glut.h>

CadeiraPraia::CadeiraPraia(){
    this->tipo = 9;
}


CadeiraPraia::~CadeiraPraia(){}
void drawCadeiraPraia(void){


}

void CadeiraPraia::Desenhar_Objeto(){
    float qr,qv,qb;
    if(isSelecionado()){
        qr = 0.6, qv = 1, qb = 0.9;
    }else{
          qr = 0.55, qv = 0.34, qb = 0.26;
    }

    glPushMatrix();
        // Rotacoes, transalacao, escala do objeto.
        Objeto::Desenhar_Objeto();
        // setando a cor...
        this->setCor(qr,qv,qb);
        // Cor do objeto
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());


        glColor3d(0.3,0,0);
        glRotatef(15, 0,0,1);
        glPushMatrix();
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);

            Desenha::drawBox(0,0,0,2.2,-0.15,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);

            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);

            Desenha::drawBox(0,0,0,2.2,-0.15,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
        glPopMatrix();

        glRotatef(-15, 0,0,1);
        glPushMatrix();
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);

            Desenha::drawBox(0,0,0,2.2,-0.15,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.2,0,0);

            Desenha::drawBox(0,0,0,2,0.1,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.1,0,0);

            Desenha::drawBox(0,0,0,2.2,-0.15,0.1);
            glTranslated(0, 0, 0.1);
            glColor3d(0.3,0,0);
            Desenha::drawBox(0,0,0,2,0.1,0.1);
        glPopMatrix();

        // Desenha eixos
        if(isDesenhaEixos()){
            Desenha::drawEixos(0.5);
        }


    glPopMatrix();

}
