#include <GL/glut.h>
#include <math.h>

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

float dist(GLfloat px, GLfloat py, GLfloat qx, GLfloat qy){
    printf("px %2f qx %2f py %2f qy %2f \n", px, qx, py, qy);
    return sqrt(pow((px - qx), 2) + pow((py - qy), 2));
}