#pragma once
#include <stdlib.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"
#include "Mesh.h"
#include <vector>
class Model
{
	vector<Mesh> meshes;
public:
	Model();
	int getSize(){ return meshes.size(); };
	void render();
	void addMesh(Mesh mesh){ meshes.push_back(mesh); };
	~Model();
};

