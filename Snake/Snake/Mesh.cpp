#include "Mesh.h"
#include <iostream>

Mesh::Mesh()
{
}

void Mesh::bindDiffuseTexture(){
	if (textureIds.find(TEX_DIFF) != textureIds.end()){
		//cout << textureIds[TEX_DIFF];
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, textureIds[TEX_DIFF]);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	}
};

Mesh::~Mesh()
{
}
