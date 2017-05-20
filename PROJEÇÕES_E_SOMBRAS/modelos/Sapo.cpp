#include "Sapo.h"
#include <GL/glut.h>

// referencia> https://www.thiagomedeiros.com/jogos/versao-explicativa-do-jogo-em-opengl-street-frog

Sapo::Sapo(){}
Sapo::~Sapo(){}

void Sapo::Desenhar_Objeto(){
    //Declaracoes das variaveis
    GLint movercarro=0;
    GLint moversapox=0;
    glPushMatrix();

    glColor3f(0.5,1,0);
    glBegin(GL_QUADS);
    glVertex2f (movercarro+2,3.5);
    glVertex2f (movercarro+2,4.5);
    glVertex2f (movercarro+4,4.5);
    glVertex2f (movercarro+4,3.5);
    glEnd();
    glBegin(GL_QUADS);
    glVertex2f (movercarro+1,3.5);
    glVertex2f (movercarro+1,4.0);
    glVertex2f (movercarro+2,4.0);
    glVertex2f (movercarro+2,3.5);
    glEnd();
    glPointSize(5.0);
    glBegin(GL_POINTS);
    glColor3f(0.5,0.5,0.5);
    glVertex2f (movercarro+1.5,3.5);
    glVertex2f (movercarro+3.5,3.5);
    glEnd();
    glPopMatrix();

}
