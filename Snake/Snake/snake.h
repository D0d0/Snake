#pragma once
#include <vector>
#include "Sphere.h"
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
using namespace std;
using namespace glm;

class snake
{
	GLint wall = 0;
	Sphere* hlava;
	Sphere* chvost;
	vector<Sphere*> gule;
	GLfloat size = 0.5f;
public:
	vec4 bod1, bod2, bod3, bod4, bod5, bod6, bod7, bod8;
	GLfloat posunX = 2.1f;
	GLfloat posunY = 0.0f;
	GLfloat posunZ = 0.0f;
	snake();
	void render();
	void setWall(GLint w){ wall = w; }
	void addSphere();
	void calculatePoints();
	GLint getWall(){ return wall; }
	GLfloat getPosunX(){ return posunX; }
	GLfloat getPosunY(){ return posunY; }
	GLfloat getPosunZ(){ return posunZ; }
	~snake();
};

