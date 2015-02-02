#include <stdlib.h>
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"
#include "assimp/Importer.hpp"
#include "assimp/scene.h"           
#include "assimp/postprocess.h"
#include "Model.h"
#include "Mesh.h"

typedef pair<unsigned int*, unsigned int> intArray;

const string programPath = "C:/Users/Jozef/Source/Repos/Snake/Snake/Snake/";

class ObjectLoader
{
	const aiScene* scene;
	string directory;
	Model model;
	void processScene(Model* model);
	bool sceneLoaded(){ return (scene != NULL); };
	void loadTexture(aiMesh* sceneMesh, Mesh* mesh);
	map<string, string> getTextureNames(aiMesh* sceneMesh);
	void genBuffers(aiMesh* sceneMesh, Mesh* mesh);
	void genBuffer(aiVector3D* coords, int size, GLuint *buffer);
	intArray createFaceArray(const struct aiMesh* mesh);
	void genBufferForFaces(aiMesh* mesh, GLuint *buffer);
	void genBufferForVertices(aiMesh* mesh, GLuint *buffer);
	void genBufferForNormals(aiMesh* mesh, GLuint *buffer);
	void genBufferForTexCoords(aiMesh* mesh, GLuint *buffer);
	void genBufferForColors(aiMesh* mesh, GLuint *buffer);
	void unbindBuffers();
public:
	ObjectLoader();
	bool loadModel(const string& fileName);
	Model getModel(){ if (sceneLoaded()){ return model; } };
	~ObjectLoader();
};
