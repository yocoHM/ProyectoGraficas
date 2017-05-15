#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.hpp"

//clase plataforma que hereda de la clase objeto
class Platform: public Object{
	//enumeración de colores para las plataformas
	public: enum class Color{
		GREEN,
		RED,
		BLUE, 
		WHITE
	};
private:
	//propiedades de color
	Color color;
	Color activeColor;
	float r;
	float g;
	float b;
	//variable de control para saber si una plataforma está activa o no
	bool active;
	//materiales
	GLfloat no_mat[4];
	GLfloat mat_diffuse[4];
	GLfloat no_shininess[1];
	GLfloat low_shininess[1];
public:		
	//constructor
	Platform();
	//destructor
	~Platform();
	//asiganción de color
	void setColor(Color _color);
	//saber si la plataforma está activa o no
	bool getActive();
	//iniciar la caja para saber los límites de la plataforma
	virtual void initBoundingBox();
	//crear la platadorma en la escena
	void Draw();	
	//cambio del color actual
	void changeActiveColor(Color _activeColor);	
};

#endif