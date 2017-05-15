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
#include <math.h>
#include <stdbool.h>
#include <time.h>
#include "glm.h"
#include "Object.hpp"
#include "Platform.hpp"
#include "SOIL.h"
#include "Grid.hpp"

Grid * grid;
Object * tiki;
Object * rock;
Platform * centroTest;
GLuint textureMode;
Platform::Color nextColor;
int ww;
int wh;

float camX=2.0, camY=4.0, camZ=7.0;

bool mostrarVerdes = true;
bool mostrarRojos = true;
bool mostrarAzul = true;

static GLuint texName[2];

GLfloat ctrlpoints[4][4][3] =
{
    {
        {-1.5, -1.5, 0.0},
        {-0.5, -1.5, 0.5},
        {0.5, -1.5, 1.0},
        {1.5, -1.5, -0.5}},
    {
        {-1.5, -0.5, 0.0},
        {-0.5, -0.5, 0.5},
        {0.5, -0.5, 1.0},
        {1.5, -0.5, -0.5}},
    {
        {-1.5, 0.5, 0.0},
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 1.0},
        {1.5, 0.5, -0.5}},
    {
        {-1.5, 1.5, 0.0},
        {-0.5, 1.5, 0.5},
        {0.5, 1.5, 1.0},
        {1.5, 1.5, -0.5}}
};

GLfloat texpts[2][2][2] = {{{0.0, 0.0}, {0.0, 1.0}}, {{1.0, 0.0}, {1.0, 1.0}}};

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
  
  textureMode = GLM_SMOOTH | GLM_MATERIAL | GLM_TEXTURE | GLM_2_SIDED;
  GLuint mode = GLM_FLAT | GLM_MATERIAL | GLM_TEXTURE;

  tiki = new Object("Creature.obj");
  tiki->setRotation(-90,0,0);
  tiki->setScale(0.4, 0.4, 0.4);

  rock = new Object("obj_f_500_v_252.obj");

  centroTest = new Platform();

  glBindTexture(GL_TEXTURE_2D, texName[0]);
  glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
  glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);
  glEnable(GL_MAP2_TEXTURE_COORD_2);
  glEnable(GL_MAP2_VERTEX_3);
  glMapGrid2f(20, 0.0, 1.0, 20, 0.0, 1.0);
  
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
  glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
  
  
  int width_1, height_1;
  unsigned char* image_1 = SOIL_load_image("lava.png", &width_1, &height_1, 0, SOIL_LOAD_RGB);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width_1,  height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);
  glTexImage2D(GL_TEXTURE_2D, 0, 3, width_1, height_1, 0, GL_RGB, GL_UNSIGNED_BYTE, image_1);
  glEnable(GL_TEXTURE_2D);
  centroTest->setScale(1.5,1.5,1.5);
  centroTest->setColor(Platform::Color::RED);
  centroTest->setTranslation(2,3.1,0);

  grid = new Grid(5,5);

  nextColor = Platform::Color::RED;
  centroTest->setColor(nextColor);
}

void dibujarTiki() {
  glPushMatrix();
    float zPos = tiki->getParams()["transY"];
    tiki->setTranslation(posX, zPos, posY);
    tiki->Draw(textureMode);
<<<<<<< HEAD
    tiki->DrawBoundingBox();
    // if(tiki->intersects(centroTest))
    // {
    //   printf("INTERSECT\n");
    // }
    // else
    // {
    //   printf("NO INTERSECT\n");
    // }
  glPopMatrix();
}

void drawRocks() {
    rock->setScale(7.0, 7.0, 7.0);
    rock->setTranslation(-3.0, 0.0, -3.5);
    rock->Draw(textureMode);

    rock->setScale(8.0, 8.0, 7.0);
    rock->setTranslation(0.0, 0.0, -3.5);
    rock->Draw(textureMode);

    rock->setScale(9.0, 7.0, 7.0);
    rock->setTranslation(3.0, 0.0, -3.5);
    rock->Draw(textureMode);
}

void drawLava() {
  glPushMatrix();
    
      glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL);
      glMap2f(GL_MAP2_VERTEX_3, 0, 1, 3, 4, 0, 1, 12, 4, &ctrlpoints[0][0][0]);
      glMap2f(GL_MAP2_TEXTURE_COORD_2, 0, 1, 2, 2, 0, 1, 4, 2, &texpts[0][0][0]);
      glBindTexture(GL_TEXTURE_2D, texName[0]);
      glTranslatef(0.0, -4.0, 0.0);
      glRotatef(-90.0, 1.0, 0.0, 0.0);
      glScalef(7.0, 5.0, 5.0);
      glEvalMesh2(GL_FILL, 0, 20, 0, 20);
    
    if(!grid->tikiLives(tiki))
    {
      printf("YA ME MORIBUNDEE\n");
    }
    else
    {
      printf("YA ESTOY VIVITO AHORA MIMITO\n");
    }
  glPopMatrix();
}

//función para dibujar la casa
void display(void) {
  glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  
  glPushMatrix();
    //movimiento de cámara
    gluLookAt (camX, camY, camZ, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    drawRocks();
    dibujarTiki();
    grid->Draw();
    centroTest->Draw();
    glPushAttrib(GL_ALL_ATTRIB_BITS);
      drawLava();
    glPopAttrib();
  glPopMatrix();

  glutSwapBuffers();
}

//función para hacer el reshape de los objetos cuando la venta se hace más grande o más pequeña
void reshape (int w, int h) {
  ww = w;
  wh = h;
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
    case 27:
      exit(0);
      break;
    default:
      break;
  }
  glutPostRedisplay();
}

void moveTiki()
{
  if(movingUp)
        posY -= xSpeed * (currenttime - timebase);
    if(movingDown)
        posY += xSpeed * (currenttime - timebase);
    if(movingLeft)
        posX -= ySpeed * (currenttime - timebase);
    if(movingRight)
        posX += ySpeed * (currenttime - timebase);
}

void idle()
{
  frame++;
  currenttime = glutGet(GLUT_ELAPSED_TIME);
  if(currenttime - elapsed > 5000)
  {
    grid->changeColor(nextColor);    
    float color = rand() % 3 + 1; 
    if(color == 1)
    {
      nextColor = Platform::Color::RED;
    }
    if(color == 2)
    {
      nextColor = Platform::Color::GREEN;
    }
    if(color == 3)
    {
      nextColor = Platform::Color::BLUE;
    }
    centroTest->setColor(nextColor);
    elapsed = currenttime;
  }

  if (currenttime - timebase > 0.1)
  {
    moveTiki();
    timebase = currenttime;
    frame = 0;
    glutPostRedisplay();
  }

}


//main
int main(int argc, char** argv) {
  srand (time(NULL));
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
