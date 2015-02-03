#define _USE_MATH_DEFINES
#include "Sphere.h"
#include <math.h>
#include <stdlib.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"


Sphere::Sphere(int xSlices, int ySlices)
{
	size = 3 * (xSlices + 1) * (ySlices + 1);
	vertices = new float[size];
	float* normals = new float[size];
	float* texcoords = new float[2 * (xSlices + 1) * (ySlices + 1)];

	for (int i = 0; i <= xSlices; i++)
	{
		float u = i / float(xSlices);
		for (int j = 0; j <= ySlices; j++)
		{
			float v = j / float(ySlices);

			int index = i + j * (xSlices + 1);

			vertices[3 * index + 0] = cos(2 * u * M_PI) * cos((v - 0.5f) * M_PI);
			vertices[3 * index + 1] = sin(2 * u * M_PI) * cos((v - 0.5f) * M_PI);
			vertices[3 * index + 2] = sin((v - 0.5f) * M_PI);

			normals[3 * index + 0] = vertices[3 * index + 0];
			normals[3 * index + 1] = vertices[3 * index + 1];
			normals[3 * index + 2] = vertices[3 * index + 2];

			texcoords[2 * index + 0] = u;
			texcoords[2 * index + 1] = 1.0f - v;
		}
	}

	GLuint* indices = new GLuint[4 * xSlices * ySlices];
	int index = 0;
	for (int i = 0; i < xSlices; i++)
	{
		for (int j = 0; j < ySlices; j++)
		{
			indices[index++] = i + j * (xSlices + 1);
			indices[index++] = (i + 1) + j * (xSlices + 1);
			indices[index++] = (i + 1) + (j + 1) * (xSlices + 1);
			indices[index++] = i + (j + 1) * (xSlices + 1);
		}
	}

	glGenBuffers(1, &g_uiVBOSphereCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereCoords);
	glBufferData(GL_ARRAY_BUFFER, 3 * (xSlices + 1) * (ySlices + 1) * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereNormals);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereNormals);
	glBufferData(GL_ARRAY_BUFFER, 3 * (xSlices + 1) * (ySlices + 1) * sizeof(float), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereTexCoords);
	glBufferData(GL_ARRAY_BUFFER, 2 * (xSlices + 1) * (ySlices + 1) * sizeof(float), texcoords, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOSphereIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * (xSlices + 0) * (ySlices + 0) * sizeof(GLuint), indices, GL_STATIC_DRAW);

	g_uiSphereNumIndices = 4 * (xSlices + 0) * (ySlices + 0);

	delete[] normals;
	delete[] texcoords;
	delete[] indices;
	calculateBoundingBox();
}


void Sphere::renderBoundingBox(){
	glColor3f(1, 0, 0);
	glBegin(GL_LINES);
	glVertex3f(minX, minY, minZ);
	glVertex3f(maxX, minY, minZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, maxY, minZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(minX, minY, minZ);
	glVertex3f(minX, minY, maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(minX, maxY, maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, minY, maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, maxZ);
	glVertex3f(maxX, maxY, minZ);
	glEnd();





	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(maxX, minY, minZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(maxX, maxY, minZ);
	glVertex3f(minX, maxY, minZ);
	glEnd();


	glBegin(GL_LINES);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(maxX, minY, minZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(maxX, minY, maxZ);
	glVertex3f(minX, minY, maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, minY, maxZ);
	glEnd();

	glBegin(GL_LINES);
	glVertex3f(minX, maxY, maxZ);
	glVertex3f(minX, maxY, minZ);
	glEnd();




}


void Sphere::calculateBoundingBox(){
	minX = INT_MAX;
	minY = INT_MAX;
	minZ = INT_MAX;

	maxX = INT_MIN;
	maxY = INT_MIN;
	maxZ = INT_MIN;
	for (int i = 0; i < size; ){
		if (vertices[i] < minX){
			minX = vertices[i];
		}
		if (vertices[i] > maxX){
			maxX = vertices[i];
		}

		if (vertices[i+1] < minY){
			minY = vertices[i + 1];
		}
		if (vertices[i+1] > maxY){
			maxY = vertices[i + 1];
		}

		if (vertices[i+2] < minZ){
			minZ = vertices[i + 2];
		}
		if (vertices[i+2] > maxZ){
			maxZ = vertices[i + 2];
		}
		i += 3;
	}
}

void Sphere::render(){
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereCoords);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereNormals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	// draw a cube using buffer with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOSphereIndices);
	glDrawElements(GL_QUADS, g_uiSphereNumIndices, GL_UNSIGNED_INT, NULL);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

Sphere::~Sphere()
{
}
