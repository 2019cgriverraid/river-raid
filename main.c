#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "util.c"
#include "controle.c"
#include "desenhos.c"
#include "textura.c"

int lastId = 0;
GLfloat janelaX = 500;
GLfloat janelaY = 500;

GLfloat win = 30;
GLfloat anglex = 250.0;
GLfloat panX = 0.0;
GLfloat panY = -25.0;
GLfloat width_wall = 9.0;
GLfloat taxa_descida_inimigo = 0;

int tiro = 0;
int contTiro = 0;

int fimDeJogo = 0;

float auxTempo = 0.0;

int tempoPadraoObjetos = 50; //50
int tempoIntervaloObjetos = 90; //90
int tempoCriaObjetos = 0.0;
int tempoRolagem = 10;

GLuint texture_id1, texture_id2;

Lista objetos;
Aeronave aviao;

// Define posições iniciais da Aeronave e dos tiros
void inicializaAeronave(){
  aviao.x = 0.0;
  aviao.y = -25.0;
  aviao.rotX = 0.0;
  aviao.rotY = 0.0;

  int i;
  for(i=0; i<NUM_TIROS; i++){
    aviao.tiros[i].naTela = 0;
    aviao.tiros[i].y = -22;
    aviao.tiros[i].x = -31;
  }
}

// Inicialização
void init(void) {
  
  glClearColor(0.3f,0.0f,1.0f,1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_SMOOTH);   
  glEnable(GL_DEPTH_TEST); //habilita o teste de profundidade
  glMatrixMode(GL_MODELVIEW); //define que a matrix é a de projeção
  glLoadIdentity(); //carrega a matrix de identidade
  glOrtho((-win), (+win),
          (-win), (+win),
          (-win), (win));
  // Ortho só deve ser setado uma vez, e nunca deve ser alterado
  
  inicializaAeronave();
  inicializarLista(&objetos);
  //lighting(); //defininido os parâmetros de iluminação

  glGenTextures(1,&texture_id1);

  glPushMatrix();
}

// Desenha avião e tiros
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

// Verifica se ocorreu a colisão tiro-obstaculo e aviao-obstaculo
void verificarColisao(){
  int i;
  Objeto *p = objetos.inicio;
  while(p != NULL){
    for(i=0; i<NUM_TIROS; i++){
      //if(dist(15.0,pos_inimigo, aviao.tiros[i].x, aviao.tiros[i].y) < 5){
      if(dist(p->posX, p->posY, aviao.tiros[i].x, aviao.tiros[i].y) < 4){
        //pos_inimigo = 37.0;
        p->posY = 37.0;
        remover(&objetos, p->posY, p->posX);// = 37.0;
        aviao.tiros[i].x =-31.0;
      }
    }
    //if(dist(15.0,pos_inimigo, aviao.x, aviao.y) < 5){
    if(dist(p->posX, p->posY, aviao.x, aviao.y) < 4){
      //pos_inimigo = 37.0;
      //p->posY = 37.0;
      fimDeJogo = 1;
      aviao.x = 0.0;
    }
    if(p->posY < -30){
      p->posY = 37.0;
    }
    p = p->prox;
  }

}

// Desenha objetos obstáulo
void desenharObjetos(){
  Objeto *p = objetos.inicio;
  while(p != NULL){
    desenharInimigo(p->posX, p->posY);
    p = p->prox;
  }
}

// Define o que será mostrado na tela
void display(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer
  if(!fimDeJogo){ //DESENHA OBJETOS NA TELA
    aeronave();
    //desenharInimigo(15.0, (panY+10.0));
    desenharObjetos();
    //int posx = (2*win-win/2);
    //desenharInimigo(rand() % posx,pos_inimigo);
    glEnable(GL_TEXTURE_2D);
    desenhaParedeEsquerda(win,width_wall,texture_id1);
    desenhaParedeDireita(win,width_wall,texture_id1);
    desenhaAgua(win,width_wall,texture_id2);
    glDisable(GL_TEXTURE_2D);
  }
  else{ // TELA AZUL
    if(auxTempo == 0.0) printf("fim de jogo\n");
    if(auxTempo<100) auxTempo+=1;
    else fimDeJogo = 0;
  }
  glutSwapBuffers();
}

// NÃO EXCLUIR - Controle extra, tá sobrando, mas vamos usar pra fazer o avião rotacionar na movimentação
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

// Adiciona um tiro no vetor de tiros e seta a posição inicial dele
void controleTiros(){
  aviao.tiros[contTiro].x = aviao.x;
  aviao.tiros[contTiro].y = -22.0;
  //printf("%d: %f\n",contTiro, aviao.x );
  //aviao.tiros[contTiro].naTela = 1;
  contTiro = (contTiro+1) % NUM_TIROS;     //troca de 10 para 30 porque se dermos tiros consecutivos sem parar porque 
                                    //com % 10 eles somem no meio da tela
  tiro = 1;
}

// Controle das setas
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
            //if(aviao.x-4>-win+width_wall)
            if(aviao.x  - 4<=-win +width_wall + 0.5)
              fimDeJogo = 1;
            else
              aviao.x -= 1.0; //movimenta o avião para a esquerda
            break;
        case GLUT_KEY_RIGHT:
            //if(aviao.x+4<win-width_wall) 
            if(aviao.x + 4 >= win -width_wall - 0.5) 
              fimDeJogo = 1;
              aviao.x += 1.0; //movimenta o avião para a direita
            break;
    }
    glutPostRedisplay();
}

// Cria novos objetos na lista de objetos, a partir do limite superior da tela
void criarObjetosSecundarios(){
  // Cria considerando o intervalo de tempo controlado pelas variáveis tempoCriaObjetos e tempoPadraoObjetos
  if(tempoCriaObjetos == tempoPadraoObjetos){
    inserir(&objetos, win, 28.0, width_wall);
    tempoCriaObjetos = -tempoIntervaloObjetos;
  }
}

// Movimenta para baixo os objetos que não foram atingidos
void movimentarObjetosSecundarios () {
  Objeto *p = objetos.inicio;
  while(p != NULL){
    if(p->posY != 37.0) p->posY -= 0.2;
    p = p->prox;
  }
}

// Executa a cada 10ms inicialmente, cria e movimenta os objetos, além de verificar a colisão
// TO DO: fazer variar o tempo de acordo com o nivel que o jogador está
void movimentarPorTempo (){
  tempoCriaObjetos += 1;
  //printf("%d\n", tempoCriaObjetos);
  
  criarObjetosSecundarios();
  movimentarObjetosSecundarios();
  verificarColisao();
  
  if(tiro){
      int i;
      for(i=0; i<NUM_TIROS; i++){
          aviao.tiros[i].y += 0.4;
          if(aviao.tiros[i].y > 30.0){
            aviao.tiros[i].y = -30.0;
            aviao.tiros[i].x = -31.0;
          }
      }
  }
  
  glutPostRedisplay();
	glutTimerFunc(tempoRolagem, movimentarPorTempo, 1);
}

int main(int argc, char** argv){
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
  glutInitWindowSize(janelaX, janelaY);
  glutInitWindowPosition(300 ,100);
  glutCreateWindow("River Raid 3D");
  init();

  CarregaTextura("grama.bmp",texture_id1);
  CarregaTextura("agua.bmp",texture_id2);

  /*SetupRC();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);*/

  glutDisplayFunc(display);
  glutKeyboardFunc(teclado);
  glutSpecialFunc(controle);
  glutTimerFunc(tempoRolagem, movimentarPorTempo, 1);

  glutMainLoop();

  return 0;
}