#pragma once
#include <stdlib.h>
#include "glut-3.7.6-bin\glut.h"
#include <sstream>
#include <map>
#include "Vector3D.h"
using namespace std;

const string TEX_DIFF = "diffuse";
const string TEX_NORM = "normal";
const string TEX_AMB = "ambient";
const string TEX_EMSS = "emissive";
const string TEX_SPEC = "specular";

class Mesh
{
	int faceCount;
public:
	GLfloat maxX, minX, maxY, minY, maxZ, minZ;
	int verticesCount;
	Vector3D *normals;
	Vector3D *vertices;
	GLuint vertexBuffer;
	GLuint colorBuffer;
	GLuint normalBuffer;
	GLuint faceBuffer;
	GLuint texCoordBuffer;
	Mesh();
	map<string, GLuint> textureIds;
	void bindDiffuseTexture();
	int getFaceCount(){ return faceCount; };
	void setFaceCount(int count){ faceCount = count; };
	void setBundingBox();
	~Mesh();
};

