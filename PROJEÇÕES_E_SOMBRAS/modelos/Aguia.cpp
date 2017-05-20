#include "Aguia.h"
#include "GL/glut.h"

Aguia::Aguia()
{
//     this->tipo = 10;
    this-> modelo_3ds_aguia = new Model3DS ("/home/lupum/MEGA/UFC/2017/1°SEM/Computação Gráfica/RUBENS DROPBOX/dropbox_alunos/trabalhos/Trabalho1/release/3ds/EAGLE.3ds");
}

Aguia::~Aguia(){}


void Aguia::Desenhar_Objeto(){

    glPushMatrix();

        Objeto::Desenhar_Objeto();

        float qr,qg,qb;
        if(isSelecionado()){
            qr = 1, qg = 1, qb = 1;
        }else{
            qr = 0.3, qg = 0.3, qb = 0.3;
        }

        this->setCor(qr,qg,qb);
        glColor3f(this->getQtd_R(), this->getQtd_G(), this->getQtd_B());

        glRotatef(-90,1,0,0);
        glScalef(0.5,0.5,0.5);
        this->modelo_3ds_aguia->draw();

        if(isDesenhaEixos()){
           Desenha::drawEixos(0.5);
        }

    glPopMatrix();
}

