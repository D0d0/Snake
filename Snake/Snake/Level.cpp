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
	hulk_stena = -10;
	points = 0;
	priehladny = false;
	hulk_dopadol = false;
	hulk = NULL;
	opacity = 1;
	obejct_info* tmp = new obejct_info();
	Vector3D* vec = new Vector3D();
	modely.clear();
	this->uroven = uroven;
	time = 0.0f;
	switch (uroven)
	{
	case 5:
	case 10:
		// stena 0///////////////////////////////////////////////////////////////////////////
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
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(-10, 20, 15);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = -90;
		tmp->model = WALL;
		modely.push_back(tmp);
		//////////////////////////////////////////////////////////////////////////////////
		
		//stena 3////////////////////////////////////////////////////////////////////


		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(5, 20, -5);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = 90;
		tmp->model = WALL;
		modely.push_back(tmp);
		///////////////////////////////////////////////////


		// stena 4 //////////////////////////////////////////////////////////////////////////
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


		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(0, 20, 10.5);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->model = WALL;
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.1, 0.1, 0.1);
		tmp->translate = new Vector3D(0, 20, -10);
		tmp->rotation = new Vector3D(1, 1, 1);
		tmp->angle = 0;
		tmp->model = WALL;
		modely.push_back(tmp);
		////////////////////////////////////////////////////////////////////////////////////////
	case 15:
		////stena 1 ///////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(5, -3, 10);
		tmp->rotation = new Vector3D(1, 0, 0);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = APPLE;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(10);
		tmp->par->setParticle(new Vector3D(0, 0, 1), new Vector3D(-2, -3, 6), 90);
		tmp->par->setFont(new Vector3D(1, 1, 1), new Vector3D(1, -0.5, 3), 0);
		modely.push_back(tmp);
		///////////////////////////////////////////////////////////////////////////////////	
		
		
		////stena 3 ///////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(5, -3, -10);
		tmp->rotation = new Vector3D(1, 0, 0);
		tmp->angle = -90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = APPLE;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(10);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(-3, -2, 6), 180);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(1, -0.5, -3), 180);
		modely.push_back(tmp);
		///////////////////////////////////////////////////////////////////////////////////


		////stena 4///////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.004, 0.004, 0.004);
		tmp->translate = new Vector3D(270, 500, -240);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = FOX;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(40);
		tmp->par->setParticle(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), -90);
		tmp->par->setFont(new Vector3D(1, 0, 0), new Vector3D(1.3, 3.6, -1), 90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.3, 0.3, 0.3);
		tmp->translate = new Vector3D(-5, 7.2, 2);
		tmp->rotation = new Vector3D(0, 1, 0);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = CAN;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(20);
		tmp->par->setParticle(new Vector3D(-1, 0, 0), new Vector3D(-4.9, -2.0, 6), 90);
		tmp->par->setFont(new Vector3D(1, 0, 0), new Vector3D(-0.9, 3.6, 0.7), 90);
		modely.push_back(tmp);
		///////////////////////////////////////////////////////////////////////////////

		////stena 5///////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(5, -10, 5);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = 180;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = OSTRICH;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(30);
		tmp->par->setParticle(new Vector3D(1, 0, 0), new Vector3D(3.6, 3.6, 6), 90);
		tmp->par->setFont(new Vector3D(1, 0, 0), new Vector3D(1.3, -3.6, 1), 90);
		modely.push_back(tmp);
		///////////////////////////////////////////////////////////////////////////////


		////stena 2/////////////////////////////////////////////////////////////////////
		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(-10, 8, 0);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = APPLE;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(10);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(0, 5.5, 6), -90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(-3, 1.7, 0.3), -90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(-10, -8, 0);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, -1, 0);
		tmp->model = APPLE;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(10);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(0, -5.5, 6), -90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(-3, -1.7, 0.3), -90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.004, 0.004, 0.004);
		tmp->translate = new Vector3D(-500, 0, 0);
		tmp->rotation = new Vector3D(0, 0, 1);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = FOX;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(40);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(0, 0, 6), -90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(-3.6, 0, 0), -90);
		modely.push_back(tmp);
		/////////////////////////////////////////////////////////////////////////////////


		///stena 0 //////////////////////////////////////////////////////////////////////
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
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = CAN;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(20);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(-4, 4.5, 6), 90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(3, 1.4, 1), 90);
		modely.push_back(tmp);

		tmp = new obejct_info();
		tmp->scale = new Vector3D(0.2, 0.2, 0.2);
		tmp->translate = new Vector3D(10, 5, -5);
		tmp->rotation = new Vector3D(0, 0, -1);
		tmp->angle = 90;
		tmp->rotation1 = new Vector3D(0, 1, 0);
		tmp->model = OSTRICH;
		tmp->par = new ParticleSystem();
		tmp->par->setPoints(30);
		tmp->par->setParticle(new Vector3D(0, 1, 0), new Vector3D(3.5, 3.5, 6), 90);
		tmp->par->setFont(new Vector3D(0, 0, 1), new Vector3D(3, 1, -1), 90);
		modely.push_back(tmp);
		/////koniec steny 0 /////////////////////////////////////////////////////////
		break;
	default:
		break;
	}
	switch (uroven)
	{
	case 5:
	case 10:
		break;
	case 15:
		count = 0;
		break;
	default:
		break;
	}
}

void Level::generujHulk(){
	priehladny = false;
	hulk_dopadol = false;
	opacity = 1;
	int r = rand() % 6;
	switch (r)
	{
	case 0:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(10, 0, 0);
		hulk->rotation = new Vector3D(0, 0, 1);
		hulk->angle = -90;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(-0.02, 0, 0);
		break;
	case 1:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(0, 0, 10);
		hulk->rotation = new Vector3D(1, 0, 0);
		hulk->angle = 90;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(0, 0, -0.02);
		break;
	case 2:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(-10, 0, 0);
		hulk->rotation = new Vector3D(0, 0, 1);
		hulk->angle = 90;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(0.02, 0, 0);
		break;
	case 3:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(0, 0, -10);
		hulk->rotation = new Vector3D(1, 0, 0);
		hulk->angle = -90;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(0, 0, 0.02);
		break;
	case 4:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(0, 10, 0);
		hulk->rotation = new Vector3D(0, 1, 0);
		hulk->angle = 90;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(0, -0.02, 0);
		break;
	case 5:
		hulk = new obejct_info();
		hulk->scale = new Vector3D(0.5, 0.5, 0.5);
		hulk->translate = new Vector3D(0, -10, 0);
		hulk->rotation = new Vector3D(0, 0, 1);
		hulk->angle = 180;
		hulk->rotation1 = new Vector3D(1, 1, 1);
		hulk_posun = new Vector3D(0, 0.02, 0);
		break;
	default:
		break;
	}
	hulk_stena = r;
}

void Level::HulkNext(){
	switch (hulk_stena)
	{
	case 0:
		hulk_dopadol = hulk->translate->getX() <= 4;
		break;
	case 1:
		hulk_dopadol = hulk->translate->getZ() <= 4;
		break;
	case 2:
		hulk_dopadol = hulk->translate->getX() >= -4;
		break;
	case 3:
		hulk_dopadol = hulk->translate->getZ() >= -4;
		break;
	case 4:
		hulk_dopadol = hulk->translate->getY() <= 4;
		break;
	case 5:
		hulk_dopadol = hulk->translate->getY() >= -4;
		break;
	default:
		break;
	}
	if (hulk_dopadol){
		opacity -= 0.008f;
		priehladny = true;
	}
	else{
		hulk->translate->setX(hulk_posun->getX() + hulk->translate->getX());
		hulk->translate->setY(hulk_posun->getY() + hulk->translate->getY());
		hulk->translate->setZ(hulk_posun->getZ() + hulk->translate->getZ());
	}
	if (opacity < 0){
		points += 10;
		priehladny = false;
		opacity = 1.0f;
		time = 0.0f;
	}
}

void Level::render(GLboolean draw){
	if (draw){
		time += 0.1;
		if (time > 50 && uroven == 5 && (hulk_dopadol || hulk == NULL) && !priehladny){
			generujHulk();
		}
		for each (obejct_info* var in modely){
			glPushMatrix();
			if (var->model == WALL){
				glScalef(var->scale->getX(), var->scale->getY(), var->scale->getZ());
				glRotatef(var->angle, var->rotation->getX(), var->rotation->getY(), var->rotation->getZ());
				glTranslatef(var->translate->getX(), var->translate->getY(), var->translate->getZ());
				models[WALL].render(true);
			}
			else{
				if (var->model == HULK && time > 50)
				{
				}
				else
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
		if (hulk != NULL && time > 50 && uroven == 5){
			glPushMatrix();
			glEnable(GL_BLEND);
			glEnable(GL_CULL_FACE);
			glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
			glColor4f(0.5f, 0.5f, 0.5f, opacity);
			glScalef(hulk->scale->getX(), hulk->scale->getY(), hulk->scale->getZ());
			glTranslatef(hulk->translate->getX(), hulk->translate->getY(), hulk->translate->getZ());
			glRotatef(hulk->angle, hulk->rotation->getX(), hulk->rotation->getY(), hulk->rotation->getZ());
			models[HULK].render(true);
			glRotatef(-hulk->angle, hulk->rotation->getX(), hulk->rotation->getY(), hulk->rotation->getZ());
			glTranslatef(-hulk->translate->getX(), -hulk->translate->getY(), -hulk->translate->getZ());
			glDisable(GL_BLEND);
			glDisable(GL_CULL_FACE);
			glColor3f(1, 1, 1);
			if (!kon){
				HulkNext();
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
		kon = kon || modely.size() == count || sn->narazeny || (uroven == 5 && hulk_dopadol && sn->getWall() == hulk_stena);
	}

}

Level::~Level()
{
}
