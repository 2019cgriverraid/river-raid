#include <GL/glut.h>

struct Coordenadas {
  GLfloat panX;
  GLfloat panY;
};

struct Objeto {
  GLfloat posX;
  GLfloat posY;
  int id;
  int tipo;
};