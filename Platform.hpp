#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.hpp"

class Platform: public Object{
	public: enum class Color{
		GREEN,
		RED,
		BLUE, 
		WHITE
	};
private:	
	Color color;
	Color activeColor;
	float r;
	float g;
	float b;
	bool active;
	GLfloat no_mat[4];
	GLfloat mat_diffuse[4];
	GLfloat no_shininess[1];
	GLfloat low_shininess[1];
public:		
	Platform();
	~Platform();
	void setColor(Color _color);
	bool getActive();
	virtual void initBoundingBox();
	void Draw();	
	void changeActiveColor(Color _activeColor);	
};

#endif