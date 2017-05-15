#ifndef GRID_H
#define GRID_H

#include "Platform.hpp"
#include "Object.hpp"


class Grid{
private:
	int X;
	int Y;
	std::vector<std::vector<Platform*>> platforms;
	Platform::Color activeColor;
public:
	Grid(int _X, int _Y);
	void changeColor(Platform::Color newColor);
	void Draw();
	bool tikiLives(Object * object);
};


#endif