#define _USE_MATH_DEFINES
#include <iostream>
#include "shaderLoader.h"
#include "textureLoader.h"
#include "worldObject.h"
#include "skybox.h"
#include "world.h"
#include "glew.h"
#include "glut-3.7.6-bin/glut.h"
#include "fonts.h"
//#include "fonts.h"
#include <math.h>
using namespace std;

GLuint  shaders_envmap;
GLdouble vzd, old_vzd, fi, xi, old_fi, old_xi;
GLint left_mouse_down_x, left_mouse_down_y;
GLint right_mouse_down_y;
GLboolean right_down = false, left_down = false;
GLfloat posunX = 0.0f;
GLfloat posunY = 0.0f;
GLfloat posunZ = 0.0f;
GLboolean up = true;
GLboolean down = false;
GLboolean righ = false;
GLboolean lef = false;
skybox* sky;
world* wor;


GLfloat size = 1.0f;
// id VBO
GLuint g_uiVBOSphereCoords, g_uiVBOSphereTexCoords, g_uiVBOSphereNormals, g_uiVBOSphereIndices;
GLuint g_uiSphereNumIndices;

void renderSphereVBO(){
	glScalef(0.1, 0.1, 0.1);
	glTranslatef(0, 0, 0);
	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereCoords);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_TEXTURE_COORD_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereTexCoords);
	glTexCoordPointer(2, GL_FLOAT, 0, NULL);

	glEnableClientState(GL_NORMAL_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereNormals);
	glNormalPointer(GL_FLOAT, 0, NULL);

	// draw a cube using buffer with indices
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOSphereIndices);
	glDrawElements(GL_QUADS, g_uiSphereNumIndices, GL_UNSIGNED_INT, NULL);

	// deactivate vertex arrays after drawing
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

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

	render2DTextFT(10, 45, "F1 - zapni/vypni animaciu");
	render3DTextGLUT(6, 0, 2, 0.01, GLUT_STROKE_ROMAN, "Projekt OpenGL - GLUT 3D text");

	glTranslatef(0, posunY, posunZ);
	GLUquadricObj *quadratic;
	quadratic = gluNewQuadric();
	glTranslatef(2.1, 0, 0);
	glRotatef(0, 0.0f, 1.0f, 0.0f);
	gluCylinder(quadratic, 0.1f, 0.1f, size, 32, 32);

	renderSphereVBO();
	glutSwapBuffers();
}

void initSphereVBO(int xSlices, int ySlices)
{
	float* vertices = new float[3 * (xSlices + 1) * (ySlices + 1)];
	float* normals = new float[3 * (xSlices + 1) * (ySlices + 1)];
	float* texcoords = new float[2 * (xSlices + 1) * (ySlices + 1)];

	for (int i = 0; i <= xSlices; i++)
	{
		float u = i / float(xSlices);
		for (int j = 0; j <= ySlices; j++)
		{
			float v = j / float(ySlices);

			int index = i + j * (xSlices + 1);

			vertices[3 * index + 0] = cos(2 * u * M_PI) * cos((v - 0.5f) * M_PI);
			vertices[3 * index + 1] = sin(2 * u * M_PI) * cos((v - 0.5f) * M_PI);
			vertices[3 * index + 2] = sin((v - 0.5f) * M_PI);

			normals[3 * index + 0] = vertices[3 * index + 0];
			normals[3 * index + 1] = vertices[3 * index + 1];
			normals[3 * index + 2] = vertices[3 * index + 2];

			texcoords[2 * index + 0] = u;
			texcoords[2 * index + 1] = 1.0f - v;
		}
	}

	GLuint* indices = new GLuint[4 * xSlices * ySlices];
	int index = 0;
	for (int i = 0; i < xSlices; i++)
	{
		for (int j = 0; j < ySlices; j++)
		{
			indices[index++] = i + j * (xSlices + 1);
			indices[index++] = (i + 1) + j * (xSlices + 1);
			indices[index++] = (i + 1) + (j + 1) * (xSlices + 1);
			indices[index++] = i + (j + 1) * (xSlices + 1);
		}
	}

	glGenBuffers(1, &g_uiVBOSphereCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereCoords);
	glBufferData(GL_ARRAY_BUFFER, 3 * (xSlices + 1) * (ySlices + 1) * sizeof(float), vertices, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereNormals);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereNormals);
	glBufferData(GL_ARRAY_BUFFER, 3 * (xSlices + 1) * (ySlices + 1) * sizeof(float), normals, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereTexCoords);
	glBindBuffer(GL_ARRAY_BUFFER, g_uiVBOSphereTexCoords);
	glBufferData(GL_ARRAY_BUFFER, 2 * (xSlices + 1) * (ySlices + 1) * sizeof(float), texcoords, GL_STATIC_DRAW);

	glGenBuffers(1, &g_uiVBOSphereIndices);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, g_uiVBOSphereIndices);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * (xSlices + 0) * (ySlices + 0) * sizeof(GLuint), indices, GL_STATIC_DRAW);

	g_uiSphereNumIndices = 4 * (xSlices + 0) * (ySlices + 0);

	delete[] vertices;
	delete[] normals;
	delete[] texcoords;
	delete[] indices;
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
	glEnable(GL_FOG);

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
	//size += 0.01f;
	glutPostRedisplay();
	glutTimerFunc(10, timer, a);
}

void keyboard(unsigned char key, int x, int y){
	switch (key){
	case 27:
		exit(0);
		break;
	default:
		break;
	}
}

void special_keys(int a_keys, int x, int y){
	switch (a_keys){
	case GLUT_KEY_DOWN:
		up = false;
		righ = false;
		down = true;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_UP:
		up = true;
		righ = false;
		down = false;
		lef = false;
		glutPostRedisplay();
		break;
	case GLUT_KEY_LEFT:
		up = false;
		righ = false;
		down = false;
		lef = true;
		break;
	case GLUT_KEY_RIGHT:
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
	initSphereVBO(500, 500);
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	// Nastavime zakladne vlastnosti OpenGL
	/*initTorusVBO(0.6f, 2.0f, 32, 32);
	initTextures();
	initShaders();
	init2DFontFT("fonts/planetbe.ttf");

	// Zaregistrujeme callback funkcie
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	glutSpecialFunc(special_keys);
	glutMouseFunc(mouse_klik);
	glutMotionFunc(mouse_move);
	glutTimerFunc(0, timer, 0);
	*/
	glutKeyboardFunc(keyboard);
	glutSpecialFunc(special_keys);
	glutTimerFunc(10, timer, 0);
	sky = new skybox();
	wor = new world();
	shaderLoader* sl = new shaderLoader();
	shaders_envmap = sl->loadProgram("shaders/perpixel_envmap.vert", "shaders/perpixel_envmap.frag");
	sl->SetShaderUniform1i(shaders_envmap, "color_texture", 0);
	sl->SetShaderUniform1i(shaders_envmap, "cubemap_texture", 1);
	glutDisplayFunc(render);
	glutReshapeFunc(reshape);
	worldObject* obj = new worldObject();
	// Spustenie hlavneho okruhu zachytavania sprav
	glutMainLoop();
	return 0;
}