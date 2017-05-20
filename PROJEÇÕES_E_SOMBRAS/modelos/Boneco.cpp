#include "Boneco.h"
#include <GL/glut.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include "readBMP.h"


Boneco::Boneco(){
//    this->tipo = 6;
}


static GLfloat vdata[8][3] = {
   {-1.0, -1.0, -1.0}, {1.0, -1.0, -1.0}, {1.0, 1.0, -1.0}, {-1.0, 1.0, -1.0},
   {-1.0, -1.0, 1.0}, {1.0, -1.0, 1.0}, {1.0, 1.0, 1.0}, {-1.0, 1.0, 1.0}
   };


static GLfloat ndata[6][3] = {
      {0.0, 0.0, -1.0},{0.0, 1.0, 0.0},{-1.0, 0.0, 0.0},
      {1.0, 0.0, 0.0},{0.0, 0.0, 1.0},{0.0, -1.0, 0.0}
   };

static GLuint vindices[6][4] = {
   {0,3,2,1}, {2,3,7,6}, {0,4,7,3},
   {1,2,6,5}, {4,5,6,7}, {0,1,5,4}
   };

static GLfloat ambient[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat diffuse[] = {1.0, 1.0, 1.0, 1.0};
static GLfloat specular[] = {1.0, 1.0, 1.0, 1.0};
static GLfloat position[] = {0.0, 0.0,  4.0, 1.0};
static GLfloat fog_color[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat mat_ambient[] = {0.0, 0.0, 0.0, 1.0};
static GLfloat mat_shininess[] = {90.0};
static GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
static GLfloat mat_diffuse[] = {0.8, 0.8, 0.8, 1.0};
static GLfloat lmodel_ambient[] = {0.2, 0.2, 0.2, 1.0};

GLfloat spin_x=0.0, spin_y=0.0, spin_z=0.0;

GLfloat ant=0.0, bra=0.0, cab=0.0;

GLuint braco, busto, cabeca, perna;

GLuint indice=0;

BMPImage *image1, *image2; // data structure for image

static GLuint texName[2];

/* Simple BMP reading code, should be adaptable to many
systems. Originally from Windows, ported to Linux, now works on my Mac
OS system.

NOTE!! only reads 24-bit RGB, single plane, uncompressed, unencoded
BMP, not all BMPs. BMPs saved by xv should be fine. */

//
// This code was created by Jeff Molofee '99
//  (www.demonews.com/hosted/nehe)
// Ported to Linux/GLUT by Richard Campbell '99
// Code and comments for adaptation to big endian/little endian systems
// Nina Amenta '04
//

/* Reads a long 32 bit integer; comment out one or the other shifting line below,
whichever makes your system work right. */
unsigned int endianReadInt(FILE* file) {
unsigned char  b[4];
unsigned int i;

   if ( fread( b, 1, 4, file) < 4 )
     return 0;
   /* LITTLE VS BIG ENDIAN LINES - comment out one or the other */
   i = (b[3]<<24) | (b[2]<<16) | (b[1]<<8) | b[0]; // big endian
   //i = (b[0]<<24) | (b[1]<<16) | (b[2]<<8) | b[3]; // little endian
   return i;
}

/* Reads a 16 bit integer; comment out one or the other shifting line below,
whichever makes your system work right. */
unsigned short int endianReadShort(FILE* file) {
unsigned char  b[2];
unsigned short s;

   if ( fread( b, 1, 2, file) < 2 )
     return 0;
   /* LITTLE VS BIG ENDIAN LINES - comment out one or the other */
   s = (b[1]<<8) | b[0]; // big endian
   //s = (b[0]<<8) | b[1]; // little endian
   return s;
}


// quick and dirty bitmap loader...for 24 bit bitmaps with 1 plane only.
// See http://www.dcs.ed.ac.uk/~mxr/gfx/2d/BMP.txt for more info.
/* Desenhar um cubo */

static void cube()
{
  int i, j;

   /* desenhar o cubo */
   for (i=0; i<6; i++) {
     glNormal3fv(ndata[i]);
     glBegin(GL_POLYGON);
     glVertex3fv(&vdata[vindices[i][0]][0]);
     glVertex3fv(&vdata[vindices[i][1]][0]);
     glVertex3fv(&vdata[vindices[i][2]][0]);
     glVertex3fv(&vdata[vindices[i][3]][0]);
     glEnd();
   }
}


static void boneco()
{
   /* criar braco */
  /* gerar um indice de uma lista */
   braco = glGenLists(1);
   /* inicializar o conteudo da lista "braco". Ha dois modos:
      GL_COMPLIE: somente armazena; GL_COMPILE_AND_EXECUTE: armazena e executa
      */
   glNewList(braco, GL_COMPILE);
   glScalef(0.09, 0.28, 0.09);
   cube();
   /* finalizar a lista inicializada */
   glEndList();

   /* criar busto */
   busto = glGenLists(1);
   glNewList(busto, GL_COMPILE);
   glScalef(0.35, 0.525, 0.2);
   cube();
   glEndList();

   /* criar cabeca */
   cabeca = glGenLists(1);
   glNewList(cabeca, GL_COMPILE);
   glScalef(0.2, 0.2, 0.2);
   cube();
   glEndList();

   /* criar perna */
   perna = glGenLists(1);
   glNewList(perna, GL_COMPILE);
   glScalef(0.09, 0.57, 0.09);
   cube();
   glEndList();
}
Boneco::~Boneco(){}

void Boneco::Desenhar_Objeto(){
        float qr,qv,qb;
        if(isSelecionado()){
          qr = 1, qv = 1, qb = 1;
        }else{
          qr = 0.96, qv = 0.64, qb = 0.38;
        }

        glPushMatrix();
            // Rotacoes, transalacao, escala do objeto.
            Objeto::Desenhar_Objeto();
            void boneco();



        glPopMatrix();
}
