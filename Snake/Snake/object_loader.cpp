
#include "assimp/Importer.hpp"
#include "assimp/scene.h"           
#include "assimp/postprocess.h"
#include <sstream>
#include <iostream>
#include <fstream>
#include <vector>
#include <stdio.h>

using namespace Assimp;
ObjectLoader::ObjectLoader(){
	scene = NULL;
	logFile.open("logfile.txt");
};

ObjectLoader::~ObjectLoader(){};

string ObjectLoader::toString(){
	return "";
};


bool fileExists(const string& fileName){
	ifstream inFile(fileName.c_str());
	return (inFile.fail() == false);
}

string getDircetory(const string& path){
	string dirName = "";
	bool slashFound = false;
	for (int i = path.length() - 1; i >= 0; i--){
		if (path[i] == '/'){
			slashFound = true;
		}
		if (slashFound){
			dirName = path[i] + dirName;
		}
	}
	return dirName;
}

bool ObjectLoader::loadModel(const string& fileName){
	if (fileExists(fileName) == false){
		cout << "FILE DOES NOT EXISTS!" << endl;
		return false;
	}
	Importer importer;
	scene = importer.ReadFile(fileName, aiProcess_Triangulate);

	/*
	aiProcess_CalcTangentSpace       |
	aiProcess_Triangulate            |
	aiProcess_JoinIdenticalVertices  |
	aiProcess_SortByPType
	*/

	if (!scene){
		cout << "Scene not loaded, beacuse: " << importer.GetErrorString() << endl;
		return false;
	}
	directory = getDircetory(fileName);
	cout << "directory: " << directory << endl;
	//loadTextures(directory, &model);
	processScene(&model);
	cout << "Import file " << fileName << " succesfull." << endl;
	logFile.close();
	return true;
};

void genMyBuffers(Mesh* mesh){
	static GLfloat vrcholy[] = { -1.0f, -1.0f, 0.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f, 0.0f, 0.0f, 2.0f };
	static GLfloat farby[] = { 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 0.5f, 0.5f, 0.5f };
	static GLuint indexy[] = { 0, 1, 3, 1, 2, 3, 0, 2, 1, 0, 3, 2 };
	glEnableClientState(GL_VERTEX_ARRAY);
	glVertexPointer(3, GL_FLOAT, 0, vrcholy);

	glGenBuffers(1, &(mesh->vertexBuffer));                  // Get A Valid Name
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);         // Bind The Buffer
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), vrcholy, GL_STATIC_DRAW);

	glGenBuffers(1, &(mesh->colorBuffer));                  // Get A Valid Name
	glBindBuffer(GL_ARRAY_BUFFER, mesh->colorBuffer);         // Bind The Buffer
	glBufferData(GL_ARRAY_BUFFER, 4 * 3 * sizeof(float), farby, GL_STATIC_DRAW);

	glGenBuffers(1, &(mesh->faceBuffer));                  // Get A Valid Name
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->faceBuffer);         // Bind The Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * 3 * sizeof(GLuint), indexy, GL_STATIC_DRAW);

	mesh->setFaceCount(4 * 3);

};

void printILError(){
	if (IL_INVALID_EXTENSION == ilGetError()){
		cout << "ERROR: Invalid extension " << endl;
	}
	else{
		cout << "error: " << ilGetError() << endl;
	}
}

// create blured copy 
/*
iluImageParameter(ILU_FILTER, ILU_SCALE_BELL);
int width = ilGetInteger(IL_IMAGE_WIDTH);
int height = ilGetInteger(IL_IMAGE_HEIGHT);
int depth = ilGetInteger(IL_IMAGE_DEPTH);
iluScale(width/4, height/4,depth);
iluScale(width, height,depth);
*/


ILubyte* loadImage(string path, ILuint* id){
	if (fileExists(path) == false){
		cout << "FILE DOES NOT EXISTS!" << endl;
		return NULL;
	}
	ilGenImages(1, id);
	ilBindImage(*id);
	ilEnable(IL_ORIGIN_SET);
	ilOriginFunc(IL_ORIGIN_LOWER_LEFT);
	ILboolean success = ilLoadImage((ILstring)path.c_str());
	if (success == false){
		printILError();
		return NULL;
	}
	ILubyte *data = ilGetData();
	return data;
}

void saveImage(GLuint& texId){
	stringstream stream;
	stream << "file" << texId << ".txt";
	cout << stream.str() << endl;
	ilSaveImage((ILstring)stream.str().c_str());
}

void loadTextureToOpenGL(GLuint& texId, string path){
	cout << "load to opengl...id: " << texId << " path: " << path << endl;
	ILuint imageName;
	ILubyte* data = loadImage(path, &imageName);
	glBindTexture(GL_TEXTURE_2D, texId);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	int width = ilGetInteger(IL_IMAGE_WIDTH);
	int height = ilGetInteger(IL_IMAGE_HEIGHT);
	int format = ilGetInteger(IL_IMAGE_FORMAT);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, data);
	// debugg ucely
	//saveImage(texId);

	ilDeleteImages(1, &imageName);
}


void ObjectLoader::loadTexture(aiMesh* sceneMesh, Mesh* mesh){
	map<string, string> names = getTextureNames(sceneMesh);
	int N = names.size();
	GLuint* textureIds = new GLuint[N];
	glGenTextures(N, textureIds);
	map<string, string>::iterator it = names.begin();
	for (unsigned int i = 0; it != names.end(); i++, it++){
		loadTextureToOpenGL(textureIds[i], directory + it->second);
		mesh->textureIds[it->first] = textureIds[i];
	}
	delete[] textureIds;
}

string aiToStr(aiString str){
	string result(str.data);
	result.resize(str.length);
	return result;
}

map<string, string> ObjectLoader::getTextureNames(aiMesh* sceneMesh){
	map<string, string> result;
	aiMaterial* material = scene->mMaterials[sceneMesh->mMaterialIndex];
	aiString pathDiff;
	aiString pathNormal;
	aiString pathAmbient;
	aiString pathEmmissive;
	aiString pathSpecular;

	aiReturn texFound = material->GetTexture(aiTextureType_DIFFUSE, 0, &pathDiff);
	if (texFound == AI_SUCCESS){
		result[TEX_DIFF] = aiToStr(pathDiff);
	}
	/* TODO odkomentovat a pouzit dakedy
	texFound = material->GetTexture(aiTextureType_HEIGHT,0, &pathNormal);
	if(texFound == AI_SUCCESS){
	result[TEX_NORM] = aiToStr(pathNormal);
	}
	texFound = material->GetTexture(aiTextureType_AMBIENT,0, &pathAmbient);
	if(texFound == AI_SUCCESS){
	result[TEX_AMB] = aiToStr(pathAmbient);
	}
	texFound = material->GetTexture(aiTextureType_EMISSIVE,0, &pathEmmissive);
	if(texFound == AI_SUCCESS){
	result[TEX_EMSS] = aiToStr(pathEmmissive);
	}
	texFound = material->GetTexture(aiTextureType_SPECULAR,0, &pathSpecular);
	if(texFound == AI_SUCCESS){
	result[TEX_SPEC] = aiToStr(pathSpecular);
	}
	*/
	return result;
}

// todo premenovat a zvysok upratat
void ObjectLoader::processScene(Model* model){
	if (sceneLoaded() == false){
		return;
	}
	for (unsigned int i = 0; i < scene->mNumMeshes; i++){
		aiMesh* sceneMesh = scene->mMeshes[i];
		Mesh mesh;
		//genMyBuffers(&mesh);
		loadTexture(sceneMesh, &mesh);
		genBuffers(sceneMesh, &mesh);
		model->addMesh(mesh);
	}
};

Vector3D* convert(aiVector3D* vectors, unsigned int count){
	Vector3D* result = new Vector3D[count];
	for (unsigned int i = 0; i < count; i++){
		result[i].setX(vectors[i].x);
		result[i].setY(vectors[i].y);
		result[i].setZ(vectors[i].z);
	}
	return result;
}


void ObjectLoader::genBuffers(aiMesh* sceneMesh, Mesh* mesh){
	intArray faces = createFaceArray(sceneMesh);
	mesh->setFaceCount(faces.second);
	genBufferForFaces(sceneMesh, &(mesh->faceBuffer));
	genBufferForVertices(sceneMesh, &(mesh->vertexBuffer));
	genBufferForNormals(sceneMesh, &(mesh->normalBuffer));
	genBufferForTexCoords(sceneMesh, &(mesh->texCoordBuffer));
	genBufferForColors(sceneMesh, &(mesh->colorBuffer));

	mesh->normals = convert(sceneMesh->mNormals, sceneMesh->mNumVertices);
	mesh->vertices = convert(sceneMesh->mVertices, sceneMesh->mNumVertices);
	mesh->verticesCount = sceneMesh->mNumVertices;

	unbindBuffers();
}


intArray ObjectLoader::createFaceArray(const struct aiMesh* mesh){
	int faceArraySize = mesh->mNumFaces * 3;
	GLuint* faceArray = new unsigned int[faceArraySize];
	int index = 0;
	for (unsigned int i = 0; i < mesh->mNumFaces; i++) {
		const struct aiFace face = mesh->mFaces[i];
		for (unsigned int j = 0; j < face.mNumIndices; j++){
			faceArray[index] = face.mIndices[j];
			index++;
		}
	}
	intArray result(faceArray, faceArraySize);
	return result;
}

void ObjectLoader::genBufferForFaces(aiMesh* mesh, GLuint *buffer){
	intArray faces = createFaceArray(mesh);
	logFile << "faces: " << endl;
	for (unsigned int i = 0; i < faces.second; i++){
		logFile << faces.first[i] << ", ";
		if (i % 10 == 9){
			logFile << endl;
		}
	}
	glGenBuffers(1, buffer); // buffer
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, faces.second*sizeof(GLuint), faces.first, GL_STATIC_DRAW);
}

void ObjectLoader::genBuffer(aiVector3D* coords, int size, GLuint *buffer){
	logFile << "buffer 1: " << endl;
	for (int i = 0; i < size; i++){
		logFile << coords[i].x << "-" << coords[i].y << "-" << coords[i].z << endl;
	}
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 3 * size, coords, GL_STATIC_DRAW);
	glEnableVertexAttribArray(*buffer);
	glVertexAttribPointer(*buffer, 3, GL_FLOAT, 0, 0, 0);
}

void ObjectLoader::genBufferForVertices(aiMesh* mesh, GLuint *buffer){
	if (mesh->HasPositions()){
		genBuffer(mesh->mVertices, mesh->mNumVertices, buffer);
	}
}

void ObjectLoader::genBufferForNormals(aiMesh* mesh, GLuint *buffer){
	if (mesh->HasNormals()){
		genBuffer(mesh->mNormals, mesh->mNumVertices, buffer);
	}
}

void ObjectLoader::genBufferForTexCoords(aiMesh* mesh, GLuint *buffer){
	if (mesh->HasTextureCoords(0)){
		logFile << "texture coords: " << endl;
		float *texCoords = new float[2 * mesh->mNumVertices];
		for (unsigned int i = 0; i < mesh->mNumVertices; i++){
			texCoords[i * 2] = mesh->mTextureCoords[0][i].x;
			texCoords[i * 2 + 1] = mesh->mTextureCoords[0][i].y;
			logFile << "x: " << texCoords[i * 2] << "y: " << texCoords[i * 2 + 1] << endl;
		}
		glGenBuffers(1, buffer);
		glBindBuffer(GL_ARRAY_BUFFER, *buffer);
		glBufferData(GL_ARRAY_BUFFER, sizeof(float)* 2 * mesh->mNumVertices, texCoords, GL_STATIC_DRAW);
		glEnableVertexAttribArray(*buffer);
		glVertexAttribPointer(*buffer, 2, GL_FLOAT, 0, 0, 0);
	}
};

void ObjectLoader::genBufferForColors(aiMesh* mesh, GLuint *buffer){
	for (unsigned int i = 0; i < mesh->mNumVertices; i++){
		if (mesh->HasVertexColors(i)){
			cout << mesh->mColors[i]->r << endl;
			cout << mesh->mColors[i]->g << endl;
			cout << mesh->mColors[i]->b << endl;
			cout << mesh->mColors[i]->a << endl;
		}
	}
	/*
	glGenBuffers(1, buffer);
	glBindBuffer(GL_ARRAY_BUFFER, *buffer);
	glBufferData(GL_ARRAY_BUFFER, sizeof(float)*4*mesh->mNumVertices, mesh->nColors, GL_STATIC_DRAW);
	*/
};

void ObjectLoader::unbindBuffers(){
	glBindVertexArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}