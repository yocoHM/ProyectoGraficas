#include "globalFunctions.hpp"

//variables de control para manejar el movimiento del personaje
int frame = 0;
int currenttime = 0;
int timebase = 0;
int elapsed = 0;
//variables de movimiento del personaje
float posX = 0;
float posY = 0;
bool movingUp = false;
bool movingDown = false;
bool movingLeft = false;
bool movingRight = false;
//velocidad en x y y del personaje
float xSpeed = 0.001 * SPEED_MULT;
float ySpeed = 0.001 * SPEED_MULT;

//función para cargar un objeto
GLMmodel* loadModel(const char* filename) {
	GLMmodel* model = nullptr;
	//cargar el modelo
    if (!model) {
		model = glmReadOBJ(filename);
		if (!model) {
			exit(0);
		}
		glmUnitize(model);
		glmVertexNormals(model, 90.0, GL_TRUE);
	}
	return model;
}