#include "globalFunctions.hpp"


int frame = 0;
int currenttime = 0;
int timebase = 0;
float posX = 0;
float posY = 0;
bool movingUp = false;
bool movingDown = false;
bool movingLeft = false;
bool movingRight = false;
float xSpeed = 0.1 * SPEED_MULT;
float ySpeed = 0.1 * SPEED_MULT;


GLMmodel* loadModel(const char* filename)
{
	GLMmodel* model = nullptr;
    if (!model) {		/* load up the model */
	model = glmReadOBJ(filename);
	if (!model) {
		std::cout << "\nUsage: objviewV2 <-s> <obj filename>\n" << std::endl;
		exit(0);
	}
	glmUnitize(model);
	glmVertexNormals(model, 90.0, GL_TRUE);
}
return model;
}

/*
    Enable opengl environment parameters  
*/
void enableParams()
{
	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_NORMALIZE);
	glEnable(GL_TEXTURE_2D);
}

/*
    Disable opengl environment parameters
*/
void disableParams()
{
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_NORMALIZE);
	glDisable(GL_TEXTURE_2D);
}

void moveTiki()
{
	if(movingUp)
        posY -= xSpeed;
    if(movingDown)
        posY += xSpeed;
    if(movingLeft)
        posX -= ySpeed;
    if(movingRight)
        posX += ySpeed;
}

void idle()
{
	frame++;
	currenttime = glutGet(GLUT_ELAPSED_TIME);
	if (currenttime - timebase > 0.1)
	{
		moveTiki();
		timebase = currenttime;
		frame = 0;
		glutPostRedisplay();
	}
}