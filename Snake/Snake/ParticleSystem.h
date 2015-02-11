#pragma once
#define _USE_MATH_DEFINES
#include <windows.h>
#include <math.h>
#include <cmath>
#include "Vector3D.h"
#include "glew.h"
#include "glut-3.7.6-bin\glut.h"

#define NUM_PARTICLES 200

class ParticleSystem
{
	struct Particle
	{
		float position[3];
		float velocity[3];
		float color[4];
		float life;
	};

	Vector3D* rotation;
	Vector3D* translate;
	GLfloat angle;
	Vector3D* font_rotation;
	Vector3D* font_translate;
	GLfloat font_angle;
	Particle g_particle_system[NUM_PARTICLES];
	GLuint tex_point_sprite;
	GLfloat time = 10;
	float getRandomMinMax(float fMin, float fMax);
	void getRandomVector(float* vector);
	void initParticles();
public:
	GLboolean play = false;
	int points;
	ParticleSystem();
	void render(bool update);
	void updateParticles();
	void startParticle(){ if (!play){ play = true; } }
	bool canDelete(){
		return time < -400;
	};
	void setParticle(Vector3D* rot, Vector3D* trans, GLfloat ang){
		rotation = rot;
		translate = trans;
		angle = ang;
	};
	void setFont(Vector3D* rot, Vector3D* trans, GLfloat ang){
		font_rotation = rot;
		font_translate = trans;
		font_angle = ang;
	};
	void setPoints(int p){ points = p; };
	void decreaseTime(){ time -= 2; };
	~ParticleSystem();
};