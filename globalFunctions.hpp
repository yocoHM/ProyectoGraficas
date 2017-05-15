#ifndef GLOBALFUNCTIONS_H
#define GLOBALFUNCTIONS_H
/* 
    Function that loads a .obj model given a path
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

#include <iostream>
#include <vector>
#include <map>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "glm.h"

#define SPEED_MULT 1.5

extern int frame;//frame for fps counter
extern int currenttime;//current time for fps counter
extern int timebase;
extern float posX;
extern float posY;
extern bool movingUp;
extern bool movingDown;
extern bool movingLeft;
extern bool movingRight;
extern float xSpeed;//rotation speed on X axis
extern float ySpeed;//rotation speed on Y axis


GLMmodel* loadModel(const char* filename);
void enableParams();
void disableParams();
void idle();

#endif