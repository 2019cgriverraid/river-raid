#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "util.c"
#include "controle.c"
#include "desenhos.c"

#define PI 3.14159265
int lastId = 0;
GLfloat janelaX = 500;
GLfloat janelaY = 500;

GLfloat win = 30;
GLfloat anglex = 250.0;
GLfloat panX = 0.0;
GLfloat panY = -25.0;
//GLfloat posX = ;

GLfloat pi = PI/360.0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 0.5f, 5.0f, 2.0f, 0.0f };

struct Objeto objetos[100];

void init(void) {
  glClearColor(0.8f,0.8f, 0.8f, 0.8f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_PROJECTION); //define que a matrix é a de projeção
  glLoadIdentity(); //carrega a matrix de identidade
  glOrtho((-win), (+win),
          (-win), (+win),
          (-win), (win));
  // Ortho só deve ser setado uma vez, e nunca deve ser alterado
}

void aeronave(){

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //gluLookAt(sin(anglex*pi)+cos(anglex*pi),1.0,cos(anglex*pi)-sin(anglex*pi),
  gluLookAt(0.0,0.5,1.0,
            0.0, 0.0, 0.0,   //para onde a câmera aponta (P_ref)
            0.0, 1.0, 0.0); //vetor view-up (V)
  desenharAeronave(panX, panY);



}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

  aeronave();

  glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
  anglex = acionarLetra(key, anglex);
  // glutPostRedisplay(); // remover caso a atualização seja apenas por tempo
}

void controle(int key, int x, int y){
  struct Coordenadas coordenadas = acionarSetas(key, panX, panY, win);
  panX = coordenadas.panX;
  panY = coordenadas.panY;
  // glutPostRedisplay(); // remover caso a atualização seja apenas por tempo
}

void movimentarObjetosSecundarios () {
  for (int i = 0; i < 100; i++) {
    // procurar elementos dentro ?
    // diminuir o Y (aproximar do jogador) ?
  }
}

void movimentarPorTempo (){
  // TODO movimentar objetos "secundários"
  movimentarObjetosSecundarios();
  // TODO calcular colisao
  // TODO
  glutPostRedisplay();
  glutTimerFunc(20 /* tempo * escala */ , movimentarPorTempo, 0);
}

int  main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(janelaX, janelaY);
  glutInitWindowPosition(300 ,100);
  glutCreateWindow("River Raid 3D");

  init();

  glutDisplayFunc(display);
  glutTimerFunc(1, movimentarPorTempo, 0);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(controle);

  glutMainLoop();

  return 0;
}
