#include "Level.h"
#include <iostream>
#include "shaderLoader.h"

Level::Level()
{
	shaderLoader* sl = new shaderLoader();
	transparent_shader = sl->loadProgram("shaders/transparent.vert", "shaders/transparent.frag");
	ObjectLoader loader = ObjectLoader();
	models = new Model[6];

	loader.loadModel("mountain/Mountain Dew Code Red soda can.obj");
	models[CAN] = loader.getModel();

	loader = ObjectLoader();
	loader.loadModel("Hulk/Hulk.obj");
	models[HULK] = loader.getModel();

	loader = ObjectLoader();
	loader.loadModel("Apple/app.obj");
	models[APPLE] = loader.getModel();

	loader = ObjectLoader();
	loader.loadModel("Ostrich/Ostrich.obj");
	models[OSTRICH] = loader.getModel();

	loader = ObjectLoader();
	loader.loadModel("fox/fox.obj");
	models[FOX] = loader.getModel();

	loader = ObjectLoader();
	loader.loadModel("wall/grade.obj");
	models[WALL] = loader.getModel();
}

void Level::init(GLint uroven, snake* sna){
	sn = sna;
	kon = false;
	float opacity = 1.0f;
	points = 0;
	obejct_info* tmp = new obejct_info();
	Vector3D* vec = new Vector3D();
	modely.clear();

	switch (uroven)
	{
	case 5:
		vec = new Vector3D(0.3, 0.3, 0.3);
		tmp->scale = vec;
		vec = new Vector3D(-7.2, 4.3, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = CAN;
		modely.push_back(tmp);

		tmp = new obejct_info();
		vec = new Vector3D(0.3, 0.3, 0.3);
		tmp->scale = vec;
		vec = new Vector3D(7.2, 4.3, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = -90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = CAN;
		modely.push_back(tmp);
		break;

		tmp = new obejct_info();
		vec = new Vector3D(0.3, 0.3, 0.3);
		tmp->scale = vec;
		vec = new Vector3D(7.2, 4.3, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = -90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = HULK;
		modely.push_back(tmp);
		break;
	case 10:
		vec = new Vector3D(0.3, 0.3, 0.3);
		tmp->scale = vec;
		vec = new Vector3D(-7.2, 4.3, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = CAN;
		modely.push_back(tmp);

		tmp = new obejct_info();
		vec = new Vector3D(0.3, 0.3, 0.3);
		tmp->scale = vec;
		vec = new Vector3D(7.2, 4.3, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = -90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = CAN;
		modely.push_back(tmp);

		tmp = new obejct_info();
		vec = new Vector3D(0.2, 0.2, 0.2);
		tmp->scale = vec;
		vec = new Vector3D(-10, 0, 10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = OSTRICH;
		modely.push_back(tmp);

		tmp = new obejct_info();
		vec = new Vector3D(0.2, 0.2, 0.2);
		tmp->scale = vec;
		vec = new Vector3D(-10, 9, 0);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 90;
		vec = new Vector3D(0, 1, 0);
		tmp->rotation1 = vec;
		tmp->model = APPLE;
		modely.push_back(tmp);

		


		// stena 4 //////////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.004, 0.004, 0.004);
		tmp->translate = new Vector3D(270, 500, -240);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = FOX;
		tmp->par = new ParticleSystem();
		tmp->par->setParticle(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), -90);
		tmp->par->setFont(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), -90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(15, 20, -10);
		tmp->rotation = new Vector3D(1, 1, 1);
		tmp->angle = 0;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(13.5, 20, 10.5);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(6.8, 20, -10);
		tmp->rotation = new Vector3D(1, 1, 1);
		tmp->angle = 0;
		tmp->model = WALL;
		modely.push_back(tmp);
		////////////////////////////////////////////////////////////////////////////////////////


		///stena 0 //////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(6.8, 20, 10);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = -90;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(6.8, 20, 2.5);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = -90;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(6.8, 20, -5);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = -90;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(10, -6, 0);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = -90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = APPLE;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(10);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(0, -3.9, 6), 90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(3, -1.1, -0.2), 90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.3, 0.3, 0.3);
		tmp->translate = new Vector3D(7.2, 5, 5);
		tmp->rotation = new Vector3D(0, 0, -1);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, 1, 0);;
		tmp->model = CAN;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(20);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(-4, 4.5, 6), 90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(3, 1.4, 1), 90);
		modely.push_back(tmp);


		tmp = new obejct_info();
		tmp->scale = new Vector3D(1, 1, 1);
		tmp->translate = new Vector3D(0, 0, 0);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = HULK;
		tmp->par = new ParticleSystem();
		tmp->par->setParticle(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), -90);
		tmp->par->setFont(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), -90);
		modely.push_back(tmp);
		/////koniec steny 0 /////////////////////////////////////////////////////////
		break;
	case 15:
		break;
	default:
		break;
	}
}

void Level::render(GLboolean draw){
	if (draw){
		for each (obejct_info* var in modely){
			glPushMatrix();
			if (var->model == WALL){
				glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
				glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
				models[WALL].render(true);
			}
			else{
				if (var->model == HULK)
				{
					glEnable(GL_BLEND); 
					glEnable(GL_CULL_FACE);
					glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
					glColor4f(0.5f, 0.5f, 0.5f, opacity);
					glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
					glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
					glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glRotatef(rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					models[var->model].render(true);
					glRotatef(-rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					glRotatef(-var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glTranslatef(-var->translate->getX(), -var->translate->getY(), -var->translate->getZ());
					glDisable(GL_BLEND);
					glDisable(GL_CULL_FACE);
					glColor3f(1,1,1);
					opacity -= 0.008f;
					if (opacity < 0){
						opacity = 1.0f;
					}
				} else
				if (var->par != NULL && !var->par->play){
					glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
					glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
					glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glRotatef(rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					models[var->model].render(true);
					glRotatef(-rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					glRotatef(-var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glTranslatef(-var->translate->getX(), -var->translate->getY(), -var->translate->getZ());
				}
			}
			glPopMatrix();
		}
		for each (obejct_info* var in modely){
			if (var->par != NULL && var->par->play){
				var->par->render();
			}
		}
	}
	else{
		obejct_info* var;
		for (vector<obejct_info*>::iterator it = modely.begin(); it != modely.end();){
			var = *it;
			glPushMatrix();
			if (var->model == WALL){
				glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
				glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
				models[WALL].render(false);
			}
			else{
				if (var->par != NULL && !var->par->play){
					glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
					glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
					glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glRotatef(rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					models[var->model].render(false);
					glRotatef(-rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
					glRotatef(-var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
					glTranslatef(-var->translate->getX(), -var->translate->getY(), -var->translate->getZ());
				}
			}
			++it;
			for (int i = 0; i < 8; i++){
				if (models[var->model].getCollision(sn->body[i].x, sn->body[i].y, sn->body[i].z)){
					if (var->model == WALL){
						kon = true;
					}
					else{
						if ((var->par != NULL && !var->par->play) && var->model != HULK){
							points += var->par->points;
							var->par->startParticle();
							sn->papam();
							break;
						}
					}
				}
			}
			if (var->par != NULL && var->par->canDelete()){
				it = modely.erase(--it);
			}
			glPopMatrix();
		}
		kon = kon || modely.size() == 0 || sn->narazeny;
	}

}

Level::~Level()
{
}
