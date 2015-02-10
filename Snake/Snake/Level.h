#pragma once
#include "snake.h"
#include "ObjectLoader.h"
#include "Model.h"
#include "ParticleSystem.h"
#include "glut-3.7.6-bin\glut.h"


struct obejct_info{
	Vector3D* scale;
	Vector3D* translate;
	Vector3D* rotation;
	Vector3D* rotation1;
	ParticleSystem* par;
	GLfloat angle;
	GLint model;
};

class Level
{
	float opacity = 1.0f;
	const GLint HULK = 0;
	const GLint WALL = 1;
	const GLint CAN = 2;
	const GLint APPLE = 3;
	const GLint OSTRICH = 4;
	const GLint FOX = 5;
	GLint transparent_shader;
	GLfloat rotation = 0.0f;
	Model* models;
	vector<obejct_info*> modely;
	snake* sn;
	bool kon = false;
public:
	int points = 0;
	Level();
	void init(GLint uroven, snake* sna);
	void render(GLboolean draw);
	void rotate(){
		rotation += 0.5f;
	};
	bool koniec(){
		return kon;
	};
	~Level();
};

