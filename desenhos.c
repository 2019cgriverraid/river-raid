#include <GL/glut.h>

void desenharAeronave(GLfloat x, GLfloat y) {
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0.0,0.65,0.0);
  glVertex3f(0.0+x,3.0+y,0.0);

  glColor3f(0.0,1.0,0.0);
  glVertex3f(-4.0+x,-3.0+y,0.0);

  glColor3f(0.0,0.4,0.0);
  glVertex3f(4.0+x,-3.0+y,0.0);

  glColor3f(0.0,0.4,0.0);
  glVertex3f(0.0+x,-3.0+y,-4.0);

  glColor3f(0.0,0.4,0.0);
  glVertex3f(-4.0+x,-3.0+y,0.0);
  glEnd();
}