#include <GL/glut.h>

void desenhaAeronave(){
   glBegin(GL_TRIANGLE_FAN);
      glColor3f(1.0,0.0,0.0);
      glVertex3f(0.0,3.0,2.0);

      glColor3f(0.0,1.0,0.0);
      glVertex3f(-4.0,-3.0,2.0);

      glColor3f(0.0,0.0,1.0);
      glVertex3f(4.0,-3.0,2.0);

      glColor3f(1.0,0.0,1.0);
      glVertex3f(0.0,-3.0,6.0);

      glColor3f(1.0,1.0,0.0);
      glVertex3f(-4.0,-3.0,2.0);
   glEnd();
}

void desenhaTiro(){
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(-0.5,-0.5,0.5);
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(-0.5,0.5,0.5);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(0.5,-0.5,-0.5);
      glVertex3f(0.5,0.5,-0.5);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(0.5,-0.5,0.5);
      glVertex3f(-0.5,-0.5,0.5);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(0.5,-0.5,-0.5);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(-0.5,0.5,0.5);
      glVertex3f(0.5,0.5,0.5);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(-0.5,0.5,-0.5);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(0.5,0.5,-0.5);
      glVertex3f(0.5,-0.5,-0.5);
   glEnd();
   glColor3f(1.0,1.0,1.0);
   glBegin(GL_POLYGON);
      glVertex3f(-0.5,0.5,-0.5);
      glVertex3f(-0.5,-0.5,-0.5);
      glVertex3f(-0.5,-0.5,0.5);
      glVertex3f(-0.5,0.5,0.5);
   glEnd();
}

void desenharPostoCombustivel(GLfloat x, GLfloat y){
   glPushMatrix ();

      glColor3f(1.0,0.0,0.0);

      GLfloat tam = 4.0;

      glTranslatef(x, y, 0.0);

      glBegin(GL_POLYGON);
         glVertex3f(-tam,-tam,tam);
         glVertex3f(tam,-tam,tam);
         glVertex3f(tam,tam,tam);
         glVertex3f(-tam,tam,tam);
      glEnd();
      
      glBegin(GL_POLYGON);
         glVertex3f(tam,tam,tam);
         glVertex3f(tam,-tam,tam);
         glVertex3f(tam,-tam,-tam);
         glVertex3f(tam,tam,-tam);
      glEnd();

      glBegin(GL_POLYGON);
         glVertex3f(tam,-tam,tam);
         glVertex3f(-tam,-tam,tam);
         glVertex3f(-tam,-tam,-tam);
         glVertex3f(tam,-tam,-tam);
      glEnd();

      glBegin(GL_POLYGON);
         glVertex3f(-tam,tam,tam);
         glVertex3f(tam,tam,tam);
         glVertex3f(tam,tam,-tam);
         glVertex3f(-tam,tam,-tam);
      glEnd();

      glBegin(GL_POLYGON);
         glVertex3f(-tam,-tam,-tam);
         glVertex3f(-tam,tam,-tam);
         glVertex3f(tam,tam,-tam);
         glVertex3f(tam,-tam,-tam);
      glEnd();

      glBegin(GL_POLYGON);
         glVertex3f(-tam,tam,-tam);
         glVertex3f(-tam,-tam,-tam);
         glVertex3f(-tam,-tam,tam);
         glVertex3f(-tam,tam,tam);
      glEnd();

   glPopMatrix();
}

void desenharInimigo(GLfloat x, GLfloat y) {
  glPushMatrix();
  
  glBegin(GL_TRIANGLE_FAN);
   glColor3f(0.65,0.0,0.0);
   glVertex3f(0.0+x,-3.0+y,6.0);

   glColor3f(1.0,0.0,0.0);
   glVertex3f(-4.0+x,3.0+y,6.0);

   glColor3f(0.4,0.0,0.0);
   glVertex3f(4.0+x,3.0+y,6.0);

   glColor3f(0.4,0.0,0.0);
   glVertex3f(0.0+x,3.0+y,2.0);

   glColor3f(0.4,0.0,0.0);
   glVertex3f(-4.0+x,3.0+y,6.0);
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

void desenhaParedeEsquerda(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
   glPushMatrix();
      glBindTexture ( GL_TEXTURE_2D, texture_id );
      glBegin(GL_POLYGON);
         glColor3f(0.0,1.0,0.0);
         glTexCoord2f(0.0f, 0.0f); glVertex3f(-win,-win*4-y,1);
         glTexCoord2f(1.0f, 0.0f);  glVertex3f(-win,win*4-y,1);
         glTexCoord2f(0.0f, 1.0f); glVertex3f(-win+width_wall,win*4-y,1);
         glTexCoord2f(1.0f, 1.0f); glVertex3f(-win+width_wall,-win*4-y,1);
      glEnd();
   glPopMatrix();
}


void desenhaParedeDireita(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
   glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      glBindTexture ( GL_TEXTURE_2D, texture_id );
      glBegin(GL_POLYGON);
            glColor3f(0.0,1.0,0.0);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(win,-win*4-y,-1);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(win,win*4-y,-1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(win-width_wall,win*4-y,-1);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(win-width_wall,-win*4-y,-1);
      glEnd();
   glPopMatrix();
}

void desenhaAgua(GLfloat win, GLfloat width_wall, GLuint texture_id, GLfloat y){
   glPushMatrix();
      glEnable(GL_TEXTURE_2D);
      glBindTexture ( GL_TEXTURE_2D, texture_id );
      glBegin(GL_POLYGON);
            glColor3f(0.0,0.0,0.88);
            glTexCoord2f(0.0f, 0.0f); glVertex3f(win-width_wall+1,-win*4-y,-1);
            glTexCoord2f(1.0f, 0.0f); glVertex3f(win-width_wall+1,win*4-y,-1);
            glTexCoord2f(0.0f, 1.0f); glVertex3f(-win+width_wall-1,win*4-y,-1);
            glTexCoord2f(1.0f, 1.0f); glVertex3f(-win+width_wall-1,-win*4-y,-1);
      glEnd();
   glPopMatrix();
}
      


   
