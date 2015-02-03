#include "Model.h"
#include <stdlib.h>
#include <stdio.h>
#include <tchar.h>
#include <sstream>
#include <iostream>
#include <fstream>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"

using namespace std;

Model::Model()
{
	//logFile.open("log.txt");
}


Model::~Model()
{
}

void Model::calculateBoundingBox(){
	minX = INT_MAX;
	minY = INT_MAX;
	minZ = INT_MAX;

	maxX = INT_MIN;
	maxY = INT_MIN;
	maxZ = INT_MIN;
	for (int i = getSize() - 1; i >= 0; i--){
		Mesh mesh = meshes[i];
		if (mesh.minX < minX){
			minX = mesh.minX;
		}
		if (mesh.maxX > maxX){
			maxX = mesh.maxX;
		}

		if (mesh.minY < minY){
			minY = mesh.minY;
		}
		if (mesh.maxY > maxY){
			maxY = mesh.maxY;
		}

		if (mesh.minZ < minZ){
			minZ = mesh.minZ;
		}
		if (mesh.maxZ > maxZ){
			maxZ = mesh.maxZ;
		}
	}
}

void Model::render(){
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	for (int i = getSize() - 1; i >= 0; i--){
		Mesh mesh = meshes[i];
		mesh.bindDiffuseTexture();
		glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
		glNormalPointer(GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
		glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.texCoordBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.faceBuffer);

		glDrawElements(GL_TRIANGLES, mesh.getFaceCount(), GL_UNSIGNED_INT, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
	calculatePoints();
};

void Model::renderBoundingBox(){
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

void Model::calculatePoints(){

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glm::mat4 modelViewMatrix = glm::make_mat4(m);

	float bod[4] = { minX, minY, minZ, 1 };
	bod1 = modelViewMatrix*make_vec4(bod);

	float g[4] = { maxX, maxY, maxZ, 1 };
	bod8 = modelViewMatrix*make_vec4(g);
}


bool Model::getCollision(GLfloat x, GLfloat y, GLfloat z){
	if (bod1.x >= x && bod8.x <= x && bod1.y <= y && bod8.y >= y && bod1.z <= z && bod8.z >= z){
		cout << "kolizia" << endl;
	}
/*	if (bod1.x <= x && bod8.x >= x){
		cout << "x" << endl;
	}
	if (bod1.y <= y && bod8.y >= y){
		cout << "y" << endl;
	}
	if (bod1.z <= z && bod8.z >= z){
		cout << "z" << endl;
	}
	cout << "-----------------" << endl;*/
	return bod1.x >= x && bod8.x <= x && bod1.y <= y && bod8.y >= y && bod1.z <= z && bod8.z >= z;
}