#include <GL/glut.h>
#include "controle.c"
void desenhaAeronave(){
   glPushMatrix();

    GLfloat asa[][3] = {
        {-4.0, 0.0, 0.0},
        {+4.0, 0.0, 0.0},
        {0.0, 0.0, 3.0}};

    GLfloat cauda[][3] = {
        {0.0, 0.5, 0.0},
        {0.0, 2.0, 0.0},
        {0.0, 1.6, 0.9},
        {0.0, 0.0, 2.0}};

    GLUquadricObj *quadric;
    glColor3f(1.0, 1.0, 1.0);

    //asas
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0, 0, 2);
    glBegin(GL_TRIANGLES);
    glVertex3fv(asa[0]);
    glVertex3fv(asa[1]);
    glVertex3fv(asa[2]);
    glEnd();
    glPopMatrix();

    //cauda
    glPushMatrix();
    glTranslatef(0, -5.5, 0.6);
    glBegin(GL_POLYGON);
    glVertex3fv(cauda[0]);
    glVertex3fv(cauda[1]);
    glVertex3fv(cauda[2]);
    glVertex3fv(cauda[3]);
    glEnd();
    glPopMatrix();

    //corpo
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.6, 0.9, 5.5, 12, 3);
    glPopMatrix();

    //cockpit
    glPushMatrix();
    //glTranslatef(0,6,0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.6, 1.2, 15, 15);
    glPopMatrix();
    glPopMatrix();
}

void desenhaAeronaveVermelha(){
   glPushMatrix();

    GLfloat asa[][3] = {
        {-4.0, 0.0, 0.0},
        {+4.0, 0.0, 0.0},
        {0.0, 0.0, 3.0}};

    GLfloat cauda[][3] = {
        {0.0, 0.5, 0.0},
        {0.0, 2.0, 0.0},
        {0.0, 1.6, 0.9},
        {0.0, 0.0, 2.0}};

    GLUquadricObj *quadric;
    glColor3f(1.0, 0.4, 0.4);

    //asas
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    glTranslatef(0, 0, 2);
    glBegin(GL_TRIANGLES);
    glVertex3fv(asa[0]);
    glVertex3fv(asa[1]);
    glVertex3fv(asa[2]);
    glEnd();
    glPopMatrix();

    //cauda
    glPushMatrix();
    glTranslatef(0, -5.5, 0.6);
    glBegin(GL_POLYGON);
    glVertex3fv(cauda[0]);
    glVertex3fv(cauda[1]);
    glVertex3fv(cauda[2]);
    glVertex3fv(cauda[3]);
    glEnd();
    glPopMatrix();

    //corpo
    glPushMatrix();
    glRotatef(90, 1.0, 0.0, 0.0);
    quadric = gluNewQuadric();
    gluCylinder(quadric, 0.6, 0.9, 5.5, 12, 3);
    glPopMatrix();

    //cockpit
    glPushMatrix();
    //glTranslatef(0,6,0);
    glRotatef(-90, 1.0, 0.0, 0.0);
    glutSolidCone(0.6, 1.2, 15, 15);
    glPopMatrix();
    glPopMatrix();
}

void desenhaTiro(){
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, 0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glEnd();
    glColor3f(1.0, 1.0, 1.0);
    glBegin(GL_POLYGON);
    glVertex3f(-0.5, 0.5, -0.5);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(-0.5, -0.5, 0.5);
    glVertex3f(-0.5, 0.5, 0.5);
    glEnd();
}

void desenharPostoCombustivel(GLfloat x, GLfloat y){
    glPushMatrix();

    //glColor3f(1.0, 1.0, 1.0);
    //gameOver(x-0.1, y+0.1, "F");
    //glColor3f(1.0, 1.0, 0.0);

    glColor3f(1.0,0.0,0.0);
    GLfloat tam = 4.0;

    glTranslatef(x, y-0.5, 0.0);
    glRotatef(0.0,0.0,90.0, 1.0);
    GLUquadricObj *quadObj;
    quadObj = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj, GLU_FILL);
    gluQuadricNormals (quadObj, GLU_SMOOTH);
    gluCylinder (quadObj, 4.0, 4.0, 3.0, 24, 4);
    glTranslatef(0.0,1.5,0.0);
    glColor3f(1.0,1.0,1.0);
    GLUquadricObj *quadObj2;
    quadObj2 = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj2, GLU_FILL);
    gluQuadricNormals (quadObj2, GLU_SMOOTH);
    gluCylinder (quadObj2, 4.0, 4.0, 3.0, 24, 4);
    glTranslatef(0.0,1.5,0.0);
    glColor3f(1.0,0.0,0.0);
    GLUquadricObj *quadObj3;
    quadObj3 = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj3, GLU_FILL);
    gluQuadricNormals (quadObj3, GLU_SMOOTH);
    gluCylinder (quadObj3, 4.0, 4.0, 3.0, 24, 4);
    glTranslatef(0.0,1.5,0.0);
    glColor3f(1.0,1.0,1.0);
    GLUquadricObj *quadObj4;
    quadObj4 = gluNewQuadric ();
    gluQuadricDrawStyle (quadObj4, GLU_FILL);
    gluQuadricNormals (quadObj4, GLU_SMOOTH);
    gluCylinder (quadObj4, 4.0, 4.0, 3.0, 24, 4);
    glTranslatef(0.0,4.0,0.0);
    

    glPopMatrix();
}

void desenharInimigo(GLfloat x, GLfloat y){
    glPushMatrix();
    glTranslatef(0,0,6);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.65, 0.0, 0.0);
    glVertex3f(0.0 + x, -3.0 + y, 4.0);

    glColor3f(1.0, 0.0, 0.0);
    glVertex3f(-4.0 + x, 3.0 + y, 4.0);

    glColor3f(0.4, 0.0, 0.0);
    glVertex3f(4.0 + x, 3.0 + y, 4.0);

    glColor3f(0.4, 0.0, 0.0);
    glVertex3f(0.0 + x, 3.0 + y, 0.0);

    glColor3f(0.4, 0.0, 0.0);
    glVertex3f(-4.0 + x, 3.0 + y, 4.0);
    glEnd();
    glPopMatrix();
}

void desenharTiro(GLfloat x, GLfloat y){
    glPushMatrix();
    glColor3f(0.8, 0.3, 0.3);
    glTranslatef(x, y, 1.0);
    glutSolidSphere(1.0, 20, 50);
    glTranslatef(x, y, 1.0);
    glPopMatrix();
}

void desenhaParedeEsquerda(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
    glPushMatrix();
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-win, -win * 4 - y, 1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-win, win * 4 - y, 1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-win + width_wall, win * 4 - y, 1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-win + width_wall, -win * 4 - y, 1);
    glEnd();
    glPopMatrix();
}

void desenhaParedeDireita(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 1.0, 0.0);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(win, -win * 4 - y, -1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(win, win * 4 - y, -1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(win - width_wall, win * 4 - y, -1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(win - width_wall, -win * 4 - y, -1);
    glEnd();
    glPopMatrix();
}

void desenhaAgua(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
    glPushMatrix();
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    glBegin(GL_POLYGON);
    glColor3f(0.0, 0.0, 0.88);
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(win - width_wall + 1, -win * 4 - y, -1);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(win - width_wall + 1, win * 4 - y, -1);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-win + width_wall - 1, win * 4 - y, -1);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-win + width_wall - 1, -win * 4 - y, -1);
    glEnd();
    glPopMatrix();
}
