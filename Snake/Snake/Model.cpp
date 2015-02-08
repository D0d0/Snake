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
	body = new vec4[8];
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

void Model::render(bool render){
	if (render){
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
	}
	else{
		calculatePoints();
	}
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
	glColor3f(1, 1, 1);

}

void Model::calculatePoints(){
	minX_w = INT_MAX;
	minY_w = INT_MAX;
	minZ_w = INT_MAX;

	maxX_w = INT_MIN;
	maxY_w = INT_MIN;
	maxZ_w = INT_MIN;

	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glm::mat4 modelViewMatrix = (glm::make_mat4(m));

	float bod[4] = { minX, minY, minZ, 1 };
	body[0] = modelViewMatrix*make_vec4(bod);

	float bo[4] = { maxX, minY, minZ, 1 };
	body[1] = modelViewMatrix*make_vec4(bo);

	float b[4] = { minX, maxY, minZ, 1 };
	body[2] = modelViewMatrix*make_vec4(b);

	float c[4] = { minX, minY, maxZ, 1 };
	body[3] = modelViewMatrix*make_vec4(c);

	float d[4] = { maxX, maxY, minZ, 1 };
	body[4] = modelViewMatrix*make_vec4(d);

	float e[4] = { maxX, minY, maxZ, 1 };
	body[5] = modelViewMatrix*make_vec4(e);

	float f[4] = { minX, maxY, maxZ, 1 };
	body[6] = modelViewMatrix*make_vec4(f);

	float g[4] = { maxX, maxY, maxZ, 1 };
	body[7] = modelViewMatrix*make_vec4(g);

	for (int i = 0; i < 8; i++){
		if (body[i].x < minX_w){
			minX_w = body[i].x;
		}
		if (body[i].x  > maxX_w){
			maxX_w = body[i].x;
		}

		if (body[i].y < minY_w){
			minY_w = body[i].y;
		}
		if (body[i].y > maxY_w){
			maxY_w = body[i].y;
		}

		if (body[i].z < minZ_w){
			minZ_w = body[i].z;
		}
		if (body[i].z > maxZ_w){
			maxZ_w = body[i].z;
		}
	}
}


bool Model::getCollision(GLfloat x, GLfloat y, GLfloat z){
	return minX_w <= x && x <= maxX_w &&
		minY_w <= y && y <= maxY_w &&
		minZ_w <= z && z <= maxZ_w;
}