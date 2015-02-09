#include "Level.h"
#include <iostream>

Level::Level()
{
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

		tmp = new obejct_info();
		vec = new Vector3D(0.004, 0.004, 0.004);
		tmp->scale = vec;
		vec = new Vector3D(-500, -10, 0);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 90;
		vec = new Vector3D(0, -1, 0);
		tmp->rotation1 = vec;
		tmp->model = FOX;
		modely.push_back(tmp);

		tmp = new obejct_info();
		vec = new Vector3D(0.1, 0.1, 0.1);
		tmp->scale = vec;
		vec = new Vector3D(0, -25, -10);
		tmp->translate = vec;
		vec = new Vector3D(0, 0, 1);
		tmp->rotation = vec;
		tmp->angle = 0;
		vec = new Vector3D(0, 0, 0);
		tmp->rotation1 = vec;
		tmp->model = WALL;
		modely.push_back(tmp);
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
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getY());
				models[WALL].render(true);
			}
			else{
				glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getY());
				glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glRotatef(rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
				models[var->model].render(true);
				glRotatef(-rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
				glRotatef(-var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glTranslatef(-var->translate->getX(), -var->translate->getY(), -var->translate->getY());
			}
			glPopMatrix();
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
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getY());
				models[var->model].render(false);
			}
			else{
				glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getY());
				glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glRotatef(rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
				models[var->model].render(false);
				glRotatef(-rotation, var->rotation1->getX(), var->rotation1->getY(), var->rotation1->getZ());
				glRotatef(-var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glTranslatef(-var->translate->getX(), -var->translate->getY(), -var->translate->getY());
			}
			++it;
			for (int i = 0; i < 8; i++){
				if (models[var->model].getCollision(sn->body[i].x, sn->body[i].y, sn->body[i].z)){
					if (var->model == WALL){
						//stena
					}
					else{
						it = modely.erase(--it);
						sn->papam();
						break;
					}
				}
			}
			glPopMatrix();
		}
	}

}

Level::~Level()
{
}
