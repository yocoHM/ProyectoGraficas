/*
 Autores: Yocoyani Hernández A01017817
 Avance del proyecto final
 Descripción: Este es el primer avance del proyecto final de la materia de Gráficas Computacionales.
 Instrucciones:
 Si es Linux, abrir la terminal y poner el siguiente comando:
 ./comp
 Si es Mac, abrir el archivo comp y comentar las líneas necesarias que se indican.
*/


#ifdef __APPLE__
    #include <GLUT/glut.h>
    #include <OpenGL/gl.h>
    #include <OpenGL/glu.h>
#elif _WIN32
    #include <GL\glut.h>
#elif __linux__
    #include <GL/glut.h>
    #include <GL/gl.h>
    #include <GL/glu.h>
#endif

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "glm.h"
#include "Object.hpp"

Object * tiki;
GLuint textureMode;

float camX=0.0, camY=3.0, camZ=3.0;

bool mostrarVerdes = true;
bool mostrarRojos = true;
bool mostrarAzul = true;

void init(void) {
  //luces
  GLfloat ambient[] = { 0.2, 0.2, 0.2, 1.0 };
  GLfloat diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
  GLfloat specular[] = { 0.0, 0.0, 0.0, 1.0 };
  GLfloat shininess = 90.0;
  
  glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, ambient);
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, diffuse);
  glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, specular);
  glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, shininess);
  
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  
  glEnable(GL_DEPTH_TEST);
  
  glEnable(GL_CULL_FACE);
  
  textureMode = GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE | GLM_2_SIDED;
  GLuint mode = GLM_FLAT | GLM_MATERIAL | GLM_TEXTURE;

  tiki = new Object("Creature.obj");
  tiki->setRotation(-90,0,0);
  tiki->setScale(0.6, 0.6, 0.6);
}

void dibujarTiki() {
  glPushMatrix();
    tiki->setTranslation(posX, 1, posY);
    tiki->Draw(textureMode);
  glPopMatrix();
}

void cuadroCentro() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //verde
  GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(0.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroIzqCentro() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //rojo
  GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroDerCentro() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //azul
  GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroCentroAtras() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //rojo
  GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(0.0, 0.0, -1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroIzqAtras() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //azul
  GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(-1.0, 0.0, -1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroDerAtras() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //verde
  GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(1.0, 0.0, -1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroDerAdelante() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //rojo
  GLfloat mat_diffuse[] = { 1.0, 0.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(1.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroCentroAdelante() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //azul
  GLfloat mat_diffuse[] = { 0.0, 0.0, 1.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(0.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void cuadroIzqAdelante() {
  GLfloat no_mat[] = { 0.0, 0.0, 0.0, 1.0 };
  //verde
  GLfloat mat_diffuse[] = { 0.0, 1.0, 0.0, 1.0 };
  GLfloat no_shininess[] = { 0.0 };
  GLfloat low_shininess[] = { 5.0 };

  glPushMatrix();
    glScalef(1.0, 0.25, 1.0);
    glTranslatef(-1.0, 0.0, 1.0);
    glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
    glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
    glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
    glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
    glutSolidCube(1.0);
  glPopMatrix();
}

void dibujarPiso() {
  //fila atras
  if (mostrarRojos) {
    cuadroCentroAtras();
    cuadroIzqCentro();
    cuadroDerAdelante();
  }
  if (mostrarAzul) {
    cuadroIzqAtras();
    cuadroDerCentro();
    cuadroCentroAdelante();
  }
  
  if (mostrarVerdes) {
    cuadroDerAtras();
    cuadroCentro();
    cuadroIzqAdelante();
  }
  
}

//función para dibujar la casa
void display(void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  
  glPushMatrix();
    //movimiento de cámara
    gluLookAt (camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    dibujarTiki();
    dibujarPiso();

  glPopMatrix();

  glutSwapBuffers();
}

//función para hacer el reshape de los objetos cuando la venta se hace más grande o más pequeña
void reshape (int w, int h) {
  glViewport (0, 0, (GLsizei) w, (GLsizei) h);
  glMatrixMode (GL_PROJECTION);
  glLoadIdentity ();
  gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 200.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
}

//función para utilizar el teclado y mover la cámara
void keyboard(unsigned char c, int x, int y) {
  switch(c) {
    case 'w':
      movingUp = true;
      break;
    case 's':
      movingDown = true;
      break;
    case 'a':
      movingLeft = true;
      break;
    case 'd':
      movingRight = true;
      break;
    case 'g':
      if (mostrarVerdes) {
        mostrarVerdes = false;
      }
      else {
        mostrarVerdes = true;
      }
      glutPostRedisplay();
      break;
    case 'r':
      if (mostrarRojos) {
        mostrarRojos = false;
      }
      else {
        mostrarRojos = true;
      }
      glutPostRedisplay();
      break;
    case 'b':
      if (mostrarAzul) {
        mostrarAzul = false;
      }
      else {
        mostrarAzul = true;
      }
      glutPostRedisplay();
      break;
    case 27:
      exit(0);
      break;
    default:
      break;
  }
}


//función para utilizar el teclado y mover la cámara
void keyboardUp(unsigned char c, int x, int y) {
  switch(c) {
    case 'w':
      movingUp = false;
      break;
    case 's':
      movingDown = false;
      break;
    case 'a':
      movingLeft = false;
      break;
    case 'd':
      movingRight = false;
      break;
    case 'g':
      if (mostrarVerdes) {
        mostrarVerdes = false;
      }
      else {
        mostrarVerdes = true;
      }
      break;
    case 'r':
      if (mostrarRojos) {
        mostrarRojos = false;
      }
      else {
        mostrarRojos = true;
      }
      break;
    case 'b':
      if (mostrarAzul) {
        mostrarAzul = false;
      }
      else {
        mostrarAzul = true;
      }
      break;
    case 27:
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

//main
int main(int argc, char** argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize (900, 900);
  glutInitWindowPosition (100, 100);
  glutCreateWindow (argv[0]);
  init ();
  glutDisplayFunc(display);
  glutIdleFunc(idle);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboardUp);
  glutMainLoop();
  return 0;
}
