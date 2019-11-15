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

GLfloat rX = 0.0;
GLfloat rY = 0.0;
GLfloat x = 6.0;
GLfloat y = -25.0;

GLfloat win = 30;
GLfloat anglex = 250.0;
GLfloat panX = 0.0;
GLfloat panY = -25.0;
GLfloat width_wall = 9.0;

int tiro = 0;
int novoTiro = 0;
int contTiro = 0;

typedef struct tipoTiros{
    float x;
    float y;
}tipoTiros;

tipoTiros tiros[30];

GLfloat pi = PI/360.0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 0.5f, 5.0f, 2.0f, 0.0f };

struct Objeto objetos[100];

void init(void) {
  //glClearColor(0.0f,0.0f, 0.0f, 0.0f);
  glClearColor(0.3f,0.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW); //define que a matrix é a de projeção
  glLoadIdentity(); //carrega a matrix de identidade
  glOrtho((-win), (+win),
          (-win), (+win),
          (-win), (win));
  // Ortho só deve ser setado uma vez, e nunca deve ser alterado
  glPushMatrix();
}


void aeronave(){

  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();

  glPushMatrix();

      glTranslatef(x, y, 0.0);    
      glRotatef(rX,0,1,0);
      glRotatef(rY,1,0,0);

      desenhaAeronave();

  glPopMatrix();

  if(tiro){
      int i;
      for(i=0; i<10; i++){
          glPushMatrix();
              glTranslatef(tiros[i].x, tiros[i].y, 0.0);
              desenhaTiro();
          glPopMatrix();    
      }
  }

}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

  aeronave();
  desenharInimigo(15.0, (panY+10.0));
  desenhaParede(win,width_wall);
  glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
  //anglex = acionarLetra(key, anglex);
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
  
  //glutPostRedisplay(); // remover caso a atualização seja apenas por tempo
}

void controleTiros(){
  tiro = 1;
  tiros[contTiro].x = x;
  tiros[contTiro].y = -22.0;
  contTiro = (contTiro+1) % 10;
}

void controle(int key, int xx, int yy){
  /*struct Coordenadas coordenadas = acionarSetas(key, panX, panY, win, width_wall);
  panX = coordenadas.panX;
  panY = coordenadas.panY;*/
  switch(key){
        case GLUT_KEY_UP:
            controleTiros();
            break;
        case GLUT_KEY_DOWN:
            //rY += 5;
            break;
        case GLUT_KEY_LEFT:
            x -= 1.0;
            break;
        case GLUT_KEY_RIGHT:
            x += 1.0;
            break;
    }
    glutPostRedisplay();
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

  if(tiro){
      int i;
      for(i=0; i<10; i++){
          tiros[i].y += 0.2;
      }
  }
  glutPostRedisplay();
	glutTimerFunc(10, movimentarPorTempo, 1);
}

int  main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(janelaX, janelaY);
  glutInitWindowPosition(300 ,100);
  glutCreateWindow("River Raid 3D");

  init();

  glutDisplayFunc(display);
  //glutTimerFunc(1, movimentarPorTempo, 0);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(controle);
  glutTimerFunc(10, movimentarPorTempo, 1);
  glutMainLoop();

  return 0;
}
