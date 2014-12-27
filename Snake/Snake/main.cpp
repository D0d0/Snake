#include <iostream>
#include "shaderLoader.h"
#include "textureLoader.h"
#include "glew.h"
#include "glut-3.7.6-bin/glut.h"
using namespace std;

GLuint tex_skybox;
GLuint shaders_skybox, shaders_envmap;
GLdouble vzd, old_vzd, fi, xi, old_fi, old_xi;
GLint left_mouse_down_x, left_mouse_down_y;
GLint right_mouse_down_y;
GLboolean right_down = false, left_down = false;

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
	//glOrtho(-10.0f*ratio, 10.0f*ratio, -10.0f, 10.0f, 1.0, 5000.0); 
}

void render(){
	// Vymaz (vypln) obrazovku a z-buffer definovanymi hodnotami
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

	// Nastav modelview maticu (transformaciu) na jednotkovu maticu
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Nastav view matice pre pohlad na svetovy suradnicovy system
	GLfloat camera_pos[4];
	camera_pos[0] = vzd*cos(fi)*cos(xi);
	camera_pos[1] = vzd*sin(fi)*cos(xi);
	camera_pos[2] = vzd*sin(xi);
	camera_pos[3] = 1;
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
	glUseProgram(shaders_skybox);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, tex_skybox);
	glPushMatrix();
	glScalef(500, 500, 500);
	//renderCubeVBO();
	glPopMatrix();
	glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
	glUseProgram(0);
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
		glutPostRedisplay();
	}

	if (right_down == true){
		vzd = old_vzd + (right_mouse_down_y - y) / 10.0f;
		glutPostRedisplay();
	}

}

int main(int argc, char** argv){
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
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	// Nastavime zakladne vlastnosti OpenGL
	/*init();
	initSphereVBO(32, 32);
	initTorusVBO(0.6f, 2.0f, 32, 32);
	initTextures();
	initShaders();
	init2DFontFT("fonts/planetbe.ttf");

	// Zaregistrujeme callback funkcie
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	glutTimerFunc(0, timer, 0);
	*/
	textureLoader* tl = new textureLoader();
	tex_skybox = tl->LoadCubeTexture("skybox/snow_positive_x.jpg", "skybox/snow_negative_x.jpg",
		"skybox/snow_positive_y.jpg", "skybox/snow_negative_y.jpg",
		"skybox/snow_positive_z.jpg", "skybox/snow_negative_z.jpg");
	shaderLoader* sl = new shaderLoader();
	shaders_skybox = sl->loadProgram("shaders/skybox.vert", "shaders/skybox.frag");
	sl->SetShaderUniform1i(shaders_skybox, "cube_map", 0);

	shaders_envmap = sl->loadProgram("shaders/perpixel_envmap.vert", "shaders/perpixel_envmap.frag");
	sl->SetShaderUniform1i(shaders_envmap, "color_texture", 0);
	sl->SetShaderUniform1i(shaders_envmap, "cubemap_texture", 1);
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	// Spustenie hlavneho okruhu zachytavania sprav
	glutMainLoop();
	return 0;
}