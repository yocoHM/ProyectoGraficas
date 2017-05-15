/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#ifndef Object_H
#define Object_H

#include "globalFunctions.hpp"

class Object{	
protected:
	float scaleX;
	float scaleY;
	float scaleZ;
	float transX;
	float transY;
	float transZ;
	float rotX;
	float rotY;
	float rotZ;
	float centerX;
	float centerY;
	float centerZ;
	float distance;
	GLMmodel * model;	
	std::map<std::string, float> parameterMap;
	std::map<std::string, float> initialParameterMap;
	float min_x;
	float max_x;
    float min_y; 
    float max_y;
    float min_z; 
    float max_z;
   	std::vector<std::vector<float>> vertexArray;
   	glm::mat4 transformationMatrix; 
   	std::string name = "";
   	std::string type = "Object";
public:	
	virtual void Draw(GLuint _mode);	
	Object();
	~Object();
	Object(const char * filename);
	void setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);
	void setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ);	
	void setTranslation(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float x, float y, float z);
	void addTranslation(float x, float y, float z);
	void addRotation(float x, float y, float z);
	void addScale(float x, float y, float z);
	GLMmodel * getModel();
	std::string getName();
	void initBoundingBox();	
	void DrawBoundingBox();
	void updateBoundingBoxToTransforms();
	virtual void updateVertexArray();	
	std::vector<std::vector<float>> getBoundingBox();
	std::map<std::string, float> getParams();
	std::map<std::string, float> getInitialParams();
	void setParamsByMap(std::map<std::string, float> _newParams);
	void setName(std::string _name);
	void drawModel(GLuint _mode);
	void resetParams();	
	void front(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void back(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void left(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void right(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void top(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
	void bottom(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7);
};

#endif