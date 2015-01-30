#pragma once

#include <iostream>
#include "glew.h"
using namespace std;
class skybox 
{
	GLuint tex_skybox, shaders_skybox;
	GLuint g_uiVBOCubeCoords = 0, g_uiVBOCubeTexCoords = 0, g_uiVBOCubeNormals = 0, g_uiVBOCubeIndices = 0;
public:
	skybox();
	void renderCubeVBO();
	void render();
	~skybox();
};

