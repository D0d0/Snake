#include "cubeVBO.h"
#include <iostream>
using namespace std;

cubeVBO::cubeVBO()
{
}


cubeVBO::~cubeVBO()
{
}

void cubeVBO::initCubeVBO()
{
	glGenBuffers(1, &g_uiVBOCubeCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeCoords);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), cube_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOCubeNormals);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeNormals);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), cube_normals, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOCubeTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeTexCoords);
	glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), cube_texcoords, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOCubeIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOCubeIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 4 * sizeof(GLuint), cube_indices, GL_STATIC_DRAW);
}

void cubeVBO::renderCubeVBO()
{
	if (g_uiVBOCubeCoords == 0){
		initCubeVBO();
	}

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeCoords);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOCubeNormals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	// draw a cube using buffer with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOCubeIndices);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}