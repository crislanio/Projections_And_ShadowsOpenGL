#include "Banco.h"
#include <GL/glut.h>

Banco::Banco(){
    this->tipo = 6;
}


Banco::~Banco(){}

void Banco::Desenhar_Objeto(bool sombra){
        float qr,qv,qb;
        if(isSelecionado()){
          qr = 1, qv = 1, qb = 1;
        }else{
          qr = 0.96, qv = 0.64, qb = 0.38;
        }

    glPushMatrix();
        // Rotacoes, transalacao, escala do objeto.
        Objeto::Desenhar_Objeto();

        // Desenha eixos
        if(isDesenhaEixos()){
            Desenha::drawEixos(0.5);
        }

        // setando a cor...
        this->setCor(qr,qv,qb);

        // Cor do objeto
        if (!sombra){
            glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());
        }
        //Pilar 1
        Desenha::drawBox(0.5,0,-0.3,
                         3,0.3,0);

        //Parte superior
        Desenha::drawBox(0.4,0.3,-.8,
                         3,0.5,0);


    glPopMatrix();

}
