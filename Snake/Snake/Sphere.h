#pragma once
#include <stdlib.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"
class Sphere
{
	GLuint g_uiVBOSphereCoords, g_uiVBOSphereTexCoords, g_uiVBOSphereNormals, g_uiVBOSphereIndices, g_uiSphereNumIndices;
public:
	GLfloat posunX, posunY, posunZ;
	Sphere(int xSlices, int ySlices);
	void setPosition(GLfloat X, GLfloat Y, GLfloat  Z){
		posunX = X;
		posunY = Y;
		posunZ = Z;
	}
	void render();
	~Sphere();
};

