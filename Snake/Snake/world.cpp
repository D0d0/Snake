#include <iostream>
#include "world.h"
#include "il.h"
#include "glew.h"
using namespace std;

GLfloat tex_vertices[] = { 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1, 1,
1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
-1, 1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1,
-1, -1, -1, 1, -1, -1, 1, -1, 1, -1, -1, 1,
1, -1, -1, -1, -1, -1, -1, 1, -1, 1, 1, -1 };
GLfloat tex_texcoords[] = { 0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1,
0, 0, 1, 0, 1, 1, 0, 1 };
GLuint tex_indices[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23 };

GLuint g_uiVBOVertices;
GLuint g_uiVBOTexCoords;
GLuint g_uiVBOTriangles;

ILuint texIL;
GLuint tex_cube;

world::world()
{

	// inicializuj VBO
	glGenBuffers(1, &g_uiVBOTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOTexCoords);
	glBufferData(GL_ARRAY_BUFFER, 24 * 2 * sizeof(float), tex_texcoords, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOVertices);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOVertices);
	glBufferData(GL_ARRAY_BUFFER, 24 * 3 * sizeof(float), tex_vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOTriangles);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOTriangles);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 6 * 4 * sizeof(GLuint), tex_indices, GL_STATIC_DRAW);

	// vynuluj nastavenie aktualnych bufferov
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	ilGenImages(1, &texIL);
	ilBindImage(texIL);
	// nacitanie textury zo suboru
	bool result = ilLoadImage("cube.jpg");
	cout << "textura" << result << endl;
	// generovanie OpenGL textur
	glGenTextures(1, &tex_cube);
	glBindTexture(GL_TEXTURE_2D, tex_cube);
	// nastavenie parametrov textury
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	// definovanie texlov
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT),
		0, ilGetInteger(IL_IMAGE_FORMAT), GL_UNSIGNED_BYTE, ilGetData());
	// zamzanie OpenIL textury
	ilDeleteImages(1, &texIL);
}

void world::render(){
	glPushMatrix();
	glScalef(2, 2, 2);
	glBindTexture(GL_TEXTURE_2D, tex_cube);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
	glEnable(GL_TEXTURE_2D);

	// aktivuje 2 bufre s atributmi
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOVertices);
	glVertexPointer(3, GL_FLOAT, 0, NULL);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	// draw a cube using buffer with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOTriangles);
	glDrawElements(GL_QUADS, 24, GL_UNSIGNED_INT, NULL);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	glDisable(GL_TEXTURE_2D);
	glPopMatrix();
}


world::~world()
{
}
