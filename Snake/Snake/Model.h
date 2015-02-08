#pragma once
#include <stdlib.h>
#include <stdio.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"
#include "Mesh.h"
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include <vector>

using namespace glm;
using namespace std;

class Model
{
	vector<Mesh> meshes;
public:
	vec4* body;
	GLfloat maxX, minX, maxY, minY, maxZ, minZ;
	GLfloat maxX_w, minX_w, maxY_w, minY_w, maxZ_w, minZ_w;
	Model();
	void calculatePoints();
	int getSize(){ return meshes.size(); };
	void calculateBoundingBox();
	void render(bool render);
	void renderBoundingBox();
	void addMesh(Mesh mesh){ meshes.push_back(mesh); };
	bool getCollision(GLfloat x, GLfloat y, GLfloat z);
	~Model();
};

