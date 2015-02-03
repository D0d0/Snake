#include "snake.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
snake::snake()
{
	posunX = 2.1f;
	posunY = 0.0f;
	posunZ = 0.0f;
	hlava = new Sphere(15, 15);
	chvost = new Sphere(15, 15);
}

void snake::addSphere(){
	Sphere* tmp = new Sphere(15, 15);
	tmp->setPosition(getPosunX(), getPosunY(), getPosunZ());
	gule.push_back(tmp);
}

void snake::calculatePoints(){

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glm::mat4 modelViewMatrix = glm::make_mat4(m);

	float bod[4] = { hlava->minX, hlava->minY, hlava->minZ, 1 };
	bod1 = modelViewMatrix*make_vec4(bod);

	float bo[4] = { hlava->maxX, hlava->minY, hlava->minZ, 1 };
	bod2 = modelViewMatrix*make_vec4(bo);

	float b[4] = { hlava->minX, hlava->maxY, hlava->minZ, 1 };
	bod3 = modelViewMatrix*make_vec4(b);

	float c[4] = { hlava->minX, hlava->minY, hlava->maxZ, 1 };
	bod4 = modelViewMatrix*make_vec4(c);

	float d[4] = { hlava->maxX, hlava->maxY, hlava->minZ, 1 };
	bod5 = modelViewMatrix*make_vec4(d);

	float e[4] = { hlava->maxX, hlava->minY, hlava->maxZ, 1 };
	bod6 = modelViewMatrix*make_vec4(e);

	float f[4] = { hlava->minX, hlava->maxY, hlava->maxZ, 1 };
	bod7 = modelViewMatrix*make_vec4(f);

	float g[4] = { hlava->maxX, hlava->maxY, hlava->maxZ, 1 };
	bod8 = modelViewMatrix*make_vec4(g);
}

void snake::render(){
	glPushMatrix();
	//cout << "posunX " << posunX << endl;
	//cout << "posunY " << posunY << endl;
	//cout << "posunZ " << posunZ << endl;
	glTranslatef(getPosunX(), getPosunY(), getPosunZ());
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glRotatef(180, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, 0.1f, 0.1f, size, 32, 32);
	glScalef(0.1, 0.1, 0.1);
	hlava->render();
	hlava->renderBoundingBox();
	calculatePoints();
	glPopMatrix();

	for each (Sphere* var in gule){
		glPushMatrix();
		glTranslatef(var->posunX, var->posunY, var->posunZ);
		glScalef(0.1, 0.1, 0.1);
		var->render();
		glPopMatrix();
	}

	glPushMatrix();
	glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
	glScalef(0.1, 0.1, 0.1);
	chvost->render();
	glPopMatrix();
}



snake::~snake()
{
}