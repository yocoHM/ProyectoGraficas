#include "Platform.hpp"

Platform::Platform():Object(), no_mat{0.0, 0.0, 0.0, 1.0}, mat_diffuse{1, 1, 1, 1.0}, no_shininess{0.0}, low_shininess{5.0}
{
	scaleX = 1;
	scaleY = 0.25;
	scaleZ = 1;
	transX = 0;
	transY = 0;
	transZ = 0;	
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	centerX = 0;
	centerY = 0;
	centerZ = 0;	
	distance = 0;
	active = true;

	r = 1;
	g = 1;
	b = 1;

	initBoundingBox();
	updateBoundingBoxToTransforms();
}

void Platform::setColor(int _r, int _g, int _b)
{
	r = (float) _r / (float) 255;
	g = (float) _g / (float) 255;
	b = (float) _b / (float) 255;
	mat_diffuse[0] = r;
	mat_diffuse[1] = g;
	mat_diffuse[2] = b;
}

void Platform::initBoundingBox()
{
	max_x = 0.5;
	max_y = 0.5;
	max_z = 0.5;
	min_x = -0.5;
	min_y = -0.5;
	min_z = -0.5;
	vertexArray.push_back({max_x, max_y, min_z});
	vertexArray.push_back({min_x, max_y, min_z});
	vertexArray.push_back({min_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, max_z});
	vertexArray.push_back({max_x, max_y, max_z});
	vertexArray.push_back({min_x, max_y, max_z});
	vertexArray.push_back({min_x, min_y, max_z});
}

void Platform::Draw()
{	
	if(active)
	{
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glPushMatrix();
				glScalef(scaleX, scaleY, scaleZ);
				glMaterialfv(GL_FRONT, GL_AMBIENT, no_mat);
				glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
				glMaterialfv(GL_FRONT, GL_SPECULAR, no_mat);
				glMaterialfv(GL_FRONT, GL_SHININESS, no_shininess);
				glMaterialfv(GL_FRONT, GL_EMISSION, no_mat);
				glutSolidCube(1.0);
			glPopMatrix();
		glPopAttrib();
	}	
}


Platform::~Platform()
{

}
