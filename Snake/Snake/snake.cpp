#include "snake.h"
#include <iostream>
#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Vector3D.h"

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
	switch (getWall()){
	case 0:
		if (righ){
			posunY += 0.005f;
		}
		if (lef){
			posunY -= 0.005f;
		}
		if (up){
			posunZ += 0.005f;
		}
		if (down){
			posunZ -= 0.005f;
		}
		if (posunZ >= 2.1f){
			setWall(1);
		}
		if (posunZ <= -2.1f){
			setWall(3);
			down = false;
			up = true;
		}
		if (posunY >= 2.1f){
			setWall(4);
		}
		if (posunY <= -2.1f){
			setWall(5);
		}
		break;
	case 1:
		if (righ){
			posunY += 0.005f;
		}
		if (lef){
			posunY -= 0.005f;
		}
		if (up){
			posunX -= 0.005f;
		}
		if (down){
			posunX += 0.005f;
		}
		if (posunX <= -2.1f){
			setWall(2);
			up = false;
			down = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
		}
		if (posunY >= 2.1f){
			setWall(4);
			righ = false;
			down = true;
		}
		if (posunY <= -2.1f){
			setWall(5);
			lef = false;
			down = true;
		}
		break;
	case 2:
		if (righ){
			posunY -= 0.005f;
		}
		if (lef){
			posunY += 0.005f;
		}
		if (up){
			posunZ += 0.005f;
		}
		if (down){
			posunZ -= 0.005f;
		}
		if (posunZ <= -2.1f){
			setWall(3);
		}
		if (posunZ >= 2.1f){
			setWall(1);
			up = false;
			down = true;
		}
		if (posunY <= -2.1f){
			setWall(5);
		}
		if (posunY >= 2.1f){
			setWall(4);
		}
		break;
	case 3:
		if (righ){
			posunY += 0.005f;
		}
		if (lef){
			posunY -= 0.005f;
		}
		if (up){
			posunX -= 0.005f;
		}
		if (down){
			posunX += 0.005f;
		}
		if (posunX >= 2.1f){
			setWall(0);
			up = true;
			down = false;
		}
		if (posunX <= -2.1f){
			setWall(2);
		}

		/////
		if (posunY <= -2.1f){
			setWall(5);
			lef = false;
			up = true;
		}
		if (posunY >= 2.1f){
			setWall(4);
			righ = false;
			down = true;
		}

		///// po tadeto je nieco zle
		break;
	case 4:
		if (righ){
			posunX -= 0.005f;
		}
		if (lef){
			posunX += 0.005f;
		}
		if (up){
			posunZ += 0.005f;
		}
		if (down){
			posunZ -= 0.005f;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			up = false;
			lef = true;
		}
		if (posunZ <= -2.1f){
			setWall(1);
			down = false;
			lef = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
		}
		if (posunX <= -2.1f){
			setWall(2);
		}
		break;
	case 5:
		if (righ){
			posunX += 0.005f;
		}
		if (lef){
			posunX -= 0.005f;
		}
		if (up){
			posunZ += 0.005f;
		}
		if (down){
			posunZ -= 0.005f;
		}
		if (posunZ >= 2.1f){
			setWall(1);
			up = false;
			righ = true;
		}
		if (posunZ <= -2.1f){
			setWall(3);
			down = false;
			righ = true;
		}
		if (posunX >= 2.1f){
			setWall(0);
		}
		if (posunX <= -2.1f){
			setWall(2);
		}
		break;
	default:
		break;
	}
	if (telo.size() > 0){
		size += 0.005;
		Body* last = &(telo.back());
		if (last->size < 0){
			telo.pop_back();
			chvost = gule.back();
			gule.pop_back();
		}
		else{
			last->size -= 0.005f;
		}
	}
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

void snake::render(bool render){
	if (render){
		calculateRotations();
		glPushMatrix();
		glTranslatef(getPosunX(), getPosunY(), getPosunZ());
		glRotatef(rotation_angle, rotation->getX(), rotation->getY(), rotation->getZ());
		glRotatef(secondRotation.second_rotation_angle, secondRotation.second_rotation->getX(), secondRotation.second_rotation->getY(), secondRotation.second_rotation->getZ());
		gluCylinder(quadratic, 0.1f, 0.1f, size, 32, 32);
		glScalef(0.1, 0.1, 0.1);
		calculatePoints();
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
		calculateRotations();
		glPushMatrix();
		glTranslatef(getPosunX(), getPosunY(), getPosunZ());
		glRotatef(rotation_angle, rotation->getX(), rotation->getY(), rotation->getZ());
		glRotatef(secondRotation.second_rotation_angle, secondRotation.second_rotation->getX(), secondRotation.second_rotation->getY(), secondRotation.second_rotation->getZ());
		glScalef(0.1, 0.1, 0.1);
		calculatePoints();
		glPopMatrix();
	}
}



snake::~snake()
{
}