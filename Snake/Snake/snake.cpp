#include "snake.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Vector3D.h"
#include <ctime>

using namespace std;

snake::snake()
{
	posunX = 2.1f;
	posunY = 0.0f;
	posunZ = 0.0f;
	hlava = new Sphere(15, 15);
	chvost = new Sphere(15, 15);
	quadratic = gluNewQuadric();
	rotation = new Vector3D();
	rotation->setX(0.0f);
	rotation->setY(1.0f);
	rotation->setZ(0.0f);
	secondRotation = Body();
	nullSecondrotation();
	body = new vec4[8];
}

void snake::nullSecondrotation(){
	secondRotation.second_rotation = new Vector3D(0, 0, 0);
	secondRotation.second_rotation_angle = 0;
}

void snake::setDirection(GLint dir){
	switch (dir){
	case GLUT_KEY_DOWN:
		if (up || down){
			return;
		}
		if (dir >= 100 && dir <= 103){
			addBody();
		}
		up = false;
		righ = false;
		down = true;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (up || down){
			return;
		}
		if (dir >= 100 && dir <= 103){
			addBody();
		}
		up = true;
		righ = false;
		down = false;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (righ || lef){
			return;
		}
		if (dir >= 100 && dir <= 103){
			addBody();
		}
		up = false;
		righ = false;
		down = false;
		lef = true;
		break;
	case GLUT_KEY_RIGHT:
		if (righ || lef){
			return;
		}
		if (dir >= 100 && dir <= 103){
			addBody();
		}
		up = false;
		righ = true;
		down = false;
		lef = false;
		break;
	default:
		break;
	}
}

void snake::calculateRotations(){
	if (down){
		if (getWall() == 0){
			rotation_angle = -180;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			secondRotation.second_rotation_angle = 180;
			secondRotation.second_rotation->setX(1);
			secondRotation.second_rotation->setY(0);
			secondRotation.second_rotation->setZ(0);
		}
		if (getWall() == 1){
			rotation_angle = -90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 2){
			rotation_angle = -180;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			secondRotation.second_rotation_angle = 180;
			secondRotation.second_rotation->setX(1);
			secondRotation.second_rotation->setY(0);
			secondRotation.second_rotation->setZ(0);
		}
		if (getWall() == 3){
			rotation_angle = -90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 4){
			rotation_angle = 180;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			secondRotation.second_rotation_angle = 180;
			secondRotation.second_rotation->setX(1);
			secondRotation.second_rotation->setY(0);
			secondRotation.second_rotation->setZ(0);
		}
		if (getWall() == 5){
			rotation_angle = 180;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			secondRotation.second_rotation_angle = 180;
			secondRotation.second_rotation->setX(1);
			secondRotation.second_rotation->setY(0);
			secondRotation.second_rotation->setZ(0);
		}
		return;
	}
	if (up){
		if (getWall() == 0){
			rotation_angle = 180;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 1){
			rotation_angle = 90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 2){
			rotation_angle = 180;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 3){
			rotation_angle = 90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 4){
			rotation_angle = 180;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 5){
			rotation_angle = -180;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		return;
	}
	if (lef){
		if (getWall() == 0){
			rotation_angle = -90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 1){
			rotation_angle = -90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 2){
			rotation_angle = 90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 3){
			rotation_angle = -90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 4){
			rotation_angle = -90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 5){
			rotation_angle = 90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		return;
	}
	if (righ){
		if (getWall() == 0){
			rotation_angle = 90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 1){
			rotation_angle = 90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 2){
			rotation_angle = -90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 3){
			rotation_angle = 90;
			rotation->setX(1.0f);
			rotation->setY(0.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 4){
			rotation_angle = 90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		if (getWall() == 5){
			rotation_angle = -90;
			rotation->setX(0.0f);
			rotation->setY(1.0f);
			rotation->setZ(0.0f);
			nullSecondrotation();
		}
		return;
	}
}

void snake::addBody(){
	Vector3D* tmp = new Vector3D(getPosunX(), getPosunY(), getPosunZ());
	Vector3D* rotatio = new Vector3D(rotation->getX(), rotation->getY(), rotation->getZ());
	Body bod = Body();
	bod.posun = tmp;
	bod.rotation = rotatio;
	bod.size = size;
	bod.rotation_angle = rotation_angle;
	size = 0.0;
	bod.second_rotation = secondRotation.second_rotation;
	bod.second_rotation_angle = secondRotation.second_rotation_angle;
	bod.wall = wall;
	bod.up = up;
	bod.down = down;
	bod.righ = righ;
	bod.lef = lef;
	telo.insert(telo.begin(), bod);
	addSphere();
}

void snake::addSphere(){
	Sphere* tmp = new Sphere(15, 15);
	tmp->setPosition(getPosunX(), getPosunY(), getPosunZ());
	gule.insert(gule.begin(), tmp);
}

void snake::setWall(GLint w){
	addBody();
	wall = w;
}

void snake::posun(){
	GLfloat pos = cas > 0 ? 0.01f : 0.005f;
	switch (getWall()){
	case 0:
		if (righ){
			posunY += pos;
		}
		if (lef){
			posunY -= pos;
		}
		if (up){
			posunZ += pos;
		}
		if (down){
			posunZ -= pos;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			posunZ = 2.1f;
		}
		if (posunZ <= -2.1f){
			setWall(3);
			posunZ = -2.1f;
			down = false;
			up = true;
		}
		if (posunY >= 2.1f){
			setWall(4);
			posunY = 2.1f;
		}
		if (posunY <= -2.1f){
			setWall(5);
			posunY = -2.1f;
		}
		break;
	case 1:
		if (righ){
			posunY += pos;
		}
		if (lef){
			posunY -= pos;
		}
		if (up){
			posunX -= pos;
		}
		if (down){
			posunX += pos;
		}
		if (posunX <= -2.1f){
			setWall(2);
			posunX = -2.1f;
			up = false;
			down = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
			posunX = 2.1f;
		}
		if (posunY >= 2.1f){
			setWall(4);
			posunY = 2.1f;
			righ = false;
			down = true;
		}
		if (posunY <= -2.1f){
			setWall(5);
			posunY = -2.1f;
			lef = false;
			down = true;
		}
		break;
	case 2:
		if (righ){
			posunY -= pos;
		}
		if (lef){
			posunY += pos;
		}
		if (up){
			posunZ += pos;
		}
		if (down){
			posunZ -= pos;
		}
		if (posunZ <= -2.1f){
			setWall(3);
			posunZ = -2.1f;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			posunZ = 2.1f;
			up = false;
			down = true;
		}
		if (posunY <= -2.1f){
			setWall(5);
			posunY = -2.1f;
		}
		if (posunY >= 2.1f){
			setWall(4);
			posunY = 2.1f;
		}
		break;
	case 3:
		if (righ){
			posunY += pos;
		}
		if (lef){
			posunY -= pos;
		}
		if (up){
			posunX -= pos;
		}
		if (down){
			posunX += pos;
		}
		if (posunX >= 2.1f){
			setWall(0);
			posunX = 2.1f;
			up = true;
			down = false;
		}
		if (posunX <= -2.1f){
			setWall(2);
			posunX = -2.1f;
		}

		/////
		if (posunY <= -2.1f){
			setWall(5);
			posunY = -2.1f;
			lef = false;
			up = true;
		}
		if (posunY >= 2.1f){
			setWall(4);
			posunY = 2.1f;
			righ = false;
			down = true;
		}

		///// po tadeto je nieco zle
		break;
	case 4:
		if (righ){
			posunX -= pos;
		}
		if (lef){
			posunX += pos;
		}
		if (up){
			posunZ += pos;
		}
		if (down){
			posunZ -= pos;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			posunZ = 2.1f;
			up = false;
			lef = true;
		}
		if (posunZ <= -2.1f){
			setWall(1);
			posunZ = -2.1f;
			down = false;
			lef = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
			posunX = 2.1f;
		}
		if (posunX <= -2.1f){
			setWall(2);
			posunX = -2.1f;
		}
		break;
	case 5:
		if (righ){
			posunX += pos;
		}
		if (lef){
			posunX -= pos;
		}
		if (up){
			posunZ += pos;
		}
		if (down){
			posunZ -= pos;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			posunZ = 2.1f;
			up = false;
			righ = true;
		}
		if (posunZ <= -2.1f){
			setWall(3);
			posunZ = -2.1f;
			down = false;
			righ = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
			posunX = 2.1f;
		}
		if (posunX <= -2.1f){
			setWall(2);
			posunX = -2.1f;
		}
		break;
	default:
		break;
	}
	if (telo.size() > 0){
		if (cas > 0){
			size += 0.01f;
			cas -= 0.01f;
		}
		else{
			size += 0.005f;
		}
		Body* last = &(telo.back());
		if (last->size < 0.0f){
			telo.pop_back();
			chvost = gule.back();
			gule.pop_back();
		}
		else{
			if (cas <= 0.0f){
				cas = 0.0f;
				last->size -= 0.005f;
			}
		}
	}
}

void snake::papam(){
	cas += 1.0f;
}


void snake::calculatePoints(){
	float m[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glm::mat4 modelViewMatrix = (glm::make_mat4(m));

	float bod[4] = { hlava->minX, hlava->minY, hlava->minZ, 1 };
	body[0] = modelViewMatrix*make_vec4(bod);

	float bo[4] = { hlava->maxX, hlava->minY, hlava->minZ, 1 };
	body[1] = modelViewMatrix*make_vec4(bo);

	float b[4] = { hlava->minX, hlava->maxY, hlava->minZ, 1 };
	body[2] = modelViewMatrix*make_vec4(b);

	float c[4] = { hlava->minX, hlava->minY, hlava->maxZ, 1 };
	body[3] = modelViewMatrix*make_vec4(c);

	float d[4] = { hlava->maxX, hlava->maxY, hlava->minZ, 1 };
	body[4] = modelViewMatrix*make_vec4(d);

	float e[4] = { hlava->maxX, hlava->minY, hlava->maxZ, 1 };
	body[5] = modelViewMatrix*make_vec4(e);

	float f[4] = { hlava->minX, hlava->maxY, hlava->maxZ, 1 };
	body[6] = modelViewMatrix*make_vec4(f);

	float g[4] = { hlava->maxX, hlava->maxY, hlava->maxZ, 1 };
	body[7] = modelViewMatrix*make_vec4(g);
}

bool snake::narazilsomdoseba(Sphere* gula1, Sphere* gula2, float* m1, float* m2){
	glm::mat4 mat1 = glm::make_mat4(m1);
	glm::mat4 mat2 = glm::make_mat4(m2);

	vec4* s1_body = new vec4[8];

	float bod[4] = { gula1->minX, gula1->minY, gula1->minZ, 1 };
	s1_body[0] = mat1*make_vec4(bod);

	float bo[4] = { gula1->maxX, gula1->minY, gula1->minZ, 1 };
	s1_body[1] = mat1*make_vec4(bo);

	float b[4] = { gula1->minX, gula1->maxY, gula1->minZ, 1 };
	s1_body[2] = mat1*make_vec4(b);

	float c[4] = { gula1->minX, gula1->minY, gula1->maxZ, 1 };
	s1_body[3] = mat1*make_vec4(c);

	float d[4] = { gula1->maxX, gula1->maxY, gula1->minZ, 1 };
	s1_body[4] = mat1*make_vec4(d);

	float e[4] = { gula1->maxX, gula1->minY, gula1->maxZ, 1 };
	s1_body[5] = mat1*make_vec4(e);

	float f[4] = { gula1->minX, gula1->maxY, gula1->maxZ, 1 };
	s1_body[6] = mat1*make_vec4(f);

	float g[4] = { gula1->maxX, gula1->maxY, gula1->maxZ, 1 };
	s1_body[7] = mat1*make_vec4(g);


	vec4* s2_body = new vec4[8];

	float bod1[4] = { gula2->minX, gula2->minY, gula2->minZ, 1 };
	s2_body[0] = mat2*make_vec4(bod1);

	float bo1[4] = { gula2->maxX, gula2->minY, gula2->minZ, 1 };
	s2_body[1] = mat2*make_vec4(bo1);

	float b1[4] = { gula2->minX, gula2->maxY, gula2->minZ, 1 };
	s2_body[2] = mat2*make_vec4(b1);

	float c1[4] = { gula2->minX, gula2->minY, gula2->maxZ, 1 };
	s2_body[3] = mat2*make_vec4(c1);

	float d1[4] = { gula2->maxX, gula2->maxY, gula2->minZ, 1 };
	s2_body[4] = mat2*make_vec4(d1);

	float e1[4] = { gula2->maxX, gula2->minY, gula2->maxZ, 1 };
	s2_body[5] = mat2*make_vec4(e1);

	float f1[4] = { gula2->minX, gula2->maxY, gula2->maxZ, 1 };
	s2_body[6] = mat2*make_vec4(f1);

	float g1[4] = { gula2->maxX, gula2->maxY, gula2->maxZ, 1 };
	s2_body[7] = mat2*make_vec4(g1);

	float minX_s = INT_MAX;
	float minY_s = INT_MAX;
	float minZ_s = INT_MAX;

	float maxX_s = INT_MIN;
	float maxY_s = INT_MIN;
	float maxZ_s = INT_MIN;

	for (int i = 0; i < 8; i++){
		if (s1_body[i].x < minX_s){
			minX_s = s1_body[i].x;
		}
		if (s1_body[i].x  > maxX_s){
			maxX_s = s1_body[i].x;
		}

		if (s1_body[i].y < minY_s){
			minY_s = s1_body[i].y;
		}
		if (s1_body[i].y > maxY_s){
			maxY_s = s1_body[i].y;
		}

		if (s1_body[i].z < minZ_s){
			minZ_s = s1_body[i].z;
		}
		if (s1_body[i].z > maxZ_s){
			maxZ_s = s1_body[i].z;
		}

		if (s2_body[i].x < minX_s){
			minX_s = s2_body[i].x;
		}
		if (s2_body[i].x  > maxX_s){
			maxX_s = s2_body[i].x;
		}

		if (s2_body[i].y < minY_s){
			minY_s = s2_body[i].y;
		}
		if (s2_body[i].y > maxY_s){
			maxY_s = s2_body[i].y;
		}

		if (s2_body[i].z < minZ_s){
			minZ_s = s2_body[i].z;
		}
		if (s2_body[i].z > maxZ_s){
			maxZ_s = s2_body[i].z;
		}
	}


	for (int i = 0; i < 8; i++){
		if ((minX_s <= body[i].x && body[i].x <= maxX_s  &&
			minY_s <= body[i].y && body[i].y <= maxY_s  &&
			minZ_s <= body[i].z && body[i].z <= maxZ_s)){
			return true;
		}
	}
	return false;
}

void snake::render(bool render){
	if (render){
		glPushMatrix();
		glTranslatef(getPosunX(), getPosunY(), getPosunZ());
		glRotatef(rotation_angle, rotation->getX(), rotation->getY(), rotation->getZ());
		glRotatef(secondRotation.second_rotation_angle, secondRotation.second_rotation->getX(), secondRotation.second_rotation->getY(), secondRotation.second_rotation->getZ());
		gluCylinder(quadratic, 0.1f, 0.1f, size, 32, 32);
		glScalef(0.1, 0.1, 0.1);
		hlava->render();
		hlava->renderBoundingBox();
		glPopMatrix();

		for each (Sphere* var in gule){
			glPushMatrix();
			glTranslatef(var->posunX, var->posunY, var->posunZ);
			glScalef(0.1, 0.1, 0.1);
			var->render();
			glPopMatrix();
		}

		for each (Body var in telo){
			glPushMatrix();
			glTranslatef(var.posun->getX(), var.posun->getY(), var.posun->getZ());
			glRotatef(var.rotation_angle, var.rotation->getX(), var.rotation->getY(), var.rotation->getZ());
			glRotatef(var.second_rotation_angle, var.second_rotation->getX(), var.second_rotation->getY(), var.second_rotation->getZ());
			gluCylinder(quadratic, 0.1f, 0.1f, var.size, 32, 32);
			glPopMatrix();
		}

		glPushMatrix();
		if (telo.size() > 0){
			Body* last = &(telo.back());
			switch (last->wall)
			{
			case 0:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 1:
				if (last->up){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->down){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 2:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				break;
			case 3:
				if (last->up){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->down){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 4:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				break;
			case 5:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				break;
			default:
				break;
			}
		}
		else{
			switch (getWall())
			{
			case 0:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 1:
				if (up){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (down){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 2:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				break;
			case 3:
				if (up){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (down){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 4:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				break;
			case 5:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				break;
			default:
				break;
			}
		}
		glScalef(0.1, 0.1, 0.1);
		chvost->render();
		glPopMatrix();
	}
	else{
		float* m1 = new float[16];
		float* m2 = new float[16];
		Sphere* s1 = nullptr;
		calculateRotations();
		//glPushMatrix();
		glLoadIdentity();
		glTranslatef(getPosunX(), getPosunY(), getPosunZ());
		glRotatef(rotation_angle, rotation->getX(), rotation->getY(), rotation->getZ());
		glRotatef(secondRotation.second_rotation_angle, secondRotation.second_rotation->getX(), secondRotation.second_rotation->getY(), secondRotation.second_rotation->getZ());
		glScalef(0.1, 0.1, 0.1);
		calculatePoints();
		//glPopMatrix();

		int i = 0;
		for each (Sphere* var in gule){
			m1 = m2;
			m2 = new float[16];
			s1 = var;
			//glPushMatrix();
			glLoadIdentity();
			glTranslatef(var->posunX, var->posunY, var->posunZ);
			glScalef(0.1, 0.1, 0.1);
			glGetFloatv(GL_MODELVIEW_MATRIX, m2);
			//glPopMatrix();
			i++;
			if (i > 2){
				narazilsomdoseba(s1, s1, m1, m2);
			}
		}
		m1 = m2;
		m2 = new float[16];
		//glPushMatrix();
		glLoadIdentity();
		if (telo.size() > 0){
			Body* last = &(telo.back());
			switch (last->wall)
			{
			case 0:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 1:
				if (last->up){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->down){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 2:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				break;
			case 3:
				if (last->up){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->down){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->lef){
					glTranslatef(last->posun->getX(), last->posun->getY() + last->size, last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX(), last->posun->getY() - last->size, last->posun->getZ());
				}
				break;
			case 4:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				break;
			case 5:
				if (last->up){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() - last->size);
				}
				if (last->down){
					glTranslatef(last->posun->getX(), last->posun->getY(), last->posun->getZ() + last->size);
				}
				if (last->lef){
					glTranslatef(last->posun->getX() + last->size, last->posun->getY(), last->posun->getZ());
				}
				if (last->righ){
					glTranslatef(last->posun->getX() - last->size, last->posun->getY(), last->posun->getZ());
				}
				break;
			default:
				break;
			}
		}
		else{
			switch (getWall())
			{
			case 0:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 1:
				if (up){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (down){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 2:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				break;
			case 3:
				if (up){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (down){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (lef){
					glTranslatef(getPosunX(), getPosunY() + size, getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX(), getPosunY() - size, getPosunZ());
				}
				break;
			case 4:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				break;
			case 5:
				if (up){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() - size);
				}
				if (down){
					glTranslatef(getPosunX(), getPosunY(), getPosunZ() + size);
				}
				if (lef){
					glTranslatef(getPosunX() + size, getPosunY(), getPosunZ());
				}
				if (righ){
					glTranslatef(getPosunX() - size, getPosunY(), getPosunZ());
				}
				break;
			default:
				break;
			}
		}
		glScalef(0.1, 0.1, 0.1);
		glGetFloatv(GL_MODELVIEW_MATRIX, m2);
		if (i > 2){
			narazilsomdoseba(s1, s1, m1, m2);
		}
		//glPopMatrix();
	}
}



snake::~snake()
{
}