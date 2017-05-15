/*
Alexis Matuk - A01021143
Diego Vazquez - A01168095
Gerardo Garcia Teruel - A01018057
*/

#include "Object.hpp"

/*
  Draw object taking into account translation, rotation, scale and center offset  
*/
void Object::Draw(GLuint _mode)
{
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

/*
    Set object's name
*/
void Object::setName(std::string _name)
{
	name = _name;
}

/*
  Get object's name  
*/
std::string Object::getName()
{
	return name;
}

/*
    Initialize object's bounding box based on the model's vertices
*/
void Object::initBoundingBox()
{
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
/*
  Pretty box used for programmer's peace of mind  
*/
/*
	   6--------5
	  /|	   /|
	 / |	  / |
	1--|-----0  |
	|  |	 |	|
	|  7-----|--4
	| / 	 | /
	|/		 |/
	2--------3
*/

/*
  Function to update the bouding box vertices  
*/
void Object::updateVertexArray()
{	   
	for(int i = 0; i < vertexArray.size(); i++)
	{
		glm::vec4 vec(vertexArray[i][0], vertexArray[i][1], vertexArray[i][2], 1.0f);
		vec = transformationMatrix * vec;
		vertexArray[i][0] = vec.x;
		vertexArray[i][1] = vec.y;
		vertexArray[i][2] = vec.z;
	}
}

/*
  Function to update the bounding box to new transforms.
  the transformation matrix is inverted, then the points are returned to their identity and 
  	the new transformations are applied.  
*/
void Object::updateBoundingBoxToTransforms()
{	
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


/*
   Get bounding box
*/
std::vector<std::vector<float>> Object::getBoundingBox()
{
	return vertexArray;
}

/*
  Render front face of bounding box 
*/
void Object::front(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// front face =================
    glVertex3fv(v0);    // v0-v1-v2
    glVertex3fv(v1);
    glVertex3fv(v2);
    glVertex3fv(v2);    // v2-v3-v0
    glVertex3fv(v3);
    glVertex3fv(v0);
}

/*
  Render right face of bounding box 
*/
void Object::right(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// right face =================
    glVertex3fv(v0);    // v0-v3-v4
    glVertex3fv(v3);
    glVertex3fv(v4);
    glVertex3fv(v4);    // v4-v5-v0
    glVertex3fv(v5);
    glVertex3fv(v0);
}

/*
  Render top face of bounding box 
*/
void Object::top(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// top face ===================
    glVertex3fv(v0);    // v0-v5-v6
    glVertex3fv(v5);
    glVertex3fv(v6);
    glVertex3fv(v6);    // v6-v1-v0
    glVertex3fv(v1);
    glVertex3fv(v0);
}

/*
  Render left face of bounding box 
*/
void Object::left(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	// left face ===================
    glVertex3fv(v6);    // 
    glVertex3fv(v7);
    glVertex3fv(v2);
    glVertex3fv(v2);    // 
    glVertex3fv(v1);
    glVertex3fv(v6);
}

/*
  Render back face of bounding box 
*/
void Object::back(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	 // back face ===================
    glVertex3fv(v5);    // 
    glVertex3fv(v6);
    glVertex3fv(v7);
    glVertex3fv(v7);    // 
    glVertex3fv(v4);
    glVertex3fv(v5);
}

/*
  Render bottom face of bounding box 
*/
void Object::bottom(float * v0, float * v1, float * v2, float * v3, float * v4, float * v5, float * v6, float * v7)
{
	 // bottom face ===================
    glVertex3fv(v7);    // 
    glVertex3fv(v2);
    glVertex3fv(v3);
    glVertex3fv(v3);    // 
    glVertex3fv(v4);
    glVertex3fv(v7);
}

/*
  Draw entire bounding box
*/
void Object::DrawBoundingBox()
{	
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);//Activar wireframe		
	glColor3f(1, 1, 0);
	float * v0 = &vertexArray[0][0];
	float * v1 = &vertexArray[1][0];
	float * v2 = &vertexArray[2][0];
	float * v3 = &vertexArray[3][0];
	float * v4 = &vertexArray[4][0];
	float * v5 = &vertexArray[5][0];
	float * v6 = &vertexArray[6][0];
	float * v7 = &vertexArray[7][0];
	glBegin(GL_TRIANGLES);  // draw a cube with 12 triangles	
    front(v0,v1,v2,v3,v4,v5,v6,v7);
    right(v0,v1,v2,v3,v4,v5,v6,v7);
    top(v0,v1,v2,v3,v4,v5,v6,v7);
    left(v0,v1,v2,v3,v4,v5,v6,v7);
    back(v0,v1,v2,v3,v4,v5,v6,v7);
    bottom(v0,v1,v2,v3,v4,v5,v6,v7);             
	glEnd();
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);  	
}

void Object::drawModel(GLuint _mode)
{
	glPushAttrib(GL_ALL_ATTRIB_BITS);
    if (model)
        glmDraw(model, _mode);
    glPopAttrib();
}

/*
  Default constructor for object
*/
Object::Object()
{
	scaleX = 1;
	scaleY = 1;
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
}

Object::~Object()
{
	
}

/*
  Constructor of object given a filename
*/
Object::Object(const char * filename):Object()
{
	model = loadModel(filename);
	initBoundingBox();
	updateBoundingBoxToTransforms();
}

/*
  Set object parameters including offset
*/
void Object::setParams(float _centerX, float _centerY, float _centerZ, float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ)
{
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;	
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;
	centerX = _centerX;
	centerY = _centerY;
	centerZ = _centerZ;
	updateBoundingBoxToTransforms();
}

/*
  Set object parameters and initialize their starting ones for further use.
  The parameter map is used for resetting the object's values in runtime.
*/
void Object::setParams(float _scaleX, float _scaleY, float _scaleZ, float _x, float _y, float _z, float _rotX, float _rotY, float _rotZ)
{	
	if(initialParameterMap.size() <= 0)
	{
		initialParameterMap["scaleX"] = _scaleX;
		initialParameterMap["scaleY"] = _scaleY;
		initialParameterMap["scaleZ"] = _scaleZ;
		initialParameterMap["transX"] = _x;
		initialParameterMap["transY"] = _y;
		initialParameterMap["transZ"] = _z;
		initialParameterMap["rotX"] = _rotX;
		initialParameterMap["rotY"] = _rotY;
		initialParameterMap["rotZ"] = _rotZ;
		initialParameterMap["centerX"] = centerX;
		initialParameterMap["centerY"] = centerY;
		initialParameterMap["centerZ"] = centerZ;
	}	
	scaleX = _scaleX;
	scaleY = _scaleY;
	scaleZ = _scaleZ;
	transX = _x;
	transY = _y;
	transZ = _z;	
	rotX = _rotX;
	rotY = _rotY;
	rotZ = _rotZ;	
	updateBoundingBoxToTransforms();
}

/*
  Set translation
*/
void Object::setTranslation(float x, float y, float z)
{
	transX = x;
	transY = y;
	transZ = z;	
	updateBoundingBoxToTransforms();
}

/*
  Set scale
*/
void Object::setScale(float x, float y, float z)
{
	scaleX = x;
	scaleY = y;
	scaleZ = z;
	updateBoundingBoxToTransforms();
}

/*
  Set rotation
*/
void Object::setRotation(float x, float y, float z)
{	
	rotX = x;
	rotY = y;
	rotZ = z;
	updateBoundingBoxToTransforms();
}

/*
  Add translation
*/
void Object::addTranslation(float x, float y, float z)
{
	transX += x;
	transY += y;
	transZ += z;
	updateBoundingBoxToTransforms();
}

/*
  Add rotation
*/
void Object::addRotation(float x, float y, float z)
{
	rotX += x;
	rotY += y;
	rotZ += z;
	updateBoundingBoxToTransforms();
}

/*
  Add scale
*/
void Object::addScale(float x, float y, float z)
{
	scaleX += x;
	scaleY += y;
	scaleZ += z;
	updateBoundingBoxToTransforms();
}

/*
  Get object parameters as map
*/
std::map<std::string, float> Object::getParams()
{
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

/*
  Get initial parameters as map for reset
*/
std::map<std::string, float> Object::getInitialParams()
{
	return initialParameterMap;
}

/*
  Set an object's parameters given a map
*/
void Object::setParamsByMap(std::map<std::string, float> _newParams)
{
	scaleX = _newParams["scaleX"];
	scaleY = _newParams["scaleY"];
	scaleZ = _newParams["scaleZ"];
	transX = _newParams["transX"];
	transY = _newParams["transY"];
	transZ = _newParams["transZ"];
	rotX = _newParams["rotX"];
	rotY = _newParams["rotY"];
	rotZ = _newParams["rotZ"];
	centerX = _newParams["centerX"];
	centerY = _newParams["centerY"];
	centerZ = _newParams["centerZ"];	
	updateBoundingBoxToTransforms();
}

/*
  Get model
*/
GLMmodel * Object::getModel()
{
	return model;
}

/*
  Reset objects to its initial parameters
*/
void Object::resetParams()
{
	setParamsByMap(initialParameterMap);
}