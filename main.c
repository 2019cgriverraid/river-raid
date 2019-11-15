#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "util.c"
#include "controle.c"
#include "desenhos.c"

int lastId = 0;
GLfloat janelaX = 500;
GLfloat janelaY = 500;

GLfloat win = 30;
GLfloat anglex = 250.0;
GLfloat panX = 0.0;
GLfloat panY = -25.0;
GLfloat width_wall = 9.0;

GLfloat x0_inimigo = 0;
GLfloat y0_inimigo = 500; // = janelaY

int tiro = 0;
int contTiro = 0;

const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 0.5f, 5.0f, 2.0f, 0.0f };

//Objeto objetos[100];
Aeronave aviao;

void inicializaAeronave(){
  aviao.x = 0.0;
  aviao.y = -25.0;
  aviao.rotX = 0.0;
  aviao.rotY = 0.0;

  int i;
  for(i=0; i<NUM_TIROS; i++){
    aviao.tiros[i].naTela = 0;
    aviao.tiros[i].y = -22;
  }
}

void init(void) {
  
  glClearColor(0.3f,0.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW); //define que a matrix é a de projeção
  glLoadIdentity(); //carrega a matrix de identidade
  glOrtho((-win), (+win),
          (-win), (+win),
          (-win), (win));
  // Ortho só deve ser setado uma vez, e nunca deve ser alterado
  inicializaAeronave();
  glPushMatrix();
}

void aeronave(){
  //glMatrixMode(GL_MODELVIEW);
  //glLoadIdentity();

  glPushMatrix();
      glTranslatef(aviao.x, aviao.y, 0.0); //leva o avião para baixo na tela
      glRotatef(aviao.rotX,0,1,0); //será usado para rotacionar levemente o avião para os lados em direção ao eixo x quando ele se movimentar
      //glRotatef(aviao.rotY,1,0,0);
      desenhaAeronave();
  glPopMatrix();

  if(tiro){
      int i;
      for(i=0; i<NUM_TIROS; i++){
        glPushMatrix();
            glTranslatef(aviao.tiros[i].x, aviao.tiros[i].y, 0.0);
            desenhaTiro();
        glPopMatrix();    
      }
  }

}

void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

  aeronave();
  //desenharInimigo(15.0, (panY+10.0));
  desenharInimigo(15.0,-panY);
  desenhaParede(win,width_wall);
  glutSwapBuffers();
}

void teclado(unsigned char key, int x, int y){
  //anglex = acionarLetra(key, anglex);
  switch(key){
      case '8':
          aviao.rotY -= 5;
          break;
      case '2':
          aviao.rotY += 5;
          break;    
      case '4':
          aviao.rotX -= 5;
          break;
      case '6':
          aviao.rotX += 5;
          break;
      default:
          break;
  }
  glutPostRedisplay();
}

void controleTiros(){
  aviao.tiros[contTiro].x = aviao.x;
  aviao.tiros[contTiro].y = -22.0;
  //aviao.tiros[contTiro].naTela = 1;
  contTiro = (contTiro+1) % 30;     //troca de 10 para 30 porque se dermos tiros consecutivos sem parar porque 
                                    //com % 10 eles somem no meio da tela
  tiro = 1;
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
            if(aviao.x-4>-win+width_wall) 
              aviao.x -= 1.0; //movimenta o avião para a esquerda
            break;
        case GLUT_KEY_RIGHT:
            if(aviao.x+4<win-width_wall) 
              aviao.x += 1.0; //movimenta o avião para a direita
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
      for(i=0; i<NUM_TIROS; i++){
          aviao.tiros[i].y += 0.2;
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
  glutKeyboardFunc(teclado);
  glutSpecialFunc(controle);
  glutTimerFunc(10, movimentarPorTempo, 1);
  glutMainLoop();

  return 0;
}