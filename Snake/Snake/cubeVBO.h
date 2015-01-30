#pragma once
#include <iostream>
using namespace std;
#include "glew.h"
class cubeVBO
{
protected:

	GLuint g_uiVBOCubeCoords = 0, g_uiVBOCubeTexCoords = 0, g_uiVBOCubeNormals = 0, g_uiVBOCubeIndices = 0;
	void initCubeVBO();
	void renderCubeVBO();
public:
	cubeVBO();
	~cubeVBO();
};

