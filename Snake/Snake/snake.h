#pragma once
#include <vector>
#include "Sphere.h"
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Vector3D.h"
using namespace std;
using namespace glm;

struct Body{
	Vector3D* posun;
	Vector3D* rotation;
	Vector3D* second_rotation;
	GLfloat size;
	GLfloat rotation_angle;
	GLfloat second_rotation_angle;
	GLint wall = 0;
	GLboolean up = true;
	GLboolean down = false;
	GLboolean righ = false;
	GLboolean lef = false;
};

class snake
{
	GLint wall = 0;
	Sphere* hlava;
	Body prva;
	Body posledna;
	Sphere* chvost;
	vector<Sphere*> gule;
	vector<Body> telo;
	GLfloat size = 2.0f;
	GLUquadricObj *quadratic;
	GLboolean up = true;
	GLboolean down = false;
	GLboolean righ = false;
	GLboolean lef = false;
	Vector3D* rotation;
	GLfloat rotation_angle = 180;
	void addBody();
	GLboolean rotate_more = false;
	Body secondRotation;
	void nullSecondrotation();
	void calculateRotations();
	GLfloat cas;
public:
	bool narazeny = false;
	vec4* body;
	GLfloat posunX = 2.1f;
	GLfloat posunY = 0.0f;
	GLfloat posunZ = 0.0f;
	snake();
	void render(bool render);
	void posun();
	void setWall(GLint w);
	void addSphere();
	void calculatePoints();
	void setDirection(GLint dir);
	bool narazilsomdoseba(Sphere* gula1, Sphere* gula2, float* m1, float* m2);
	void papam();
	GLint getWall(){ return wall; }
	GLfloat getPosunX(){ return posunX; }
	GLfloat getPosunY(){ return posunY; }
	GLfloat getPosunZ(){ return posunZ; }
	~snake();
};

