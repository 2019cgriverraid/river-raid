#include <GL/glut.h>

void desenharAeronave() {
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(1.0,0.0,0.0);
  glVertex3f(0.0,3.0,0.0);

  glColor3f(0.0,1.0,0.0);
  glVertex3f(-4.0,-3.0,0.0);

  glColor3f(0.0,0.0,1.0);
  glVertex3f(4.0,-3.0,0.0);

  glColor3f(1.0,0.0,1.0);
  glVertex3f(0.0,-3.0,-4.0);

  glColor3f(1.0,1.0,0.0);
  glVertex3f(-4.0,-3.0,0.0);
  glEnd();
}