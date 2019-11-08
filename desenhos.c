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

void desenhaParede(GLfloat win, GLfloat width_wall){
    glBegin(GL_POLYGON);
      glColor3f(0.11,0.38,0.09);
      glVertex3f(-win,-win*2,1);
      glVertex3f(-win,win*2,1);
      glVertex3f(-win+width_wall,win*2,1);
      glVertex3f(-win+width_wall,-win*2,1);
    glEnd();

    glBegin(GL_POLYGON);
      glColor3f(0.11,0.38,0.09);
      glVertex3f(win,-win*2,1);
      glVertex3f(win,win*2,1);
      glVertex3f(win-width_wall,win*2,1);
      glVertex3f(win-width_wall,-win*2,1);
    glEnd();
}