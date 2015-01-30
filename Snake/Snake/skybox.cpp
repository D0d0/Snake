#include "skybox.h"
#include "textureLoader.h"
#include "shaderLoader.h"
#include <iostream>
using namespace std;


GLfloat cube_vertices[] = { 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1,
1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
-1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1,
-1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,
1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1 };
GLfloat cube_normals[] = { 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1,
1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0,
0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0,
-1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0,
0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1, 0,
0, 0, -1, 0, 0, -1, 0, 0, -1, 0, 0, -1 };
GLfloat cube_texcoords[] = { 0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1 };
GLuint cube_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

skybox::skybox()
{
	textureLoader* tl = new textureLoader();
	tex_skybox = tl->LoadCubeTexture("skybox/snow_positive_x.jpg", "skybox/snow_negative_x.jpg",
		"skybox/snow_positive_y.jpg", "skybox/snow_negative_y.jpg",
		"skybox/snow_positive_z.jpg", "skybox/snow_negative_z.jpg");
	shaderLoader* sl = new shaderLoader();
	shaders_skybox = sl->loadProgram("shaders/skybox.vert", "shaders/skybox.frag");
	sl->SetShaderUniform1i(shaders_skybox, "cube_map", 0);

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

void skybox::render(){
	glUseProgram(shaders_skybox);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_skybox);
	glPushMatrix();
	glScalef(500, 500, 500);
	renderCubeVBO();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
}

void skybox::renderCubeVBO()
{
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


skybox::~skybox()
{
}
