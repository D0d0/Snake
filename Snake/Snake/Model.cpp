#include "Model.h"
#include <iostream>
#include <stdlib.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"
using namespace std;

Model::Model()
{
}


Model::~Model()
{
}

void Model::render(){
	glEnable(GL_TEXTURE_2D);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glEnableClientState(GL_VERTEX_ARRAY);
	bool texturing = true;
	for (int i = getSize() - 1; i >= 0; i--){
		Mesh mesh = meshes[i];
		mesh.bindDiffuseTexture();
		glBindBuffer(GL_ARRAY_BUFFER, mesh.normalBuffer);
		glNormalPointer(GL_FLOAT, 0, NULL);
		glBindBuffer(GL_ARRAY_BUFFER, mesh.vertexBuffer);
		glVertexPointer(3, GL_FLOAT, 0, (char *)NULL);       // Set The Vertex Pointer To The Vertex Buffer
		glBindBuffer(GL_ARRAY_BUFFER, mesh.texCoordBuffer);
		glTexCoordPointer(2, GL_FLOAT, 0, (char *)NULL);

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.faceBuffer);

		glDrawElements(GL_TRIANGLES, mesh.getFaceCount(), GL_UNSIGNED_INT, NULL);

		glBindTexture(GL_TEXTURE_2D, 0);
		glDisable(GL_TEXTURE_2D);
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
};
