#include "Object.hpp"

void Object::Draw(GLuint _mode) {
	glPushMatrix();
		glPushAttrib(GL_ALL_ATTRIB_BITS);
			glTranslatef(transX,transY,transZ);  
			glRotatef(rotX, 1, 0, 0);
			glRotatef(rotY, 0, 1, 0);
			glRotatef(rotZ, 0, 0, 1);		    
		    glScalef(scaleX, scaleY, scaleZ);     
		    glTranslatef(centerX, centerY, centerZ);
			drawModel(_mode);		
		glPopAttrib();
	glPopMatrix();
}

//constructor
Object::Object()
{
	scaleX = 1;
	scaleY = 1;
	scaleZ = 1;
	transX = 0;
	transY = 0.5;
	transZ = -1;	
	rotX = 0;
	rotY = 0;
	rotZ = 0;
	centerX = 0;
	centerY = 0;
	centerZ = 0;	
	distance = 0;
}

//inicializar la caja de los límites del objeto
void Object::initBoundingBox() {
	if (model->numvertices == 0)
		return;  
    max_x = min_x = model->vertices[3 + 0];
    max_y = min_y = model->vertices[3 + 1];
    max_z = min_z = model->vertices[3 + 2];
    for (int i = 1; i <= model->numvertices; i++) {
        if (max_x < model->vertices[3 * i + 0])
            max_x = model->vertices[3 * i + 0];
        if (min_x > model->vertices[3 * i + 0])
            min_x = model->vertices[3 * i + 0];       
        if (max_y < model->vertices[3 * i + 1])
            max_y = model->vertices[3 * i + 1];
        if (min_y > model->vertices[3 * i + 1])
            min_y = model->vertices[3 * i + 1];        
        if (max_z < model->vertices[3 * i + 2])
            max_z = model->vertices[3 * i + 2];
        if (min_z > model->vertices[3 * i + 2])
            min_z = model->vertices[3 * i + 2];
    }
	vertexArray.push_back({max_x, max_y, min_z});
	vertexArray.push_back({min_x, max_y, min_z});
	vertexArray.push_back({min_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, min_z});
	vertexArray.push_back({max_x, min_y, max_z});
	vertexArray.push_back({max_x, max_y, max_z});
	vertexArray.push_back({min_x, max_y, max_z});
	vertexArray.push_back({min_x, min_y, max_z});
}

//acualizar el arreglo de vertices
void Object::updateVertexArray() {	   
	for(int i = 0; i < vertexArray.size(); i++) {
		glm::vec4 vec(vertexArray[i][0], vertexArray[i][1], vertexArray[i][2], 1.0f);
		vec = transformationMatrix * vec;
		vertexArray[i][0] = vec.x;
		vertexArray[i][1] = vec.y;
		vertexArray[i][2] = vec.z;
	}
}

//actualizar la caja de límites de acuerdo a las transformaciones del objeto
void Object::updateBoundingBoxToTransforms() {	
	glm::vec4 inv;
	transformationMatrix = glm::inverse(transformationMatrix);
	updateVertexArray();
	transformationMatrix = glm::mat4();
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(transX, transY, transZ));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotX), glm::vec3(1.0, 0.0, 0.0));
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotY), glm::vec3(0.0, 1.0, 0.0)); 
    transformationMatrix = glm::rotate(transformationMatrix, glm::radians(rotZ), glm::vec3(0.0, 0.0, 1.0));	        
    transformationMatrix = glm::scale(transformationMatrix, glm::vec3(scaleX, scaleY, scaleZ));  
    transformationMatrix = glm::translate(transformationMatrix, glm::vec3(centerX, centerY, centerZ));
    updateVertexArray();	
}

//obtener la caja de límites del objeto
std::vector<std::vector<float>> Object::getBoundingBox()
{
	return vertexArray;
}

//crear al modelo en la escena
void Object::drawModel(GLuint _mode)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    if (model)
        glmDraw(model, _mode);
    glPopAttrib();
}

//destructor
Object::~Object() {
	
}

//constructor con parametro del nombre del archivo obj
Object::Object(const char * filename):Object() {
	model = loadModel(filename);
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

//traslación
void Object::setTranslation(float x, float y, float z) {
	transX = x;
	transY = y;
	transZ = z;	
	updateBoundingBoxToTransforms();
}

//escalamiento
void Object::setScale(float x, float y, float z) {
	scaleX = x;
	scaleY = y;
	scaleZ = z;
	updateBoundingBoxToTransforms();
}

//rotación
void Object::setRotation(float x, float y, float z) {	
	rotX = x;
	rotY = y;
	rotZ = z;
	updateBoundingBoxToTransforms();
}

//obtener los parámetros del objeto
std::map<std::string, float> Object::getParams() {
	parameterMap["scaleX"] = scaleX;
	parameterMap["scaleY"] = scaleY;
	parameterMap["scaleZ"] = scaleZ;
	parameterMap["transX"] = transX;
	parameterMap["transY"] = transY;
	parameterMap["transZ"] = transZ;
	parameterMap["rotX"] = rotX;
	parameterMap["rotY"] = rotY;
	parameterMap["rotZ"] = rotZ;
	parameterMap["centerX"] = centerX;
	parameterMap["centerY"] = centerY;
	parameterMap["centerZ"] = centerZ;	
	return parameterMap;
}

//métodos para saber si dos objetos están intersectando
void Object::SATtest( glm::vec3 axis, std::vector<std::vector<float>> points, float& minAlong, float& maxAlong ) {	
	minAlong=10000, maxAlong=-10000;
	for( int i = 0 ; i < points.size() ; i++ ) {
		glm::vec3 point(points[i][0], points[i][1], points[i][2]);
		float dotVal = glm::dot(point, axis);
		if( dotVal < minAlong )  minAlong=dotVal;
		if( dotVal > maxAlong )  maxAlong=dotVal;
	}
}

bool Object::intersects( Object * platform_2 ) {

  //obtener las normales para los objetos
  for( int i = 0 ; i < 3 ; i++ ) {
  	glm::vec3 axis(transformationMatrix[i].x, transformationMatrix[i].y, transformationMatrix[i].z);
    float shape1Min, shape1Max, shape2Min, shape2Max ;
    SATtest( axis, vertexArray, shape1Min, shape1Max ) ;
    SATtest( axis, platform_2->getBoundingBox(), shape2Min, shape2Max ) ;
    if( !overlaps( shape1Min, shape1Max, shape2Min, shape2Max ) ) {
    	//aqui no hay intersección
      return 0 ;
    }

  }

  //aqui intersecta
  return 1 ;
}

bool Object::overlaps( float min1, float max1, float min2, float max2 ) {
  return isBetweenOrdered( min2, min1, max1 ) || isBetweenOrdered( min1, min2, max2 ) ;
}

bool Object::isBetweenOrdered( float val, float lowerBound, float upperBound ) {
  return lowerBound <= val && val <= upperBound ;
}