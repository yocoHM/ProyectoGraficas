#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H

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

#include <iostream>
#include <vector>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm.h"

#define SPEED_MULT 1

//variables de control para manejar el movimiento del personaje
extern int frame;
extern int currenttime;
extern int timebase;
extern int elapsed;
//variables de movimiento del personaje
extern float posX;
extern float posY;
extern bool movingUp;
extern bool movingDown;
extern bool movingLeft;
extern bool movingRight;
//velocidad en x y y del personaje
extern float xSpeed;
extern float ySpeed;

//función para cargar un objeto
GLMmodel* loadModel(const char* filename);


#endif