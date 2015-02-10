// fonts.h
// FUNKCIE PRE INICIALIZACIU A VYKRESLOVANIE TEXTOV
#include "Vector3D.h"
// vytvorenie 2D znakov do display listov pomocou WGL
void init2DFontWGL(const char* font_name, int size);

// vytvorenie 3D znakov do display listov pomocou WGL
void init3DFontWGL(const char* font_name);

// nacitanie znakov z .ttf suboru pre renderovanie 2D znakov pomocou FreeType kniznice
void init2DFontFT(const char* font_file);

// renderovanie pripraveneho 2D textu na danu oknovu poziciu pomocou FreeType kniznice
void render2DTextFT(float x, float y, const char *string);

// renderovanie pripraveneho 2D textu na danu oknovu poziciu pomocou WGL kniznice
void render2DTextWGL(float x, float y, const char *string, int size);

// renderovanie 3D textu na danu svetovu poziciu s danou skalou pomocou WGL kniznice
void render3DTextWGL(Vector3D* trans, Vector3D* rotate, float angle, void *font, const char *string);

// renderovanie pripraveneho 2D textu na danu oknovu poziciu pomocou WGL kniznice
void render2DTextGLUT(float x, float y, void *font, const char *string);

// renderovanie 3D textu na danu svetovu poziciu s danou skalou pomocou GLUT kniznice
void render3DTextGLUT(float x, float y, float z, float scale, void *font, const char *string);