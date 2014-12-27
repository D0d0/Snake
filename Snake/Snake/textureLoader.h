#pragma once
#include <stdio.h>
#include "glew.h"
class textureLoader
{
public:
	textureLoader();
	GLuint LoadTexture(const char* tex_file);
	GLuint LoadCubeTexture(const char* tex_pos_x_file, const char* tex_neg_x_file,
		const char* tex_pos_y_file, const char* tex_neg_y_file,
		const char* tex_pos_z_file, const char* tex_neg_z_file);
	~textureLoader();
};