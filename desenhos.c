#include <GL/glut.h>

void desenharAeronave(GLfloat x, GLfloat y) {
  glPushMatrix ();
  
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
  glPopMatrix ();
}

void desenharInimigo(GLfloat x, GLfloat y) {
  glPushMatrix ();
  
  glBegin(GL_TRIANGLE_FAN);
  glColor3f(0.65,0.0,0.0);
  glVertex3f(0.0+x,-3.0+y,0.0);

  glColor3f(1.0,0.0,0.0);
  glVertex3f(-4.0+x,3.0+y,0.0);

  glColor3f(0.4,0.0,0.0);
  glVertex3f(4.0+x,3.0+y,0.0);

  glColor3f(0.4,0.0,0.0);
  glVertex3f(0.0+x,3.0+y,-4.0);

  glColor3f(0.4,0.0,0.0);
  glVertex3f(-4.0+x,3.0+y,0.0);
  glEnd();
  glPopMatrix ();
}


void desenharTiro(GLfloat x, GLfloat y) {
  glPushMatrix ();
    glColor3f(0.8,0.3,0.3);
    glTranslatef(x,y,1.0);
    glutSolidSphere (1.0, 20, 50);
    glTranslatef(x,y,1.0);
  glPopMatrix ();
}