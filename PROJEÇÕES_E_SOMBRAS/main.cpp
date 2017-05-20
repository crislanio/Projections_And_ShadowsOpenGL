#include <GL/glut.h>
#include <iostream>
#include <iomanip>
#include <vector>
#include "modelos/Banco.h"
#include "modelos/Cerca.h"
#include "modelos/Arvore.h"
#include "modelos/Placa.h"


//*** LUZ AMBIENTE é a parte constante, se tiver a LUZ DIFUSA E ESPECULAR fica 2D. Difusa fica aquele efeito degradê.

using namespace std;

#include "CameraDistante.h"
#include "Desenha.h"

#include "gui.h"

#include "stanfordbunny.h"
#include "model3ds.h"

GLuint gBunnyWireList = NULL;
GLuint gBunnySolidList = NULL;

string str;

//variaveis globais
int width = 800;
int height = 600;

int slices = 16;
int stacks = 16;

float trans_obj = false;
float trans_luz = false;

float tx = 0.0;
float ty = 0.0;
float tz = 0.0;

float ax = 0.0;
float ay = 0.0;
float az = 0.0;

float delta = 5.0;

float sx = 1.0;
float sy = 1.0;
float sz = 1.0;

//ponto em coords locais, a ser calculado em coords de mundo
float pl[4] = { 0.0, 0.0, 0.0, 1.0 };
//ponto em coords globais, resultado da conversao a partir de pl
float pg[4] = { 0.0, 0.0, 0.0, 1.0 };

bool lbpressed = false;
bool mbpressed = false;
bool rbpressed = false;

float last_x = 0.0;
float last_y = 0.0;

Camera* cam = new CameraDistante();
float savedCamera[9];

Camera* cam2 = new CameraDistante(-3,2,-5, 0,0,0, 0,1,0);
//Camera* cam2 = new CameraDistante(2,1,0, 2,1,-5, -1,0,0);
bool manual_cam = false;
bool change_manual_cam = false;

GLfloat light_position[] = { 1.5f, 1.5f, 1.5f, 1.0f };


Banco *banco = new Banco();
Cerca *cerca = new Cerca();
Arvore*arvore= new Arvore();
Placa*placa= new Placa();

// Vetor de objetos base
vector<Objeto*> objs;

//subrotinas extras
void mult_matriz_vetor(float res[4], float matriz[16], float entr[4]) {
    for (int i = 0; i < 4; i++) {
        res[i] = 0.0;
        for (int j = 0; j < 4; j++) {
            //res[i] += matriz[4*i+j] * entr[j];
            res[i] += matriz[4*j+i] * entr[j]; //matriz^T.entr
        }
    }
}

void mostra_matriz_transform(float matriz[16], bool transposta = true) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!transposta) {
                cout << setiosflags (ios::fixed) << setprecision(2) << matriz[4*i+j] << "  ";
            } else {
                cout << setiosflags (ios::fixed) << setprecision(2) << matriz[4*j+i] << "  "; //matriz^T
            }
        }
        cout << "\n";
    }
    //cout << "\n";
}

void imprime_coords_locais_globais()
{
    //imprimindo coords locais e coords globais
      //locais
        cout << "Coords locais: " << pl[0] << ", " << pl[1] << ", " << pl[2] << "\n";
      //globais
        glMatrixMode(GL_MODELVIEW);
        glPushMatrix();
            glLoadIdentity();
              //composicao de transformacoes
              glTranslated(tx,ty,tz);
              glRotated(az,0,0,1);
              glRotated(ay,0,1,0);
              glRotated(ax,1,0,0);
            float mudanca_sist_coords[16];
            glGetFloatv(GL_MODELVIEW_MATRIX,mudanca_sist_coords);
            cout << "Matriz mudanca sist coords local=>global (T.Rz.Ry.Rx):\n";
            mostra_matriz_transform(mudanca_sist_coords);
            mult_matriz_vetor(pg,mudanca_sist_coords,pl);
            cout << "Coords globais: " << pg[0] << ", " << pg[1] << ", " << pg[2] << "\n\n";
        glPopMatrix();
}

void desenha_camera(float tam) {
    GLUquadricObj *quad = gluNewQuadric();

    glPushMatrix();
      Desenha::drawBox( -tam,-tam,0.0, tam,tam,2*tam );
      glTranslated(0,0,-tam);
      Desenha::gluClosedCylinder(quad, tam, tam/2, tam, slices,stacks);
    glPopMatrix();

    gluDeleteQuadric( quad );
}

void transformacao_camera_2_global(Vetor3D e, Vetor3D c, Vetor3D u, bool mostra_matriz = false)
{
    //z'
    Vetor3D z_ = e - c;
    z_.normaliza();
    //x'
    Vetor3D x_ = u ^ z_;
    x_.normaliza();
    //y'
    Vetor3D y_ = z_ ^ x_;
    //y_.normaliza();

    //matriz de transformacao
        float transform[16] = {
                                x_.x,   y_.x,   z_.x,   e.x,
                                x_.y,   y_.y,   z_.y,   e.y,
                                x_.z,   y_.z,   z_.z,   e.z,
                                0.0,    0.0,    0.0,    1.0
                             };
        glMultTransposeMatrixf( transform );

    if (mostra_matriz) {
        cout << "Matriz mudanca sist coords camera2=>global (R t = x' y' z' e):\n";
        mostra_matriz_transform(transform,false);
        cout << "\n";
    }
}

void transformacao_global_2_camera(Vetor3D e, Vetor3D c, Vetor3D u, bool mostra_matriz = false)
{
    //z'
    Vetor3D z_ = e - c;
    z_.normaliza();
    //x'
    Vetor3D x_ = u ^ z_;
    x_.normaliza();
    //y'
    Vetor3D y_ = z_ ^ x_;
    //y_.normaliza();

    //t'=-R^T.t=R^T.(-e)
    Vetor3D t_;
        t_.x = x_ * ( e * (-1) );
        t_.y = y_ * ( e * (-1) );
        t_.z = z_ * ( e * (-1) );

    //matriz de transformacao
        float transform[16] = {
                                x_.x,   x_.y,   x_.z,   t_.x,
                                y_.x,   y_.y,   y_.z,   t_.y,
                                z_.x,   z_.y,   z_.z,   t_.z,
                                0.0,    0.0,    0.0,    1.0
                             };
        glMultTransposeMatrixf( transform );

    if (mostra_matriz) {
        cout << "Matriz mudanca sist coords global=>camera2 (R^T -R^T.t):\n";
        mostra_matriz_transform(transform,false);
        cout << "\n";
    }
}


/* GLUT callback Handlers */

void resize(int w, int h)
{
    width = w;
    height = h;
}

void displayInit()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//    const float ar = height>0 ? (float) width / (float) height : 1.0;

//    glViewport(0, 0, width, height);

//    glMatrixMode(GL_PROJECTION);
//    glLoadIdentity();
//    gluPerspective(30.,ar,0.1,1000.);

//    //testes
//    //glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
//    //glOrtho(-10.0, 10.0, -10.0, 10.0, -10.0, 10.0);
//    //glOrtho(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//    //glOrtho(-10*ar, 10*ar, -10.0, 10.0, 2.0, 100.0);
//    //glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);
//    //gluPerspective(30.,ar,0.1,1000.);

}

void displayEnd()
{
    glutSwapBuffers();
}

//desenha todos os objetos que possuem sombra
void desenhaObjetosComSombra(bool sombra = false) {
//    glPushMatrix();
////        banco->Desenhar_Objeto(sombra);


//        cerca->Desenhar_Objeto(sombra);
////        arvore->Desenhar_Objeto(sombra);
////          placa->Desenhar_Objeto(sombra);


//    glPopMatrix();

    glPushMatrix();
        //composicao de transformacoes
         glTranslated(tx,ty,tz);
         glRotated(az,0,0,1);
         glRotated(ay,0,1,0);
         glRotated(ax,1,0,0);
         glScaled(sx,sx,sx);

        Desenha::drawBox( 0.0,0.0,0.0, 1.0,1.0,1.0 );
    glPopMatrix();

}

void displayInner(bool manual_cam)
{
    //tempo
    const double t = glutGet(GLUT_ELAPSED_TIME) / 1000.0;
    //cam->e.z = 10+t;
    //tx = t;
    //ay = 100*t;

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    //transformacao de camera
    if (!manual_cam) {
        //definindo posicao e orientacao da camera
        gluLookAt(cam->e.x,cam->e.y,cam->e.z, cam->c.x,cam->c.y,cam->c.z, cam->u.x,cam->u.y,cam->u.z);
    } else {
        //definindo posicao e orientacao da camera 2 "manualmente"
        transformacao_global_2_camera(cam2->e,cam2->c,cam2->u);
    }

    //sistema global
    glPushMatrix();
        //posicao da luz
            glutGUI::trans_luz = trans_luz;
            GUI::setLight(0,light_position[0],light_position[1],light_position[2],false,false);
            glLightfv(GL_LIGHT0, GL_POSITION, light_position);
        //desenhando eixos do sistema de coordenadas global
            Desenha::drawEixos( 0.5 );
        //chao
            glColor3d(0.6,0.4,0.0);
            glTranslated(0.0,-0.001,0.0);
//            Desenha::drawGrid( 10, 0, 10, 1 );
            GUI::drawFloor(15.0,20.0,0.5,0.5);

// PAREDES
            glPushMatrix();
                glTranslated(-3.0, 0.0, -3.0);
//                GUI::drawBox(0.2, 0.0, -1.1, 4.5 , 4.5, 0.1); // PAREDE FRONTAL z =0.1
                GUI::drawBox(0.2, 0.0, -6.1, 4.5 , 7.5, -5.1); // PAREDE FRONTAL z =0.1
                GUI::drawBox(4.4, 0.0, -6.1, 5.0 , 7.5, 4.0); // PAREDE LATERAL x = 4.0

//                GUI::drawBox(4.4, 0.0, -1.1, 5.0 , 4.5, 4.0); // PAREDE LATERAL x = 4.0
            glPopMatrix();

    glPopMatrix();

    //sistema local 1 com sombra
    glPushMatrix();
        glColor3d(0.3,0.3,0.3);
        desenhaObjetosComSombra();
    glPopMatrix();

// SOMPRA NO CHÃO y=0
    glPushMatrix();
    {
        //matriz p multiplicar tudo por -1
            //float neg[16] = {
            //                   -1.0, 0.0, 0.0, 0.0,
            //                    0.0,-1.0, 0.0, 0.0,
            //                    0.0, 0.0,-1.0, 0.0,
            //                    0.0, 0.0, 0.0,-1.0
            //                };
            //glMultTransposeMatrixf( neg );
        //matriz de projecao para gerar sombra no plano y=0
            float sombra[16] = {
                                 light_position[1], -light_position[0],                0.0,                0.0,
                                               0.0,                0.0,                0.0,                0.0,
                                               0.0, -light_position[2],  light_position[1],                0.0,
                                               0.0, -light_position[3],                0.0,  light_position[1]
                               };
            glMultTransposeMatrixf( sombra );
        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        desenhaObjetosComSombra(true);
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();



 //PAREDE frontal * LATERAL
    glPushMatrix();
    {
        //matriz p multiplicar tudo por -1
            //float neg[16] = {
            //                   -1.0, 0.0, 0.0, 0.0,
            //                    0.0,-1.0, 0.0, 0.0,
            //                    0.0, 0.0,-1.0, 0.0,
            //                    0.0, 0.0, 0.0,-1.0
            //                };
            //glMultTransposeMatrixf( neg );
        //matriz de projecao para gerar sombra no plano y=3

// TESTE 00
    //         MEU EXEMPLO parede lateral
//                float sombra[16] = {

//                            0.1*light_position[0], 0.0, 0.0, 1.3*light_position[3], //1° DEIXAR LARGO O OBJ. 4° DIREITA MOVE
//                            0.0, 0.75*light_position[1], 0.0, 0.0, //2° TAM. AUTURA,  4° PRA FICAR NO CHÃO
//                            0.0, 0.0, 0.75*light_position[2], -2.9*light_position[3], // 3° DEIXAR OBJ COMMT ESPESSURA NO EIXO z, 4° PROF. OBJ
//                            0.0, 0.0, 0.0, 1*light_position[3] // 4° 1.0 OBJ GRANDE, PEQUENO
//                };

// TESTE 01
//            float sombra[16] = {
//            // exemplo desenho o objeto
//                                    0.75*light_position[0], 0.0, 0.0, 0.5*light_position[3], //1° DEIXAR LARGO O OBJ. 4° DIREITA MOVE
//                                    0.0, 0.75*light_position[1], 0.0, 0.0, //2° TAM. AUTURA,  4° PRA FICAR NO CHÃO
//                                    0.0, 0.0, 0.05*light_position[2], -2.9*light_position[3], // 3° DEIXAR OBJ COMMT ESPESSURA NO EIXO z, 4° PROF. OBJ
//                                    0.0, 0.0, 0.0, 1*light_position[3] // 4° 1.0
//            };

// TESTE 02
//        float sombra[16] = {
//            // exemplo desenho o objeto X=0
//                                    0.0, 0.0, 0.0, 1.8, //1° DEIXAR LARGO O OBJ. 4° DIREITA MOVE
//                                    -light_position[1], light_position[0], 0.0, 0.0, //2° TAM. AUTURA,  4° PRA FICAR NO CHÃO
//                                    -light_position[2], 0.0, light_position[0], -2.9, // 3° DEIXAR OBJ COMMT ESPESSURA NO EIXO z, 4° PROF. OBJ
//                                    -1.0, 0.0, 0.0, light_position[0] // 4° 1.0
//        };

        //EIXO X = 1.37 ** oficial
            float k = 1.37;
            float sombra[16] = {
                                            k,                      0.0,                      0.0,  -k*light_position[0],
                            light_position[1],   (-light_position[0]+k),                      0.0,  -k*light_position[1],
                            light_position[2],                      0.0,   (-light_position[0]+k),  -k*light_position[2],
                                          1.0,                      0.0,                      0.0,    -light_position[0]
            };

        glMultTransposeMatrixf( sombra );
        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        desenhaObjetosComSombra(true);
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();


// PARECE lateral
glPushMatrix();
    {
        //matriz p multiplicar tudo por -1
            float neg[16] = {
                               -1.0, 0.0, 0.0, 0.0,
                                0.0,-1.0, 0.0, 0.0,
                                0.0, 0.0,-1.0, 0.0,
                                0.0, 0.0, 0.0,-1.0
                            };
            glMultTransposeMatrixf( neg );
//matriz de projecao para gerar sombra no plano y=0

//             TESTE 0 EIXO Z=0
//            float sombra[16] = {
//                light_position[2], 0.0, -light_position[0], 0.0, //1° DEIXAR LARGO O OBJ. 4° DIREITA MOVE (0.6)
//                0.0, light_position[2], -light_position[1], 0.0, //2° TAM. AUTURA,  4° PRA FICAR NO CHÃO
//                0.0, 0.0, -6.1, 0.0, //2° PRA ONDE APONTA A SOMBRA 3° DEIXAR OBJ COM MT (-4.3) ESPESSURA NO EIXO z, 4° PROF. OBJ
//                0.0, -0.5, -1.0, light_position[2] // 1° angulo abertura sombra (-0.50)4° 1.0 OBJ GRANDE, PEQUENO
//                };



////             TESTE 1 EIXO Z=0
//            float sombra[16] = {

//                        light_position[2], 0.0, -light_position[0], 0.6, //1° DEIXAR LARGO O OBJ. 4° DIREITA MOVE
//                        0.0, light_position[2], -light_position[1], 0.0, //2° TAM. AUTURA,  4° PRA FICAR NO CHÃO
//                        0.0, 0.0, 0.0, -4.3, // 3° DEIXAR OBJ COM MT (-4.3) ESPESSURA NO EIXO z, 4° PROF. OBJ
//                        0.0, 0.0, -1.0, light_position[2] // 4° 1.0 OBJ GRANDE, PEQUENO
//                                };

//// EIXO Z= 2.9 n dc
//         float sombra[16] = {

//                    (-light_position[2]+2.9),     -2.9,     light_position[0],      -2.9*(light_position[0]),
//                          0.0,      (-light_position[2]+2.9),  light_position[1],   -2.9*(light_position[1]),
//                          0.0,             0.0,                2.9,                 -2.9*(light_position[2]),
//                          0.0 ,            0.0,                1,                   -light_position[2]
//            };

        float k = -8.099;
        float sombra[16] = {
                      (-light_position[2]+k),                      0.0,    light_position[0],  -k*light_position[0],
                                         0.0,   (-light_position[2]+k),    light_position[1],  -k*light_position[1],
                                         0.0,                      0.0,                    k,  -k*light_position[2],
                                         0.0,                      0.0,                  1.0,    -light_position[2]
        };

        glMultTransposeMatrixf( sombra );
        glDisable(GL_LIGHTING);
        glColor3d(0.0,0.0,0.0);
        desenhaObjetosComSombra(true);
        glEnable(GL_LIGHTING);
    }
    glPopMatrix();



    //sistema local 1 com distorção de projeção
    //glPushMatrix();
    //    glColor3d(0.3,0.3,0.3);
    //    glTranslatef(-0.5,-0.5,-2.5);
    //    desenhaObjetosComSombra();
    //glPopMatrix();
    //glPushMatrix();
    //    glColor3d(0.3,0.3,0.3);
    //    //glTranslatef(2.,0,0);
    //    //matriz p multiplicar z por -1
    //        float zNeg[16] = {
    //                            1.0, 0.0, 0.0, 0.0,
    //                            0.0, 1.0, 0.0, 0.0,
    //                            0.0, 0.0,-1.0, 0.0,
    //                            0.0, 0.0, 0.0, 1.0
    //                         };
    //        glMultTransposeMatrixf( zNeg );
    //    //matriz de projecao perspectiva
    //        gluPerspective(30.,1.,1.5,2.5);
    //        //glFrustum(-1.0, 1.0, -1.0, 1.0, 1.5, 2.5);
    //    //matriz de projecao ortografica
    //        //glOrtho(-1.0, 1.0, -1.0, 1.0, 1.0, 3.0);
    //    glTranslatef(-0.5,-0.5,-2.5);
    //    desenhaObjetosComSombra();
    //glPopMatrix();

    //matriz de projecao perspectiva (gluPerspective)
    //    float far = 2.5;
    //    float near = 1.5;
    //    float esq = (far+near)/(far-near);
    //    float dir = (2*far*near)/(far-near);
    //    float persp[16] = {
    //                        1.0, 0.0, 0.0, 0.0,
    //                        0.0, 1.0, 0.0, 0.0,
    //                        0.0, 0.0, esq, dir,
    //                        0.0, 0.0,-1.0, 0.0
    //                      };
    //glMultTransposeMatrixf( persp );
    //    float fovy = 30.;
    //    float aspect = 1.;
    //    float f = 1./tan((fovy/2.)*(PI/180.));
    //    float pri = f/aspect;
    //    float seg = f;
    //    float Escala[16] = {
    //                          pri, 0.0, 0.0, 0.0,
    //                          0.0, seg, 0.0, 0.0,
    //                          0.0, 0.0, 1.0, 0.0,
    //                          0.0, 0.0, 0.0, 1.0
    //                       };
    //glMultTransposeMatrixf( Escala );

    //sistema local da camera
    if (!manual_cam) {
        glPushMatrix();
            //definindo sistema de coords atraves do glulookat (eye,center,up)
            transformacao_camera_2_global(cam2->e,cam2->c,cam2->u);
            //desenhando eixos do sistema de coordenadas local da camera
              Desenha::drawEixos( 0.5 );
            //desenhando camera
            glColor3d(0.5,0.5,0.0);
            desenha_camera(0.2);
        glPopMatrix();
    } else {
        glPushMatrix();
            //definindo sistema de coords atraves do glulookat (eye,center,up)
            transformacao_camera_2_global(cam->e,cam->c,cam->u);
            //desenhando eixos do sistema de coordenadas local da camera
              Desenha::drawEixos( 0.5 );
            //desenhando camera
            glColor3d(0.5,0.5,0.5);
            desenha_camera(0.2);
        glPopMatrix();
    }

}

void display()
{
    displayInit();
    displayInner(manual_cam);
        //glViewport(0, 0, width, height);
        //displayInner(manual_cam);
        //glViewport(0, 3*height/4, width/4, height/4);
        //displayInner(!manual_cam);
    displayEnd();
}

void mouseButton(int button, int state, int x, int y) {
	// if the left button is pressed
	if (button == GLUT_LEFT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            lbpressed = true;
		} else {// state = GLUT_UP
            lbpressed = false;
		}
	}
	// if the middle button is pressed
	if (button == GLUT_MIDDLE_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            mbpressed = true;
		} else {// state = GLUT_UP
            mbpressed = false;
		}
	}
	// if the left button is pressed
	if (button == GLUT_RIGHT_BUTTON) {
		// when the button is pressed
		if (state == GLUT_DOWN) {
            rbpressed = true;
		} else {// state = GLUT_UP
            rbpressed = false;
		}
	}

    last_x = x;
    last_y = y;
}

void mouseMove(int x, int y) {
    float fator = 10.0;
    if (lbpressed && !rbpressed && !mbpressed) {
        if (!trans_obj) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam->rotatex(y,last_y);
                    cam->rotatey(x,last_x);
                } else {
                    cam2->rotatex(last_y,y);
                    cam2->rotatey(last_x,x);
                }
            } else {
                if (!change_manual_cam) {
                    cam->rotatex(last_y,y);
                    cam->rotatey(last_x,x);
                } else {
                    cam2->rotatex(y,last_y);
                    cam2->rotatey(x,last_x);
                }
            }
        } else {
            ax += (y - last_y)/fator;
            ay += (x - last_x)/fator;
        }
    }
    fator = 100.0;
    if (!lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj && !trans_luz) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam->translatex(x,last_x);
                    cam->translatey(y,last_y);
                } else {
                    cam2->translatex(last_x,x);
                    cam2->translatey(last_y,y);
                }
            } else {
                if (!change_manual_cam) {
                    cam->translatex(last_x,x);
                    cam->translatey(last_y,y);
                } else {
                    cam2->translatex(x,last_x);
                    cam2->translatey(y,last_y);
                }
            }
        } else {
            if (trans_obj) {
                tx += (x - last_x)/fator;
                ty += -(y - last_y)/fator;
            }
            if (trans_luz) {
                light_position[0] += (x - last_x)/fator;
                light_position[1] += -(y - last_y)/fator;
            }
        }
    }
    if (lbpressed && rbpressed && !mbpressed) {
        if (!trans_obj && !trans_luz) {
            if (!manual_cam) {
                if (!change_manual_cam) {
                    cam->zoom(y,last_y);
                } else {
                    cam2->zoom(last_y,y);
                }
            } else {
                if (!change_manual_cam) {
                    cam->zoom(last_y,y);
                } else {
                    cam2->zoom(y,last_y);
                }
            }
        } else {
            if (trans_obj) {
                tz += (y - last_y)/fator;
                fator = 10.0;
                az += -(x - last_x)/fator;
            }
            if (trans_luz) {
                light_position[2] += (y - last_y)/fator;
            }
        }
    }
    fator = 100.0;
    if (!lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            //sx *= 1+(x - last_x)/fator;
            sx += (x - last_x)/fator;
            sy += -(y - last_y)/fator;
        }
    }
    if (lbpressed && !rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            sz += (y - last_y)/fator;
        }
    }
    if (!lbpressed && rbpressed && mbpressed) {
        if (!trans_obj) {
        } else {
            pl[0] += (x - last_x)/fator;
            pl[1] += -(y - last_y)/fator;
            imprime_coords_locais_globais();
        }
    }

    last_x = x;
    last_y = y;
}
void ajuda(){
    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "                                     "<< endl;
    cout << "PROJEÇÕES  PARALELAS"<< endl;
    cout << "caso  R: PROJEÇÃO OBLÍQUA"<< endl;
    cout << "caso  B: PROJEÇÃO ORTOGRÁFICA"<< endl;

    cout << "PROJEÇÕES  EM PERSPECTIVA"<< endl;
    cout << "caso  A: PROJEÇÃO PERSPECTIVA"<< endl;
    cout << "caso  D: PROJEÇÃO PERSPECTIVA"<< endl;
    cout << "caso  E: PROJEÇÃO PERSPECTIVA"<< endl;

    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "                                             PROJEÇÃO ORTOGRÁFICA"<< endl;
    cout << "+++++++++++++++++++++++++++++++++++++"<< endl;
    cout << "help()"<< endl;
    cout << "primeiro aperte F para deixar a tela cheia, depois aperte B para escolher a PROJEÇÃO ORTOGRÁFICA"<< endl;
    cout << "+++++++++++++++++++++++++++++++++++++"<< endl;
    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "Mude as vistas ORTOGRÁFICAS pressionando a tecla c"<< endl;
    cout << "• aperte c  a 1° vez - Front-elevation"<< endl;
    cout << "• aperte c  a 2° vez - Side-elevation"<< endl;
    cout << "• aperte c  a 3° vez - Plan-elevation"<< endl;
    cout << "• DEPOIS DISSO APERTE c mais 2 vezes para alternar entre os testes"<< endl;
    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "Mude as vistas ORTOGRÁFICAS pressionando a tecla i (Projeções axonométricas - Um tipo especial de projeção ORTOGRÁFICA)"<< endl;
    cout << "• aperte i  a 1° vez - Isometric (Ângulos iguais com dois eixos)"<< endl;
    cout << "• aperte i  a 2° vez -  Dimetric Ângulos diferentes com os eixos x, y e z)   "<< endl;
    cout << "• aperte i  a 3° vez - Trimetric(Ângulos iguais com os eixos x, y e z:)"<< endl;
    cout << "• DEPOIS DISSO APERTE i mais 2 vezes para alternar entre os testes"<< endl;


    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "                                             PROJEÇÃO PERSPECTIVA"<< endl;
    cout << "+++++++++++++++++++++++++++++++++++++"<< endl;
    cout << "help()"<< endl;
    cout << "primeiro aperte F para deixar a tela cheia, depois aperte D, A para escolher a PROJEÇÃO PERSPECTIVA"<< endl;
    cout << "+++++++++++++++++++++++++++++++++++++"<< endl;
    cout << "                                     "<< endl;
    cout << "-------------------------------------"<< endl;
    cout << "Mude as vistas PERSPECTIVAS pressionando a tecla d"<< endl;
    cout << "• aperte d  a 1° vez - 1-point perspective"<< endl;
    cout << "• aperte d  a 2° vez - 2-point perspective"<< endl;
    cout << "• aperte d  a 3° vez - 3-point perspective"<< endl;


    cout << "-------------------------------------"<< endl;
    cout << "                                     "<< endl;
    cout << "LUZ"<< endl;
    cout << "caso  p: pontual"<< endl;
    cout << "caso  l:  lanterna"<< endl;


    cout << "caso  q: SAIR DO PROGRAMA"<< endl;
    cout << "caso  F: TELA CHEIA"<< endl;
    cout << "caso  f: TELA PEQUENA"<< endl;
}

void key(unsigned char key, int x, int y)
{
    Objeto *objeto;
    bool eixo;
    static int pos_manual_cam = 0;
    const float ar = height>0 ? (float) width / (float) height : 1.0;

    float s;
    float d; //1.0/2.0;
    float alfa; //30
    //matriz de cisalhamento (projecao obliqua)
    float transform[16] = {
                                    1.0,    0.0,    -d*cos(alfa),    0.0,
                                    0.0,    1.0,    0.0,    0.0,
                                    0.0,    0.0,    1.0,    0.0,
                                    0.0,    0.0,    0.0,    1.0
                                 };


    switch (key)
    {
        // -----------------------------------------------------------
            // MUDANDO PERSPECTIVAS DE CÂMERA - OPÇÕES A,B,D,E
        // -----------------------------------------------------------
        case 'E' :
            // PROJEÇÃO PERSPECTIVA
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(30.,ar,0.1,1000.);
            break;
        case 'B' :
            // PROJEÇÃO ORTOGRÁFICA
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glOrtho(-10*ar, 10*ar, -10.0, 10.0, -100.0, 1000.0);
            break;
        case 'D' :
            // PROJEÇÃO PERSPECTIVA
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            gluPerspective(150.,ar,0.1,1000.); //ângulo de abertura. 1° parâmetro ideia de distênciamento, distorção em relação ao plano. 30 mantem o cenário perfeito.
            break;
        // PROJEÇÃO OBLÍQUA
        case 'R' :
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            s = 3.0;
            glOrtho(-s, s, -s, s, -10.0, 100.0);
            d = 1.0; //1.0/2.0;
            alfa = alfa*(PI/180);
            glMultTransposeMatrixf( transform );
        break;
        case 'A' :
            // PROJEÇÃO PERSPECTIVA
            glMatrixMode(GL_PROJECTION);
            glLoadIdentity();
            glFrustum(-ar, ar, -1.0, 1.0, 2.0, 200.0);
            break;
        case '.':
            cout << " CRIAR Arvore:\n";
            objeto = new Arvore();
            objs.push_back(objeto);
            break;
        case ',':
            cout << " CRIAR Banco:\n";
            objeto = new Banco();
            objs.push_back(objeto);
            break;

        case 'q':
            exit(0);
            break;

        case 'F':
            glutFullScreen();
            break;
        case 'f':
            glutReshapeWindow(800,600);
            break;

        case '+':
            slices++;
            stacks++;
            break;

        case '-':
            if (slices>3 && stacks>3)
            {
                slices--;
                stacks--;
            }
            break;

        case 'X':
            //ax+=delta;
            if(trans_obj) ax+=delta;
            else { pl[0] += 0.01; imprime_coords_locais_globais(); };
            break;

        case 'Y':
            //ay+=delta;
            if(trans_obj) ay+=delta;
            else { pl[1] += 0.01; imprime_coords_locais_globais(); };
            break;

        case 'Z':
            //az+=delta;
            if(trans_obj) az+=delta;
            else { pl[2] += 0.01; imprime_coords_locais_globais(); };
            break;

        case 'x':
            //ax-=delta;
            if(trans_obj) ax-=delta;
            else { pl[0] -= 0.01; imprime_coords_locais_globais(); };
            break;

        case 'y':
            //ay-=delta;
            if(trans_obj) ay-=delta;
            else { pl[1] -= 0.01; imprime_coords_locais_globais(); };
            break;

        case 'z':
            //az-=delta;
            if(trans_obj) az-=delta;
            else { pl[2] -= 0.01; imprime_coords_locais_globais(); };
            break;

        case 't':
            trans_obj = !trans_obj;
            break;

        case 'l':
            trans_luz = !trans_luz;
            break;

        case 'p':
            light_position[3] = 1 - light_position[3];
            break;
 // PARA A PROJEÇÃO ORTOGRÁFICA - Front-elevation, Side-elevation, Plan-elevation
        case 'c':
            static int posCam = 0;
            posCam++;
            if (cam->estilo == 1) {
                delete cam;
                if (posCam%5==0) cam = new CameraDistante(); //CameraDistante(0,1,5, 0,1,0, 0,1,0);
                if (posCam%5==1) cam = new CameraDistante(5,1,0, 0,1,0, 0,1,0);
                // olho onde ela tá, centro pra onde ela tá olhando
                               // é um vetor perpendicular.
                if (posCam%5==2) cam = new CameraDistante(0,1,-5, 0,1,0, 0,1,0);
                if (posCam%5==3) cam = new CameraDistante(0,5,0, 0,1,0, 0,0,-1); // NESSE CASO up é -1 pq ta olhando z negativo. // CameraDistante(1,1,0, 1,0,0, 0,0,-1); // ISOMETRIC
                // como funciona o gluLookat prova

// GUARDA AS POSIÇÕES DA CÂMERA
                if (posCam%5==4) cam = new CameraDistante(savedCamera[0],savedCamera[1],savedCamera[2],savedCamera[3],savedCamera[4],savedCamera[5],savedCamera[6],savedCamera[7],savedCamera[8]);
            } else if (cam->estilo == 2) {
                delete cam;
                cam = new CameraDistante();
            }
            break;
// PARA A PROJEÇÃO ORTOGRÁFICA - Isometric, Dimetric, Trimetric
        case 'i':
            static int posCam3 = 0;
            posCam3++;
            if (cam->estilo == 1) {
                delete cam;
                if (posCam3%5==0) cam = new CameraDistante();
                if (posCam3%5==1) cam = new CameraDistante(5,5,5, 0,0,1, 0,1,0); // ISOMETRIC 3 eixos iguais (x,y 30°)
                if (posCam3%5==2) cam = new CameraDistante(5,0,0, 0,0,5, 0,1,0); // DIMETRIC 2 eixos iguais
                if (posCam3%5==3) cam = new CameraDistante(-64.9617, 46.4857, 71.3579, 5.88033, -3.14202, 6.02176, 0, 1, 0); // TRIMETRIC
                if (posCam3%5==4) cam = new CameraDistante(savedCamera[0],savedCamera[1],savedCamera[2],savedCamera[3],savedCamera[4],savedCamera[5],savedCamera[6],savedCamera[7],savedCamera[8]);
            } else if (cam->estilo == 2) {
                delete cam;
                cam = new CameraDistante();
            }
            break;

        // PARA A PROJEÇÃO ORTOGRÁFICA - Front-elevation, Side-elevation, Plan-elevation
        case 'd':
            static int posCam2 = 0;
            posCam2++;
            if (cam->estilo == 1) {
                delete cam;
                if (posCam2%5==0) cam = new CameraDistante(); //CameraDistante(0,1,5, 0,1,0, 0,1,0);
                if (posCam2%5==1) cam = new CameraDistante(5,1,0, 0,1,0, 0,1,0); // 1° PONTO DDE FUGA
                // olho onde ela tá, centro pra onde ela tá olhando
                               // é um vetor perpendicular.
                if (posCam2%5==2) cam = new CameraDistante(-5,0,-5, 0,0,5, 0,1,0); // 2 PONTOS DE FUGA
    //                if (posCam%5==3) cam = new CameraDistante(-5,1,0, 0,1,0, 0,0,-1);

                if (posCam2%5==3) cam = new CameraDistante(5,5,5, 0,0,1, 0,1,0); // NESSE CASO up é -1 pq ta olhando z negativo.
                // como funciona o gluLookat prova

    // GUARDA AS POSIÇÕES DA CÂMERA
                    if (posCam2%5==4) cam = new CameraDistante(savedCamera[0],savedCamera[1],savedCamera[2],savedCamera[3],savedCamera[4],savedCamera[5],savedCamera[6],savedCamera[7],savedCamera[8]);
    //                if (posCam%5==3) cam = new CameraDistante(-5,1,0, 0,1,0, 0,1,0);



            } else if (cam->estilo == 2) {
                delete cam;
                cam = new CameraDistante();
            }
            break;


        case 'C':
            static int pos_manual_cam = 0;
            pos_manual_cam++;
            if (pos_manual_cam%4==0) {
                cout << "Mostrando camera 1/Alterando camera 1:\n";
                change_manual_cam = false;
                manual_cam = false;
            }
            if (pos_manual_cam%4==1) {
                cout << "Mostrando camera 1/Alterando camera 2:\n";
                change_manual_cam = true;
                manual_cam = false;
            }
            if (pos_manual_cam%4==2) {
                cout << "Mostrando camera 2/Alterando camera 2:\n";
                change_manual_cam = true;
                manual_cam = true;
            }
            if (pos_manual_cam%4==3) {
                cout << "Mostrando camera 2/Alterando camera 1:\n";
                change_manual_cam = false;
                manual_cam = true;
            }
            //manual_cam = !manual_cam;
            if (manual_cam) {
                glPushMatrix();
                    transformacao_global_2_camera(cam2->e,cam2->c,cam2->u,true);
                glPopMatrix();
            } else {
                glPushMatrix();
                    transformacao_camera_2_global(cam2->e,cam2->c,cam2->u,true);
                glPopMatrix();
            }
            break;

        case 's':
            //save current camera location
            savedCamera[0] = cam->e.x;
            savedCamera[1] = cam->e.y;
            savedCamera[2] = cam->e.z;
            savedCamera[3] = cam->c.x;
            savedCamera[4] = cam->c.y;
            savedCamera[5] = cam->c.z;
            savedCamera[6] = cam->u.x;
            savedCamera[7] = cam->u.y;
            savedCamera[8] = cam->u.z;
            break;

        case 'm':
            if (!manual_cam) {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glLoadIdentity();
                      glTranslated(tx,ty,tz);
                      glRotated(az,0,0,1);
                      glRotated(ay,0,1,0);
                      glRotated(ax,1,0,0);
                      glScaled(sx,sy,sz);
                    float transform[16];
                    glGetFloatv(GL_MODELVIEW_MATRIX,transform);
                    cout << "Matriz composicao de transformacoes (T.Rz.Ry.Rx.S):\n";
                    mostra_matriz_transform(transform);
                    cout << "\n";
                glPopMatrix();
            } else {
                glMatrixMode(GL_MODELVIEW);
                glPushMatrix();
                    glLoadIdentity();
                      gluLookAt(cam2->e.x,cam2->e.y,cam2->e.z, cam2->c.x,cam2->c.y,cam2->c.z, cam2->u.x,cam2->u.y,cam2->u.z);
                    float transform[16];
                    glGetFloatv(GL_MODELVIEW_MATRIX,transform);
                    cout << "Matriz gluLookAt:\n";
                    mostra_matriz_transform(transform);
                    cout << "\n";
                glPopMatrix();
            }
            break;
    }

    glutPostRedisplay();
}

void idle(void)
{
    glutPostRedisplay();
}

/* Program entry point */

int main(int argc, char *argv[])
{
        ajuda();
    //chamadas de inicializacao da GLUT
        glutInit(&argc, argv);
        glutInitWindowSize(width,height);
        glutInitWindowPosition(10,10);
        glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);

        glutCreateWindow("Trabalho 1 - Parte 2");

        glutReshapeFunc(resize);
        glutDisplayFunc(display);
        glutKeyboardFunc(key);
        glutIdleFunc(idle);

        glutMouseFunc(mouseButton);
        glutMotionFunc(mouseMove);

    //chamadas de inicializacao da OpenGL
        //glClearColor(1,1,1,1);
        //glClearColor(0.3,0.3,0.3,1.0);
        glClearColor(0.8,0.8,0.9,1.0);

        glEnable(GL_LIGHTING);
        glEnable(GL_COLOR_MATERIAL);
        //glEnable(GL_CULL_FACE);
        //glCullFace(GL_BACK);
        glEnable(GL_NORMALIZE); //mantem a qualidade da iluminacao mesmo quando glScalef eh usada

        glShadeModel(GL_SMOOTH);
        //glShadeModel(GL_FLAT);

        glEnable(GL_DEPTH_TEST);
        //glDepthFunc(GL_LESS);

        //glEnable(GL_BLEND); //habilita a transparencia
        //glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        //definindo uma luz
            glEnable(GL_LIGHT0);

            const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
            const GLfloat light_diffuse[]  = { 1.0f, 1.0f, 1.0f, 1.0f };
            const GLfloat light_specular[] = { 1.0f, 1.0f, 1.0f, 1.0f };
            //const GLfloat light_position[] = { 2.0f, 5.0f, 5.0f, 0.0f };

            const GLfloat mat_ambient[]    = { 0.7f, 0.7f, 0.7f, 1.0f };
            const GLfloat mat_diffuse[]    = { 0.8f, 0.8f, 0.8f, 1.0f };
            const GLfloat mat_specular[]   = { 1.0f, 1.0f, 1.0f, 1.0f };
            const GLfloat high_shininess[] = { 100.0f };

            glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
            glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
            glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
            //glLightfv(GL_LIGHT0, GL_POSITION, light_position);

            glMaterialfv(GL_FRONT, GL_AMBIENT,   mat_ambient);
            glMaterialfv(GL_FRONT, GL_DIFFUSE,   mat_diffuse);
            glMaterialfv(GL_FRONT, GL_SPECULAR,  mat_specular);
            glMaterialfv(GL_FRONT, GL_SHININESS, high_shininess);

            //glFrontFace(GL_CCW);
            gBunnySolidList = GenStanfordBunnySolidList ();
            gBunnyWireList = GenStanfordBunnyWireList ();


                const float ar = height>0 ? (float) width / (float) height : 1.0;

//                glViewport(0, 0, width, height);
                glViewport(0, -40, 1370, 800);
                glMatrixMode(GL_PROJECTION);
                glLoadIdentity();
                gluPerspective(30.,ar,0.1,1000.);
            //iniciando o loop principal da glut
            glutMainLoop();

    return EXIT_SUCCESS;
}
