#include <stdio.h>
#include <stdlib.h>
#include <GL/glut.h>
#include <math.h>

float rX=0.0;
float rY=0.0;
float x = 6.0;
float y = -25.0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };


int tiro = 0;
int novoTiro = 0;
int contTiro = 0;

typedef struct tipoTiros{
    float x;
    float y;
}tipoTiros;

tipoTiros tiros[30];

GLuint  jato;

void init(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(-50, 50,
            -50, 50,
            -50, 50);
    glPushMatrix();
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


void desenhaAeronave(){
    
    GLfloat asa[][3]={
        {-4.0,0.0,0.0},
        {+4.0,0.0,0.0},
        {0.0,0.0,3.0}
    };

    GLfloat cauda[][3]={
        {0.0,0.5,0.0},
        {0.0,2.0,0.0},
        {0.0,1.6,0.9},
        {0.0,0.0,2.0}
    };

    GLUquadricObj *quadric;
    glColor3f(1.0,1.0,1.0);

    //asas
    glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(0,0,2);
        glBegin(GL_TRIANGLES); 
            glVertex3fv(asa[0]);
            glVertex3fv(asa[1]);
            glVertex3fv(asa[2]);
        glEnd();
    glPopMatrix();

    //cauda
    glPushMatrix();
        glTranslatef(0,-5.5,0.6);
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

}

void aeronave(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        //glTranslatef(x, y, 0.0);    
        glRotatef(rX,0,1,0);
        glRotatef(rY,1,0,0);

        desenhaAeronave();

    glPopMatrix();

    glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
    switch(key){
        case '8':
            rY -= 5;
            break;
        case '2':
            rY += 5;
            break;    
        case '4':
            rX -= 5;
            break;
        case '6':
            rX += 5;
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

int main ( int argc , char * argv [] ){
    glutInit(&argc , argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowPosition (50 ,100);
    glutInitWindowSize (600 ,600);
    glutCreateWindow ("Avião");

    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);

    glPushMatrix();
    glTranslatef(0.0,0.0,-1.0);
    glLightfv(GL_LIGHT0, GL_AMBIENT,  light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE,  light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);
    glPopMatrix();

    init();
    glutDisplayFunc(aeronave);
    glutKeyboardFunc(teclado);
    glutMainLoop ();
    return 0;
}
