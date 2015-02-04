#define _USE_MATH_DEFINES
#include <iostream>
#include <sstream>
#include <fstream>
#include "shaderLoader.h"
#include "textureLoader.h"
#include "skybox.h"
#include "world.h"
#include "glew.h"
#include "glut-3.7.6-bin/glut.h"
#include "fonts.h"
#include "il.h"
#include <math.h>
#include "assimp/Importer.hpp"
#include "assimp/scene.h"           
#include "assimp/postprocess.h"
#include "Model.h"
#include "ObjectLoader.h"
#include "Sphere.h"
#include "snake.h"
#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"

using namespace Assimp;
using namespace std;

GLuint  shaders_envmap;
GLdouble vzd, old_vzd, fi, xi, old_fi, old_xi;
GLint left_mouse_down_x, left_mouse_down_y;
GLint right_mouse_down_y;
GLboolean right_down = false, left_down = false;
GLboolean up = true;
GLboolean down = false;
GLboolean righ = false;
GLboolean lef = false;
skybox* sky;
world* wor;
Model obj;
snake* sn;
GLboolean isWired = false;


ofstream logFile;
void reshape(int w, int h){

	// nastvenie casti okna pre vykreslenie, tentoraz kreslime do celeho okna
	glViewport(0, 0, w, h);
	// Budeme menit projekcnu maticu (transformaciu)
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	if (h == 0){
		h = 1;
	}
	// Chceme perspektivnu projekciu
	float ratio = (float)w / (float)h;
	gluPerspective(60, ratio, 0.1, 1000.0);
}


void render(){
	// Vymaz (vypln) obrazovku a z-buffer definovanymi hodnotami
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if (isWired){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	// Nastav modelview maticu (transformaciu) na jednotkovu maticu
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Nastav view matice pre pohlad na svetovy suradnicovy system
	GLfloat camera_pos[4];
	camera_pos[0] = vzd*cos(fi)*cos(xi);
	camera_pos[1] = vzd*sin(fi)*cos(xi);
	camera_pos[2] = vzd*sin(xi);
	camera_pos[3] = 1;
	//	if (camera_pos[1] < 0.3f){
	//		camera_pos[1] = 0.3f;
	//	}
	gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
	float view_matrix[16];
	glGetFloatv(GL_MODELVIEW_MATRIX, view_matrix);

	shaderLoader* sl = new shaderLoader();
	sl->SetShaderUniformMatrix4f(shaders_envmap, "view_matrix", view_matrix);
	// vykresli suradnicove osi svetoveho systemu roznymi farbami
	glLineWidth(1);
	glBegin(GL_LINES);
	glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(100.0f, 0.0f, 0.0f);
	glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 100.0f, 0.0f);
	glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 100.0f);
	glEnd();
	// vykresli skybox
	// skybox je dany vo svetovych suradniciach, akurat jeho stred je stale v bode, kdeje kamera
	sky->render();
	//vykresli kocku
	wor->render();
	glPushMatrix();
	glScalef(0.1f, 0.1f, 0.1f);
	glRotatef(90, 1.0f, 0, 0);
	glTranslatef(0, 2.1f, 0);
	glPopMatrix();
	render2DTextFT(10, 45, "F1 - zapni/vypni animaciu");
	render3DTextGLUT(6, 0, 2, 0.01, GLUT_STROKE_ROMAN, "Projekt OpenGL - GLUT 3D text");

	sn->render();

	glColor3f(1, 1, 1);

	glPushMatrix();
	glTranslatef(-2, 0, 0);
	glRotatef(90, 0, 0, 1);
	//glScalef(0.005, 0.005, 0.005);
	obj.render();
	obj.renderBoundingBox();

	glPopMatrix();


	logFile << obj.getCollision(sn->bod1.x, sn->bod1.y, sn->bod1.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod1.x << " " << sn->bod1.y << " " << sn->bod1.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod2.x, sn->bod2.y, sn->bod2.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod2.x << " " << sn->bod2.y << " " << sn->bod2.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod3.x, sn->bod3.y, sn->bod3.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod3.x << " " << sn->bod3.y << " " << sn->bod3.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod4.x, sn->bod4.y, sn->bod4.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod4.x << " " << sn->bod4.y << " " << sn->bod4.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;



	logFile << obj.getCollision(sn->bod5.x, sn->bod5.y, sn->bod5.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod5.x << " " << sn->bod5.y << " " << sn->bod5.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod6.x, sn->bod6.y, sn->bod6.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod6.x << " " << sn->bod6.y << " " << sn->bod6.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod7.x, sn->bod7.y, sn->bod7.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod7.x << " " << sn->bod7.y << " " << sn->bod7.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;

	logFile << obj.getCollision(sn->bod8.x, sn->bod8.y, sn->bod8.z) << " " << endl;
	logFile << obj.bod1.x << " " << obj.bod1.y << " " << obj.bod1.z << endl;
	logFile << sn->bod8.x << " " << sn->bod8.y << " " << sn->bod8.z << endl;
	logFile << obj.bod8.x << " " << obj.bod8.y << " " << obj.bod8.z << endl;
	logFile << "------------------------------------------------" << endl;




	glutSwapBuffers();
}


bool init(void)
{
	// Cierne pozadie
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	// Nastav z-buffer testovanie
	glClearDepth(1.0f);
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);

	// nastav stencil buffer
	glClearStencil(0);

	// nastav zmiesavaciu funkciu
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	// nastav vhodne mapovanie textur
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	// initializuj kameru
	fi = 0.7f; xi = 0.7f; vzd = 10.0f;

	// initializuje svetlo
	GLfloat light_ambient[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	GLfloat light_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT0);

	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// parametre hmly
	glFogi(GL_FOG_MODE, GL_EXP2);
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.1f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 3.0f);
	glFogf(GL_FOG_END, 20.0f);
	//glEnable(GL_FOG);
	return true;
}

// Procedura obsluhujuca stlacenie tlacitka mysi
void mouse_klik(int button, int state, int x, int y){
	switch (button){
	case GLUT_LEFT_BUTTON:
		if (state == GLUT_DOWN){
			left_down = true;
			left_mouse_down_x = x;
			left_mouse_down_y = y;
			old_fi = fi;
			old_xi = xi;
		}
		else if (state == GLUT_UP){
			left_down = false;
		}
		break;
	case GLUT_RIGHT_BUTTON:
		if (state == GLUT_DOWN){
			right_down = true;
			right_mouse_down_y = y;
			old_vzd = vzd;
		}
		else if (state == GLUT_UP){
			right_down = false;
		}
		break;
	default:
		break;
	}

	glutPostRedisplay();
}

void mouse_move(int x, int y){
	if (left_down == true){
		fi = old_fi + (left_mouse_down_x - x) / 200.0f;
		xi = old_xi + (y - left_mouse_down_y) / 200.0f;
		cout << "fi " << fi << endl;
		cout << "xi " << xi << endl;
		glutPostRedisplay();
	}

	if (right_down == true){
		if (old_vzd + (right_mouse_down_y - y) / 10.0f > 6.5f){
			vzd = old_vzd + (right_mouse_down_y - y) / 10.0f;
			glutPostRedisplay();
		}
		cout << "vzd" << vzd << endl;
	}

}

void timer(int a){
	//cout << sn->getWall() << endl;
	switch (sn->getWall()){
	case 0:
		if (righ){
			sn->posunY += 0.005f;
		}
		if (lef){
			sn->posunY -= 0.005f;
		}
		if (up){
			sn->posunZ += 0.005f;
		}
		if (down){
			sn->posunZ -= 0.005f;
		}
		if (sn->posunZ >= 2.1f){
			sn->setWall(1);
		}
		if (sn->posunZ <= -2.1f){
			sn->setWall(3);
			down = false;
			up = true;
		}
		if (sn->posunY >= 2.1f){
			sn->setWall(4);
		}
		if (sn->posunY <= -2.1f){
			sn->setWall(5);
		}
		break;
	case 1:
		if (righ){
			sn->posunY += 0.005f;
		}
		if (lef){
			sn->posunY -= 0.005f;
		}
		if (up){
			sn->posunX -= 0.005f;
		}
		if (down){
			sn->posunX += 0.005f;
		}
		if (sn->posunX <= -2.1f){
			sn->setWall(2);
			up = false;
			down = true;
		}
		if (sn->posunX >= 2.1f){
			sn->setWall(0);
		}
		if (sn->posunY >= 2.1f){
			sn->setWall(4);
			righ = false;
			down = true;
		}
		if (sn->posunY <= -2.1f){
			sn->setWall(5);
			lef = false;
			down = true;
		}
		break;
	case 2:
		if (righ){
			sn->posunY -= 0.005f;
		}
		if (lef){
			sn->posunY += 0.005f;
		}
		if (up){
			sn->posunZ += 0.005f;
		}
		if (down){
			sn->posunZ -= 0.005f;
		}
		if (sn->posunZ <= -2.1f){
			sn->setWall(3);
		}
		if (sn->posunZ >= 2.1f){
			sn->setWall(1);
			up = false;
			down = true;
		}
		if (sn->posunY <= -2.1f){
			sn->setWall(5);
		}
		if (sn->posunY >= 2.1f){
			sn->setWall(4);
		}
		break;
	case 3:
		if (righ){
			sn->posunY += 0.005f;
		}
		if (lef){
			sn->posunY -= 0.005f;
		}
		if (up){
			sn->posunX -= 0.005f;
		}
		if (down){
			sn->posunX += 0.005f;
		}
		if (sn->posunX >= 2.1f){
			sn->setWall(0);
			up = true;
			down = false;
		}
		if (sn->posunX <= -2.1f){
			sn->setWall(2);
		}

		/////
		if (sn->posunY <= -2.1f){
			sn->setWall(5);
			lef = false;
			up = true;
		}
		if (sn->posunY >= 2.1f){
			sn->setWall(4);
			righ = false;
			down = true;
		}

		///// po tadeto je nieco zle
		break;
	case 4:
		if (righ){
			sn->posunX -= 0.005f;
		}
		if (lef){
			sn->posunX += 0.005f;
		}
		if (up){
			sn->posunZ += 0.005f;
		}
		if (down){
			sn->posunZ -= 0.005f;
		}
		if (sn->posunZ >= 2.1f){
			sn->setWall(1);
			up = false;
			lef = true;
		}
		if (sn->posunZ <= -2.1f){
			sn->setWall(1);
			down = false;
			lef = true;
		}
		if (sn->posunX >= 2.1f){
			sn->setWall(0);
		}
		if (sn->posunX <= -2.1f){
			sn->setWall(2);
		}
		break;
	case 5:
		if (righ){
			sn->posunX += 0.005f;
		}
		if (lef){
			sn->posunX -= 0.005f;
		}
		if (up){
			sn->posunZ += 0.005f;
		}
		if (down){
			sn->posunZ -= 0.005f;
		}
		if (sn->posunZ >= 2.1f){
			sn->setWall(1);
			up = false;
			righ = true;
		}
		if (sn->posunZ <= -2.1f){
			sn->setWall(3);
			down = false;
			righ = true;
		}
		if (sn->posunX >= 2.1f){
			sn->setWall(0);
		}
		if (sn->posunX <= -2.1f){
			sn->setWall(2);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
	glutTimerFunc(10, timer, a);
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 27:
		exit(0);
		break;
	case 'w':
		isWired = !isWired;
	default:
		break;
	}
}

void special_keys(int a_keys, int x, int y){
	//sn->addSphere();
	switch (a_keys){
	case GLUT_KEY_DOWN:
		if (up){
			return;
		}
		up = false;
		righ = false;
		down = true;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		if (down){
			return;
		}
		up = true;
		righ = false;
		down = false;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		if (righ){
			return;
		}
		up = false;
		righ = false;
		down = false;
		lef = true;
		break;
	case GLUT_KEY_RIGHT:
		if (lef){
			return;
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


int main(int argc, char** argv){
	logFile.open("test.txt");
	// GLUT Inicializacia
	glutInit(&argc, argv);
	// Display Mod (Rgb a Double Buffering)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL);
	//glutInitDisplayString("stencil>=8 rgb>=8 double depth>=24");
	// Nastavime pociatocnu poziciu a velkost okna
	glutInitWindowPosition(50, 50);
	glutInitWindowSize(800, 600);
	// Vyrobime okno s danym menom
	glutCreateWindow("--== OpenGL projekt ==--");

	// Zinicializujeme GLEW
	glewInit();
	init();
	ilInit();
	sn = new snake();
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	glutTimerFunc(10, timer, 0);
	ObjectLoader loader = ObjectLoader();
	sky = new skybox();
	wor = new world();
	//loader.loadModel("hulk/hulk.obj");
	//loader.loadModel("mountain/Mountain Dew Code Red soda can.obj");
	loader.loadModel("apple/app.obj");
	obj = loader.getModel();
	shaderLoader* sl = new shaderLoader();
	shaders_envmap = sl->loadProgram("shaders/perpixel_envmap.vert", "shaders/perpixel_envmap.frag");
	sl->SetShaderUniform1i(shaders_envmap, "color_texture", 0);
	sl->SetShaderUniform1i(shaders_envmap, "cubemap_texture", 1);

	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	//worldObject* obj = new worldObject();
	/*const aiScene* scene;
	Importer importer;
	cout << "Loading objects..." << endl;
	string fileName = "plane/Boeing747.obj";
	ifstream inFile(fileName.c_str());
	bool a = inFile.fail() == false;

	scene = importer.ReadFile(fileName, aiProcess_Triangulate);

	if (!scene){
	cout << "Scene not loaded, beacuse: " << importer.GetErrorString() << endl;
	//return false;
	}*/


	// Spustenie hlavneho okruhu zachytavania sprav
	glutMainLoop();
	logFile.close();
	return 0;
}