#define _USE_MATH_DEFINES
#include <stdio.h>
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
#include "Sphere.h"
#include "snake.h"
#include <vector>
#include "glm\glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "glm/gtx/string_cast.hpp"
#include "Level.h"
#include <string>

using namespace Assimp;
using namespace std;

int timer_id = 0;
bool paused = false;
bool koniec = false;
GLuint shaders_envmap, shaders_perpixel_phong, shaders_pervertex_phong, tex_point_sprite;
GLboolean fog_enabled = false;
GLint uroven = 10;
GLint selected_menu = 0;
GLint selected_menu_nastavenia = 0;
GLuint g_window_height, g_window_width;
GLdouble vzd, old_vzd, fi, xi, old_fi, old_xi;
GLint left_mouse_down_x, left_mouse_down_y;
GLint right_mouse_down_y;
GLboolean right_down = false, left_down = false, menu = true, nastavenia = false;
skybox* sky;
world* wor;
snake* sn;
GLboolean isWired = false;
Sphere* slnko;
Level* lvl;
ofstream logFile;
GLfloat old_camera_pos[4];

void reshape(int w, int h){
	g_window_width = w;
	g_window_height = h;
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

	glEnable(GL_MULTISAMPLE);
	if (isWired){
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else{
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	if (menu){
		glEnable(GL_LIGHTING);
		glColor3f(1.0f, 1.0f, 0.0f);
		render2DTextWGL((g_window_width - 175) / 2, g_window_height - 50, "Snake 3D", -40);
		if (nastavenia){
			if (selected_menu_nastavenia == 0){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			string uroven_string = "";
			switch (uroven)
			{
			case 15:
				uroven_string = "<    Easy    >";
				break;
			case 10:
				uroven_string = "<  Medium  >";
				break;
			case 5:
				uroven_string = "<    Hard    >";
				break;
			default:
				break;
			}
			render2DTextWGL((g_window_width - 130) / 2, g_window_height - 200, uroven_string.c_str(), -24);
			if (selected_menu_nastavenia == 1){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			render2DTextWGL((g_window_width - 40) / 2, g_window_height - 230, "Back", -24);
		}
		else{
			if (selected_menu == 0){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			render2DTextWGL((g_window_width - 110) / 2, g_window_height - 200, "New game", -24);
			if (selected_menu == 1){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			render2DTextWGL((g_window_width - 80) / 2, g_window_height - 230, "Options", -24);
			if (selected_menu == 2){
				glColor3f(1.0f, 0.0f, 0.0f);
			}
			else{
				glColor3f(1.0f, 1.0f, 0.0f);
			}
			render2DTextWGL((g_window_width - 50) / 2, g_window_height - 260, "Quit", -24);
		}
		glDisable(GL_LIGHTING);
	}
	else{
		// Nastav modelview maticu (transformaciu) na jednotkovu maticu
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		shaderLoader* sl = new shaderLoader();

		sn->render(false);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();

		lvl->render(false);

		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		// Nastav view matice pre pohlad na svetovy suradnicovy system
		GLfloat camera_pos[4];
		camera_pos[0] = vzd*cos(fi)*cos(xi);
		camera_pos[1] = vzd*sin(fi)*cos(xi);
		camera_pos[2] = vzd*sin(xi);
		camera_pos[3] = 1;
		/*if (camera_pos[1] > 0 && old_camera_pos[1] < 0 || camera_pos[1] < 0 && old_camera_pos[1] > 0){
			camera_pos[1] = old_camera_pos[1];
		}
		old_camera_pos[0]= camera_pos[0];
		old_camera_pos[1] = camera_pos[1];
		old_camera_pos[2] = camera_pos[2];
		old_camera_pos[3] = camera_pos[3];*/
		cout << camera_pos[0] << endl;
		cout << camera_pos[1] << endl;
		cout << camera_pos[2] << endl;
		float view_matrix[16];

		gluLookAt(camera_pos[0], camera_pos[1], camera_pos[2], 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);
		glGetFloatv(GL_MODELVIEW_MATRIX, view_matrix);
		sl->SetShaderUniformMatrix4f(shaders_envmap, "view_matrix", view_matrix);

		// vykresli suradnicove osi svetoveho systemu roznymi farbami
		/*glLineWidth(1);
		glBegin(GL_LINES);
		glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(100.0f, 0.0f, 0.0f);
		glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 100.0f, 0.0f);
		glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 100.0f);
		glEnd();*/
		// vykresli skybox
		// skybox je dany vo svetovych suradniciach, akurat jeho stred je stale v bode, kdeje kamera
		sky->render();
		render3DTextGLUT(1.9, 0, 0, 0.004, GLUT_STROKE_ROMAN, "EASTER EGG");

		wor->render();

		glPushMatrix();
		glEnable(GL_LIGHT0);
		glUseProgram(shaders_perpixel_phong);
		GLfloat sun_position[] = { 10.0f, 10.0f, 10.0f, 0.0f };
		glLightfv(GL_LIGHT0, GL_POSITION, sun_position);

		glUseProgram(shaders_pervertex_phong);
		GLint tex_enabled = glGetUniformLocation(shaders_pervertex_phong, "texturing_enabled");
		sl->SetShaderUniform1i(shaders_envmap, "texturing_enabled", 1);
		glUniform1i(tex_enabled, 0);
		glColor3f(1, 0, 0);

		glPopMatrix();
		sn->render(true);
		glUseProgram(0);
		glColor3f(1, 1, 1);

		glDisable(GL_LIGHT0);
		glEnable(GL_TEXTURE_2D);
		lvl->render(true);
		koniec = lvl->koniec();
		glColor3f(1, 0, 0);
		if (koniec){
			timer_id++;
			render2DTextWGL((g_window_width - 300) / 2, (g_window_height - 30) / 2, "GAME OVER!", -50);
			render2DTextWGL((g_window_width - 150) / 2, (g_window_height - 100) / 2, ("Points: " + std::to_string(lvl->points)).c_str(), -35);
		}
		else{
			render2DTextWGL(g_window_width - 150, g_window_height - 30, ("Points: " + std::to_string(lvl->points)).c_str(), -24);
		}
		glColor3f(0, 0, 1);
	}
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


	GLfloat light_ambient[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat light_diffuse[] = { 0.9f, 0.9f, 0.9f, 1.0f };
	GLfloat light_specular[] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT0, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT0);
	/*
	glLightfv(GL_LIGHT1, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT1, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT1, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT1, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT1);

	glLightfv(GL_LIGHT3, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT3, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT3, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT3, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT3);

	glLightfv(GL_LIGHT2, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT2, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT2, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT2, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT2);

	glLightfv(GL_LIGHT4, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT4, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT4, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT4, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT4);

	glLightfv(GL_LIGHT5, GL_AMBIENT, light_ambient);
	glLightfv(GL_LIGHT5, GL_DIFFUSE, light_diffuse);
	glLightfv(GL_LIGHT5, GL_SPECULAR, light_specular);
	glLightf(GL_LIGHT5, GL_CONSTANT_ATTENUATION, 1.0);
	glEnable(GL_LIGHT5);

	*/


	// parametre hmly
	glFogi(GL_FOG_MODE, GL_EXP2);
	GLfloat fogColor[4] = { 0.5f, 0.5f, 0.5f, 1.0f };
	glFogfv(GL_FOG_COLOR, fogColor);
	glFogf(GL_FOG_DENSITY, 0.1f);
	glHint(GL_FOG_HINT, GL_DONT_CARE);
	glFogf(GL_FOG_START, 3.0f);
	glFogf(GL_FOG_END, 20.0f);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	return true;
}


// Procedura obsluhujuca stlacenie tlacitka mysi
void mouse_klik(int button, int state, int x, int y){
	if (!menu){
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
	}
	glutPostRedisplay();
}

void mouse_move(int x, int y){
	if (!menu){
		if (left_down == true){
			fi = old_fi + (left_mouse_down_x - x) / 200.0f;
			xi = old_xi + (y - left_mouse_down_y) / 200.0f;
			/*cout << "fi " << fi << endl;
			cout << "xi " << xi << endl;*/
			glutPostRedisplay();
		}

		if (right_down == true){
			if (old_vzd + (right_mouse_down_y - y) / 10.0f > 6.5f){
				vzd = old_vzd + (right_mouse_down_y - y) / 10.0f;
				glutPostRedisplay();
			}
			//cout << "vzd" << vzd << endl;
		}
	}
}

void timer(int a){
	if (a + 1 == timer_id && !koniec){
		sn->posun();
		lvl->rotate();
		glutPostRedisplay();
		glutTimerFunc(uroven, timer, a);
	}
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 13:
		if (menu){
			if (nastavenia){
				if (selected_menu_nastavenia == 1){
					nastavenia = false;
				}
			}
			else{
				switch (selected_menu)
				{
				case 0:
					menu = false;
					koniec = false;
					sn = new snake();
					lvl->init(uroven, sn);
					glutTimerFunc(uroven, timer, timer_id++);
					break;
				case 1:
					selected_menu_nastavenia = 0;
					nastavenia = true;
					break;
				case 2:
					exit(0);
					break;
				default:
					break;
				}
			}
		}
		break;
	case 27:
		if (menu && nastavenia){
			nastavenia = false;
		}
		else{
			menu = true;
		}
		break;
	case 'w':
		isWired = !isWired;
		break;
	case 'f':
		fog_enabled = !fog_enabled;
		if (fog_enabled){
			glEnable(GL_FOG);
		}
		else{
			glDisable(GL_FOG);
		}
		break;
	default:
		break;
	}
	glutPostRedisplay();
}

void special_keys(int a_keys, int x, int y){
	if (menu){
		switch (a_keys)
		{
		case GLUT_KEY_UP:
			if (nastavenia){
				if (selected_menu_nastavenia - 1 < 0){
					selected_menu_nastavenia = 1;
				}
				else{
					selected_menu_nastavenia = (selected_menu_nastavenia - 1) % 2;
				}
			}
			else{
				if (selected_menu - 1 < 0){
					selected_menu = 2;
				}
				else{
					selected_menu = (selected_menu - 1) % 3;
				}
			}
			break;
		case GLUT_KEY_DOWN:
			if (nastavenia){
				selected_menu_nastavenia = (selected_menu_nastavenia + 1) % 2;
			}
			else{
				selected_menu = (selected_menu + 1) % 3;
			}
			break;
		case GLUT_KEY_LEFT:
			if (nastavenia && selected_menu_nastavenia == 0){
				switch (uroven)
				{
				case 5:
					uroven = 15;
					break;
				case 10:
					uroven = 5;
					break;
				case 15:
					uroven = 10;
					break;
				default:
					break;
				}
			}
			break;
		case GLUT_KEY_RIGHT:
			if (nastavenia && selected_menu_nastavenia == 0){
				switch (uroven)
				{
				case 5:
					uroven = 10;
					break;
				case 10:
					uroven = 15;
					break;
				case 15:
					uroven = 5;
					break;
				default:
					break;
				}
			}
			break;
		default:
			break;
		}
	}
	else{
		sn->setDirection(a_keys);
	}
	glutPostRedisplay();
}


int main(int argc, char** argv){
	logFile.open("test.txt");
	// GLUT Inicializacia
	glutInit(&argc, argv);
	// Display Mod (Rgb a Double Buffering)
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_MULTISAMPLE);
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
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	//glutTimerFunc(10, timer, 0);
	sky = new skybox();
	wor = new world();
	lvl = new Level();
	shaderLoader* sl = new shaderLoader();
	shaders_envmap = sl->loadProgram("shaders/perpixel_envmap.vert", "shaders/perpixel_envmap.frag");

	sl->SetShaderUniform1i(shaders_envmap, "color_texture", 0);
	sl->SetShaderUniform1i(shaders_envmap, "cubemap_texture", 1);

	shaders_pervertex_phong = sl->loadProgram("shaders/pervertex_phong.vert", "shaders/pervertex_phong.frag");
	int locationTexture = glGetUniformLocation(shaders_pervertex_phong, "color_texture");
	glUniform1i(locationTexture, 0);

	shaders_perpixel_phong = sl->loadProgram("shaders/perpixel_phong.vert", "shaders/perpixel_phong.frag");
	sl->SetShaderUniform1i(shaders_perpixel_phong, "color_texture", 0);

	textureLoader* tl = new textureLoader();
	tex_point_sprite = tl->LoadTexture("textures/particle.png");
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);

	// Spustenie hlavneho okruhu zachytavania sprav
	glutMainLoop();
	logFile.close();
	return 0;
}