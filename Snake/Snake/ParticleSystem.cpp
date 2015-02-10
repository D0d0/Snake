#include "ParticleSystem.h"
#include "textureLoader.h"
#include "fonts.h"
#include <string>

ParticleSystem::ParticleSystem()
{
	textureLoader* tl = new textureLoader();
	tex_point_sprite = tl->LoadTexture("textures/particle.png");
	initParticles();
}


ParticleSystem::~ParticleSystem()
{
}

float ParticleSystem::getRandomMinMax(float fMin, float fMax)
{
	float fRandNum = (float)rand() / RAND_MAX;
	return fMin + (fMax - fMin) * fRandNum;
}

void ParticleSystem::getRandomVector(float* vector)
{
	vector[2] = getRandomMinMax(0.4f, 1.0f);
	float radius = (float)sqrt(1 - vector[2] * vector[2]);
	float t = getRandomMinMax(-M_PI, M_PI);
	vector[0] = (float)cosf(t) * radius;
	vector[1] = (float)sinf(t) * radius;
}

void ParticleSystem::initParticles()
{
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		g_particle_system[i].position[0] = 0;
		g_particle_system[i].position[1] = 0;
		g_particle_system[i].position[2] = 0;
		getRandomVector(g_particle_system[i].velocity);
		g_particle_system[i].color[0] = getRandomMinMax(0.0f, 1.0f);
		g_particle_system[i].color[1] = getRandomMinMax(0.0f, 1.0f);
		g_particle_system[i].color[2] = getRandomMinMax(0.0f, 1.0f);
		g_particle_system[i].color[3] = getRandomMinMax(0.0f, 0.4f);
		g_particle_system[i].life = getRandomMinMax(1.0f, 3.0f);
	}
}

void ParticleSystem::updateParticles()
{
	static double dLastFrameTime = timeGetTime();
	double dCurrenFrameTime = timeGetTime();
	double dElpasedFrameTime = (float)((dCurrenFrameTime - dLastFrameTime) * 0.001);
	dLastFrameTime = dCurrenFrameTime;
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		g_particle_system[i].position[0] += (float)dElpasedFrameTime * g_particle_system[i].velocity[0];
		g_particle_system[i].position[1] += (float)dElpasedFrameTime * g_particle_system[i].velocity[1];
		g_particle_system[i].position[2] += (float)dElpasedFrameTime * g_particle_system[i].velocity[2];
		g_particle_system[i].life -= dElpasedFrameTime;
		if ((g_particle_system[i].life < 0 || g_particle_system[i].position[2] < 0) && time > 0)
		{
			g_particle_system[i].position[0] = 0;
			g_particle_system[i].position[1] = 0;
			g_particle_system[i].position[2] = 0;
			getRandomVector(g_particle_system[i].velocity);
			g_particle_system[i].color[0] = getRandomMinMax(0.0f, 1.0f);
			g_particle_system[i].color[1] = getRandomMinMax(0.0f, 1.0f);
			g_particle_system[i].color[2] = getRandomMinMax(0.0f, 1.0f);
			g_particle_system[i].color[3] = getRandomMinMax(0.0f, 0.4f);
			g_particle_system[i].life = getRandomMinMax(1.0f, 3.0f);
		}
	}
	decreaseTime();
}


void ParticleSystem::render()
{
	if (!play){
		return;
	}
	updateParticles();
	glPushMatrix();
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);
	glDepthMask(GL_FALSE);
	glScalef(0.3, 0.3, 0.3);
	glRotatef(angle, rotation->getX(), rotation->getY(), rotation->getZ());
	glTranslatef(translate->getX(), translate->getY(), translate->getZ());

	float quadratic[] = { 1.0f, 0.0f, 0.01f };
	glPointParameterfvARB(GL_POINT_DISTANCE_ATTENUATION_ARB, quadratic);
	glPointSize(50);
	glPointParameterfARB(GL_POINT_FADE_THRESHOLD_SIZE_ARB, 60.0f);
	glPointParameterfARB(GL_POINT_SIZE_MIN_ARB, 1.0f);
	glPointParameterfARB(GL_POINT_SIZE_MAX_ARB, 50.0f);

	glBindTexture(GL_TEXTURE_2D, tex_point_sprite);
	glTexEnvf(GL_POINT_SPRITE_ARB, GL_COORD_REPLACE_ARB, GL_TRUE);
	glEnable(GL_POINT_SPRITE_ARB);
	glEnable(GL_TEXTURE_2D);
	glBegin(GL_POINTS);
	for (int i = 0; i < NUM_PARTICLES; i++)
	{
		glColor4fv(g_particle_system[i].color);
		glVertex3fv(g_particle_system[i].position);
	}
	glEnd();
	glDisable(GL_POINT_SPRITE_ARB);

	glDepthMask(GL_TRUE);
	glDisable(GL_BLEND);
	glPopMatrix();

	glEnable(GL_LIGHTING);
	glEnable(GL_LIGHT0);
	glColor3f(0.0f, 1.0f, 1.0f);
	render3DTextWGL(font_translate, font_rotation, font_angle, GLUT_STROKE_ROMAN, std::to_string(points).c_str());
	glDisable(GL_LIGHTING);
	glDisable(GL_LIGHT0);
}