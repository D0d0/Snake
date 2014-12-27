#pragma once
#include <stdio.h>
#include "glew.h"
class shaderLoader{
	GLchar* readShaderFile(const char *fileName);
public:
	shaderLoader();
	GLuint loadShader(GLenum shaderType, const char *fileName);
	GLuint loadProgram(const char *fileVertexShader, const char *fileFragmentShader);
	bool SetShaderUniform1i(GLuint program, const char* name, GLint value);
	bool SetShaderUniform4f(GLuint program, const char* name, GLfloat* values);
	bool SetShaderUniformMatrix4f(GLuint program, const char* name, GLfloat* values);
	~shaderLoader();
};

