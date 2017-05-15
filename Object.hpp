#ifndef Object_H
#define Object_H

#include "globalFunctions.hpp"

//clase objeto (sirve para casi todo el manejo de obj's)
class Object{	
protected:
	//variables de escalamiento
	float scaleX;
	float scaleY;
	float scaleZ;
	//variables de traslación
	float transX;
	float transY;
	float transZ;
	//variables de rotación
	float rotX;
	float rotY;
	float rotZ;
	//centro del objeto
	float centerX;
	float centerY;
	float centerZ;
	float distance;
	//variable para el modelo
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
	//constructor
	Object();
	//destructor
	~Object();
	//constructor con parametro del nombre del archivo obj
	Object(const char * filename);	
	//traslación
	void setTranslation(float x, float y, float z);
	//escalamiento
	void setScale(float x, float y, float z);
	//rotación
	void setRotation(float x, float y, float z);
	//inicializar la caja de los límites del objeto
	virtual void initBoundingBox();	
	//actualizar la caja de límites de acuerdo a las transformaciones del objeto
	void updateBoundingBoxToTransforms();
	//acualizar el arreglo de vertices
	virtual void updateVertexArray();
	//obtener la caja de límites del objeto
	std::vector<std::vector<float>> getBoundingBox();
	//obtener los parámetros del objeto
	std::map<std::string, float> getParams();
	//crear al modelo en la escena
	void drawModel(GLuint _mode);
	//métodos para saber si dos objetos están intersectando
	void SATtest( glm::vec3 axis, std::vector<std::vector<float>> points, float& minAlong, float& maxAlong );
	bool intersects( Object * platform_2 );
	bool overlaps( float min1, float max1, float min2, float max2 );
	bool isBetweenOrdered( float val, float lowerBound, float upperBound );
};

#endif