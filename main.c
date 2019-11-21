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

GLfloat win = 50;
GLfloat anglex = 250.0;
GLfloat width_wall = 9.0;

int tiro = 0;
int contTiro = 0;

int fimDeJogo = 0;

float auxTempo = 0.0;

int horaDoCombustivel = 500; 
int tempoAuxComb = 0;
int intervaloEntreComb = 500;

int horaDoObstaculo = 100; // define o limite para a variável tempoAuxObstaculo, qd alcança, um obstáculo é criado
int tempoAuxObstaculo = 0; // conta o tempo que se passou sem obstáculo
int intervaloEntreObjetos = 100; // controla o intervalo entre a aparição de cada obstáculo, pode ser alterada conforme o nível aumenta

int tempoRolagem = 10;

GLuint texture_id1, texture_id2;

Lista objetos;
Aeronave aviao;

// Define posições iniciais da Aeronave e dos tiros
void inicializaAeronave(){
    aviao.x = 0.0;
    aviao.y = -win + 5.0;
    aviao.rotX = 0.0;
    aviao.rotY = 0.0;
    aviao.pontuacao = 0;
    aviao.combustivel = 30;

    int i;
    for (i = 0; i < NUM_TIROS; i++){
        aviao.tiros[i].naTela = 0;
        aviao.tiros[i].y = aviao.y + 3;
        aviao.tiros[i].x = -win - 1;
    }
}

// Inicialização
void init(void){

    glClearColor(0.3f, 0.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_SMOOTH);
    glEnable(GL_DEPTH_TEST);    //habilita o teste de profundidade
    glMatrixMode(GL_MODELVIEW); //define que a matrix é a de projeção
    glLoadIdentity();           //carrega a matrix de identidade
    glOrtho((-win), (+win),
            (-win), (+win),
            (-win), (win));
    // Ortho só deve ser setado uma vez, e nunca deve ser alterado

    inicializaAeronave();
    inicializarLista(&objetos);
    //lighting(); //defininido os parâmetros de iluminação

    glGenTextures(1, &texture_id1);

    glPushMatrix();
}

// Desenha avião e tiros
void aeronave(){
    //glMatrixMode(GL_MODELVIEW);
    //glLoadIdentity();

    glPushMatrix();
    glTranslatef(aviao.x, aviao.y, 0.0); //leva o avião para baixo na tela
    glRotatef(aviao.rotX, 0, 1, 0);      //será usado para rotacionar levemente o avião para os lados em direção ao eixo x quando ele se movimentar
    //glRotatef(aviao.rotY,1,0,0);
    desenhaAeronave();
    glPopMatrix();

    if (tiro){
        int i;
        for (i = 0; i < NUM_TIROS; i++){
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

    while (p != NULL){
        for (i = 0; i < NUM_TIROS; i++){

            // Checa colisão do tiro
            if (dist(p->posX, p->posY, aviao.tiros[i].x, aviao.tiros[i].y) < 4){

                p->posY = win + 7.0; // seta posição y fixa para remoção
                remover(&objetos, p->posY, p->posX, win);
                aviao.tiros[i].x = -win - 5.0; // tira o tiro da tela

                // Atribui pontuação de acordo com o tamanho do obstáculo
                if (p->tipo == 0)
                    aviao.pontuacao += 80;
                else if (p->tipo == 1)
                    aviao.pontuacao += 30;
                else if (p->tipo == 2)
                    aviao.pontuacao += 60;
                // ...

                printf("PONTUAÇÃO: %d\n", aviao.pontuacao);
            }
        }

        // Checa colisão de obstáculo com a aeronave
        if (p->tipo != 0 && dist(p->posX, p->posY, aviao.x, aviao.y) < 4)
            fimDeJogo = 1; // Jogo acaba se sim

        // Checa se passou por posto de combustível
        if (p->tipo == 0 && dist(p->posX, p->posY, aviao.x, aviao.y) < 4)
            aviao.combustivel = (aviao.combustivel + 3) > 30 ? 30 : aviao.combustivel + 3;

        // Checa se o objeto não passou da fronteira inferior da janela
        if (p->posY < -win)
            p->posY = win + 7.0; // seta posição y fixa para remoção

        p = p->prox;
    }
}

// Desenha objetos obstáulo
void desenharObjetos(){
    Objeto *p = objetos.inicio;

    while (p != NULL){
        if (p->tipo == 0)
            desenharPostoCombustivel(p->posX, p->posY);
        else if (p->tipo == 1)
            desenharInimigo(p->posX, p->posY);
        p = p->prox;
    }
}

// Define o que será mostrado na tela
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //limpa o buffer

    if (!fimDeJogo){ // desenha objetos na tela

        glEnable(GL_TEXTURE_2D);
        desenhaParedeEsquerda(win, width_wall, texture_id1);
        desenhaParedeDireita(win, width_wall, texture_id1);
        desenhaAgua(win, width_wall, texture_id2);
        glDisable(GL_TEXTURE_2D);
        
        desenharObjetos();
        aeronave();
    }
    else{ // TELA AZUL
        if (auxTempo == 1.0)
        {
            printf("fim de jogo\n");
            inicializaAeronave();
            removerTudo(&objetos, win);
        }
        if (auxTempo < 100)
            auxTempo += 1;
        else
        {
            fimDeJogo = 0;
            auxTempo = 0.0;
        }
    }
    glutSwapBuffers();
}

// NÃO EXCLUIR - Controle extra, tá sobrando, mas vamos usar pra fazer o avião rotacionar na movimentação
void teclado(unsigned char key, int x, int y){
    //anglex = acionarLetra(key, anglex);
    switch (key)
    {
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
    aviao.tiros[contTiro].x = aviao.x;    //mesmo x da da posição do avião quando ele atirou
    aviao.tiros[contTiro].y = -win + 3.0; //pra sair da beira do avião
    //printf("%d: %f\n",contTiro, aviao.x );
    //aviao.tiros[contTiro].naTela = 1;
    contTiro = (contTiro + 1) % NUM_TIROS; //troca de 10 para 30 porque se dermos tiros consecutivos sem parar porque
                                           //com % 10 eles somem no meio da tela
    tiro = 1;
}

// Controle das setas
void controle(int key, int xx, int yy){

    //controleSetas(key, aviao);
    switch (key)
    {
    case GLUT_KEY_UP:
        controleTiros();
        break;
    case GLUT_KEY_DOWN:
        //rY += 5;
        break;
    case GLUT_KEY_LEFT:
        if (aviao.x - 4 <= -win + width_wall + 0.5)
            fimDeJogo = 1;
        else
            aviao.x -= 1.3; //movimenta o avião para a esquerda
        break;
    case GLUT_KEY_RIGHT:
        if (aviao.x + 4 >= win - width_wall - 0.5)
            fimDeJogo = 1;
        aviao.x += 1.3; //movimenta o avião para a direita
        break;
    }
    glutPostRedisplay();
}

// Cria novos objetos na lista de objetos, a partir do limite superior da tela
void criarObjetosSecundarios(){
    // Cria considerando o intervalo de tempo controlado pelas variáveis tempoAuxObstaculo e horaDoObstaculo
    if (tempoAuxObstaculo == horaDoObstaculo){
        inserir(&objetos, win, win - 2.0, 1, width_wall);
        tempoAuxObstaculo = -intervaloEntreObjetos;
    }

    if (tempoAuxComb == horaDoCombustivel){
        inserir(&objetos, win, win - 2.0, 0, width_wall);
        tempoAuxComb = -intervaloEntreComb;
    }
}

// Movimenta para baixo os objetos que não foram atingidos
void movimentarObjetosSecundarios(){
    Objeto *p = objetos.inicio;

    while (p != NULL)
    {
        if (p->posY != (win + 7.0))
            p->posY -= 0.2;
        p = p->prox;
    }
}

// Executa a cada 10ms inicialmente, cria e movimenta os objetos, além de verificar a colisão
// TO DO: fazer variar o tempo de acordo com o nivel que o jogador está
void movimentarPorTempo(){
    if (!fimDeJogo)
    {
        printf("tempo: %d, %d\n", tempoAuxComb, aviao.combustivel);
        if(aviao.combustivel <= 0)
            fimDeJogo = 1;

        else{
            tempoAuxObstaculo++;
            tempoAuxComb++;
            if(!(tempoAuxComb % 50)) aviao.combustivel--;

            criarObjetosSecundarios();
            movimentarObjetosSecundarios();
            verificarColisao();

            if (tiro){
                int i;
                for (i = 0; i < NUM_TIROS; i++){
                    aviao.tiros[i].y += 0.8;
                    if (aviao.tiros[i].y > win){
                        aviao.tiros[i].y = -win;
                        aviao.tiros[i].x = -win - 5.0;
                    }
                }
            }
        }
    }
    glutPostRedisplay();
    glutTimerFunc(tempoRolagem, movimentarPorTempo, 1);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(janelaX, janelaY);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("River Raid 3D");
    init();

    CarregaTextura("grama.bmp", texture_id1);
    CarregaTextura("agua.bmp", texture_id2);

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