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

float win = 30;

int tiro = 0;
int novoTiro = 0;
int contTiro = 0;

typedef struct tipoTiros{
    float x;
    float y;
}tipoTiros;

tipoTiros tiros[30];

GLuint jato;

void init(){
    glClearColor(0, 0, 0, 0); //Preto
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glOrtho(-win, win,
            -win, win,
            -win, win);
    glPushMatrix();
}

void desenhaHelicoptero(){
    
    GLUquadricObj *quadric;
    glColor3f(1.0,1.0,1.0);
    glRotatef(5, 1.0, 0.0, 0.0);

    //cauda
    glPushMatrix();
        glRotatef(-10, 1, 0, 0);
        glTranslatef(0,0.5,0);
        glTranslatef(0,0,1.8);
        quadric = gluNewQuadric();
        gluCylinder(quadric, 0.9, 0.3, 3.7, 20, 20);
    glPopMatrix();

    //corpo
    glPushMatrix();
        glutSolidSphere(2.5, 15, 15);
    glPopMatrix(); 
    
    //base da helice
    glPushMatrix();
        glTranslatef(0.0, 2.4, 0.0);
        glRotatef(-90, 1, 0, 0);
        quadric = gluNewQuadric();
        gluCylinder(quadric, 0.5, 0.5, 1.0, 20, 20);
    glPopMatrix();

}

void desenhaHeliceMaior(GLint i){
    glPushMatrix();
    glRotatef(i, 0.0, 1.0, 0.0);
    
    glPushMatrix();
        glTranslatef(0.0, 3.4, 0.0);
        glScalef(8, 0.2, 1.5);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(0.0, 3.4, 0.0);
        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(8, 0.2, 1.5);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

void desenhaHeliceMenor(GLint i){
    glPushMatrix();

    glPushMatrix();
       glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 5.4, -1.5);
        glScalef(3, 0.2, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    glPushMatrix();
        glRotatef(90, 1.0, 0.0, 0.0);
        glTranslatef(0.0, 5.4, -1.5);

        glRotatef(90, 0.0, 1.0, 0.0);
        glScalef(3, 0.2, 0.5);
        glutSolidCube(1);
    glPopMatrix();

    glPopMatrix();
}

int i = 0;
void movimentarHelices(){

    i+=1;
    
    desenhaHeliceMaior(i);
    desenhaHeliceMenor(i);
    glutPostRedisplay();
    glutTimerFunc(1000, movimentarHelices, 1);
}

void helicoptero(){

    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glPushMatrix();

        glRotatef(120, 0, 1, 0);
        glRotatef(-20, 1, 0, 0);
   
        glRotatef(rX,0,1,0);
        glRotatef(rY,1,0,0);

        desenhaHelicoptero();
        movimentarHelices();

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
    glutCreateWindow ("Helicoptero");

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
    glutDisplayFunc(helicoptero);
    glutKeyboardFunc(teclado);
    glutTimerFunc(10, movimentarHelices, 1);
    glutMainLoop ();
    return 0;
}
