#ifndef GRID_H
#define GRID_H

#include "Platform.hpp"
#include "Object.hpp"

//clase para el conjunto de plataformas
class Grid{
private:
	//número de plataformas deseadas
	int X;
	int Y;
	//plataformas
	std::vector<std::vector<Platform*>> platforms;
	//colores activos
	Platform::Color activeColor;
public:
	//constructor
	Grid(int _X, int _Y);
	//cambio de color
	void changeColor(Platform::Color newColor);
	//crear las plataformas en la escena
	void Draw();
	//chequeo para saber si el personaje sigue vivo o ya murió
	bool tikiLives(Object * object);
};


#endif