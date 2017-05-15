#ifndef PLATFORM_H
#define PLATFORM_H

#include "Object.hpp"

typedef struct RGB{
		float r;
		float g;
		float b;
	}RGB;

class Platform: public Object{
private:
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
	void setColor(int r, int g, int b);
	virtual void initBoundingBox();
	void Draw();		
};

#endif