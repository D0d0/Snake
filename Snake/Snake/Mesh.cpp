#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

void Mesh::bindDiffuseTexture(){
	if (textureIds.find(TEX_DIFF) != textureIds.end()){
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureIds[TEX_DIFF]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
};

void Mesh::setBundingBox(){
	for (int i = 0; i < verticesCount; i++){
		if (vertices[i].getX() < minX){
			minX = vertices[i].getX();
		}
		if (vertices[i].getX() > maxX){
			maxX = vertices[i].getX();
		}

		if (vertices[i].getY() < minY){
			minY = vertices[i].getY();
		}
		if (vertices[i].getY() > maxY){
			maxY = vertices[i].getY();
		}

		if (vertices[i].getZ() < minZ){
			minZ = vertices[i].getZ();
		}
		if (vertices[i].getZ() > maxZ){
			maxZ = vertices[i].getZ();
		}
	}
}

Mesh::~Mesh()
{
}