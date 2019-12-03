#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

#include "util.c"
#include "desenhos.c"
#include "textura.c"

int lastId = 0;
GLfloat janelaX = 500;
GLfloat janelaY = 500;

GLfloat win = 50;
GLfloat scenicMove = 0.0;
GLfloat anglex = 250.0;
GLfloat width_wall = 9.0;
int warning = 0;
int levelClearedMessage = 0;
int helicesRotacao = 0;


const GLfloat light_ambient[]  = { 0.0f, 0.0f, 0.0f, 1.0f };
const GLfloat light_diffuse[]  = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_specular[] = { 2.0f, 2.0f, 2.0f, 2.0f };
const GLfloat light_position[] = { 1.0, 1.0, 1.0, 0.0 };


int tiro = 0;
int timerTiro = 0;
int intervaloTiro = 48;
int contTiro = 0;

int fimDeJogo = 0;

float auxTempo = 0.0;
long tempoNivel = 0;
int nivel = 1;
int highscore = 0;
int ultimaPontuacao = 0;
int intervaloDoCombustivel = 285; 
int horaDoCombustivel; 

int tempoAuxComb = 0;
int vidas = 3;

int intervaloEntreHelicopteros = 200; // Controla o intervalo entre a aparição de cada obstáculo, pode ser alterada conforme o nível aumenta
int horaDoHelicoptero; // Define o limite para a variável tempoAuxHelicoptero, qd alcança, um obstáculo é criado
int tempoAuxHelicoptero = 0; // Conta o tempo que se passou sem obstáculo

int tempoRolagem = 10;

GLuint texture_id1, texture_id2;

Lista objetos;
Aeronave aviao;

GLint auxRot = 0;
GLint auxQtdRot = 0;
GLint combRecente = 0;

// Define posições iniciais da Aeronave e dos tiros
void inicializaAeronave(){
    aviao.x = 0.0;
    aviao.y = -win + 7.0;
    aviao.rotX = 0.0;
    aviao.rotY = 0.0;
    if (aviao.pontuacao > highscore) highscore = aviao.pontuacao;
    ultimaPontuacao = aviao.pontuacao;
    vidas = 3;
    aviao.pontuacao = 0;
    aviao.combustivel = 30;

    auxRot = 0;
    auxQtdRot = 0;
    combRecente = 0;
    tempoAuxComb = 0;
    tempoAuxHelicoptero = 0; 

    tempoNivel = 0;
    nivel = 1;
    horaDoHelicoptero = intervaloEntreHelicopteros;
    horaDoCombustivel = intervaloDoCombustivel;

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
    glEnable(GL_DEPTH_TEST);     // Habilita o teste de profundidade
    

    glMatrixMode(GL_PROJECTION); // Define que a matrix é a de projeção
    glLoadIdentity();            // Carrega a matrix de identidade
    glOrtho((-win), (+win),
            (-win), (+win),
            (-win), (win));

    glMatrixMode(GL_MODELVIEW);
     gluLookAt(0.0,0.5,1.0,
             0.0, 0.0, 0.0,   // Para onde a câmera aponta (P_ref)
             0.0, 1.0, 0.0);


    // Ortho só deve ser setado uma vez, e nunca deve ser alterado

    inicializaAeronave();
    inicializarLista(&objetos);

    glGenTextures(1, &texture_id1);

    glPushMatrix();
}

// Desenha aviao e tiros
void aeronave(){
    glPushMatrix();
        glTranslatef(aviao.x, aviao.y, 3.0); // Leva o aviao para baixo na tela
        if(warning > 0) desenhaAeronaveVermelha();
        else desenhaAeronave();
        
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
            if (p->tipo != 4 && dist(p->posX, p->posY, aviao.tiros[i].x, aviao.tiros[i].y) < 5){
                timerTiro = 0;

                aviao.tiros[i].x = -win - 5.0; // Retira o tiro da tela

                // Atribui pontuação de acordo com o tamanho do obstáculo
                if (p->tipo == 0){
                    aviao.pontuacao += 80;
                }
                else if (p->tipo == 1)
                    aviao.pontuacao += 30;

                p->posY = win + LIXO; // Seta posição y fixa para remoção
                remover(&objetos, p->posX, win);
            }
        }

        // Checa colisão de obstáculo com a aeronave
        if (p->tipo != 0 && p->tipo != 4 && dist(p->posX, p->posY, aviao.x, aviao.y) < 5){
            vidas -= 1; warning = 8; tempoNivel = 0;
            p->posY = win + LIXO; // Seta posição y fixa para remoção
            remover(&objetos, p->posX, win);
            if (vidas < 1){ 
                fimDeJogo = 1; // Jogo acaba se sim
            }
            else aviao.combustivel = 30;

        }

        // Checa se passou por posto de combustível
        if (p->tipo == 0 && dist(p->posX, p->posY, aviao.x, aviao.y) < 5 && combRecente == 0){
            float xAnimation = p->posX;
            float yAnimation = p->posY + 5.0;
            aviao.combustivel = (aviao.combustivel + 10) > 30 ? 30 : aviao.combustivel + 10;
            combRecente = 1;
            p->posY = win + LIXO; // Seta posição y fixa para remoção
            remover(&objetos, p->posX, win);
            inserirPos(&objetos, xAnimation, yAnimation, 4, width_wall);
        }


        // Checa se o objeto não passou da fronteira inferior da janela
        if (p->posY < -win-3.0)
            p->posY = win + LIXO; // Seta posição y fixa para remoção
            remover(&objetos, p->posX, win);

        p = p->prox;
    }
}

// Desenha objetos obstáulo
void desenharObjetos(){
    Objeto *p = objetos.inicio;

    while (p != NULL){
        if(p->posY != win + LIXO){
            if (p->tipo == 0)
                desenharPostoCombustivel(p->posX, p->posY);
            else if (p->tipo == 1)
                desenharHelicoptero(p->posX, p->posY, helicesRotacao);
            else if (p->tipo == 4)
                animacaoPostoCombustivel(p->posX, p->posY);
        }
        p = p->prox;
    }
}

// Define o que será mostrado na tela
void display(void){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // Limpa o buffer
    if (!fimDeJogo){ // Desenha objetos na tela

        char msgp[32] = "POINTS: ";
        sprintf(msgp, "%s %d", msgp, aviao.pontuacao);
        output(-win, win, msgp);

        char msgf[32] = "FUEL: ";
        sprintf(msgf, "%s %d", msgf, ((int)floor(aviao.combustivel*100/30)));
        output(-win, win-4.0, msgf);

        char msgn[32] = "LEVEL: ";
        sprintf(msgn, "%s %d", msgn, nivel);
        output(-win, win-8.0, msgn);

        char msgv[32] = "LIVES: ";
        sprintf(msgv, "%s %d", msgv, vidas);
        output(-win, -win + 4 , msgv);

        if(levelClearedMessage > 0){
            gameOver(-win/2, 5.0, "LEVEL CLEARED!");
        }

        glEnable(GL_TEXTURE_2D);
        desenhaParedeEsquerda(win, width_wall, texture_id1, scenicMove);
        desenhaParedeDireita(win, width_wall, texture_id1,scenicMove);
        desenhaAgua(win, width_wall, texture_id2,scenicMove);
        glDisable(GL_TEXTURE_2D);
        
        desenharObjetos();
        aeronave();

    }
    else{ // Tela azul
        if (auxTempo == 1.0){            
            inicializaAeronave();
            removerTudo(&objetos, win);
        }
        char msgp[32] = "POINTS: ";
        sprintf(msgp, "%s %d", msgp, ultimaPontuacao);
        gameOver(-win/2, -10, msgp);
        char msgh[32] = "HIGHSCORE: ";
        sprintf(msgh, "%s %d", msgh, highscore);
        gameOver(-win/2, 0, msgh);
        gameOver(-win/2, 10, "GAME OVER");
        if (auxTempo < 500){
            auxTempo += 1;
        }
        else{   
            auxTempo = 0;
            fimDeJogo = 0;
        }
    }
    glutSwapBuffers();
}

// Adiciona um tiro no vetor de tiros e seta a posição inicial dele
void controleTiros(){
    if (timerTiro < 1){
    aviao.tiros[contTiro].x = aviao.x;     // Mesmo x da da posição do aviao quando ele atirou
    aviao.tiros[contTiro].y = -win + 3.0;  // pra sair da beira do aviao
    contTiro = (contTiro + 1) % NUM_TIROS; // Troca de 10 para 30 porque se dermos tiros consecutivos sem parar porque
                                           // com % 10 eles somem no meio da tela
    timerTiro = intervaloTiro;
    }
    tiro = 1;
}

// Controle das setas
void controle(int key, int xx, int yy){
    switch (key)
    {
    case GLUT_KEY_UP:
        controleTiros();
        break;
    case GLUT_KEY_LEFT:
        if (aviao.x - 4 <= -win + width_wall + 0.5){
            vidas -= 1; warning = 8; tempoNivel = 0;
            if(vidas < 1) { fimDeJogo = 1;} // Jogo acaba se sim
            else{ 
                aviao.combustivel = 30;
                aviao.x += 4.0;
            }
        }
        else{
            aviao.x -= 1.3; // Movimenta o aviao para a esquerda
            aviao.rotX = aviao.rotX-3.5 <= -28 ? -28: aviao.rotX-3.5;
        }
        break;
    case GLUT_KEY_RIGHT:
        if (aviao.x + 4 >= win - width_wall - 0.5){
            vidas -= 1; warning = 8; tempoNivel = 0;
            if(vidas < 1){ fimDeJogo = 1; } // Jogo acaba se sim
            else{ 
                aviao.combustivel = 30;
                aviao.x -= 4.0;
            }
        }
        else{
            aviao.x += 1.3; // Movimenta o aviao para a direita
            aviao.rotX = aviao.rotX+3.5 >= 28 ? 28: aviao.rotX+3.5;
        }
        break;
    }
    glutPostRedisplay();
}

// Cria novos objetos na lista de objetos, a partir do limite superior da tela
void criarObjetosSecundarios(){
    // Cria considerando o intervalo de tempo controlado pelas variáveis tempoAuxHelicoptero e horaDoHelicoptero
    if (tempoAuxHelicoptero >= horaDoHelicoptero){
        inserir(&objetos, win, win - 2.0, 1, width_wall);
        tempoAuxHelicoptero = 0;
    }

    if (tempoAuxComb >= horaDoCombustivel){
        inserir(&objetos, win, win - 2.0, 0, width_wall);
        tempoAuxComb = 0;
    }
}

// Movimenta para baixo os objetos que não foram atingidos
void movimentarObjetosSecundarios(){
    Objeto *p = objetos.inicio;
    helicesRotacao += 20;

    while (p != NULL)
    {
        if (p->posY != (win + LIXO))
            p->posY -= 0.2;
            if (nivel > 2){
                p->posY -= (nivel-2)*0.05;
            }
        else{
            remover(&objetos, p->posX, win);
        }
        if(p->tipo == 4){
            p->TTL -= 1;
            if(p->TTL == 0){
                p->posY = (win + LIXO);
                remover(&objetos, p->posX, win);
            }
        }
        if(p->tipo ==1){
            if (p->posY<win){
                GLfloat newPosX = 0;
                if(!p->specialMov){
                    newPosX = p->posX + (0.075*(nivel-1));
                    if((p->movDist + (0.075*(nivel-1)) ) > (2+nivel) || p->posX >= (win- width_wall - 3.8)){
                        p->specialMov = 1;
                    }
                    else{
                        p->posX = newPosX;
                        p->movDist = p->movDist + (0.075*(nivel-1));
                    }
                }
                else{
                    newPosX = p->posX - (0.075*(nivel-1));
                    if(( (p->movDist - (0.075*(nivel-1)) ) < (-2-nivel)) || (p->posX <= (-win + width_wall + 3.8) )){
                        p->specialMov = 0;
                    }
                    else{
                        p->posX = newPosX;
                        p->movDist = p->movDist - (0.075*(nivel-1));
                    }
                }
            }
        }
        p = p->prox;
    }
}

// Executa a cada 10ms inicialmente, cria e movimenta os objetos, além de verificar a colisão
void movimentarPorTempo(){
    if(warning > 0) warning -= 1;
    if (levelClearedMessage > 0) levelClearedMessage -= 1;
    if (!fimDeJogo)
    {
        tempoAuxHelicoptero++;
        tempoAuxComb++;
        if(aviao.combustivel <= 0){
            vidas -= 1; warning = 8; tempoNivel = 0;
            
            if (vidas < 1){
                fimDeJogo = 1; 
            }
            else aviao.combustivel = 30;
        }

        else{
            if(timerTiro > 0){
                timerTiro = timerTiro - 1;
            }
            
            if(!(tempoAuxComb % 50)) aviao.combustivel--;
            if(!(tempoAuxComb % 100)) combRecente = 0;
                
            criarObjetosSecundarios();
            movimentarObjetosSecundarios();
            verificarColisao();

            if(aviao.rotX == auxRot) auxQtdRot++;
            else{
                auxQtdRot = 0;
                auxRot = aviao.rotX;
            }
            if(aviao.rotX != 0 && auxQtdRot >= 10){
                if(auxRot < 0)
                    aviao.rotX += 7;
                else
                    aviao.rotX -= 7;
            }

            if (tiro){
                int i;
                for (i = 0; i < NUM_TIROS; i++){
                    aviao.tiros[i].y += 1.6;
                    if (aviao.tiros[i].y > win + 5){
                        aviao.tiros[i].y = -win;
                        aviao.tiros[i].x = -win - 5.0;
                    }
                }
            }
            scenicMove = (scenicMove + 0.2);
            if(scenicMove>(win*1.25)) scenicMove = -win*1.25;    
        }
        tempoNivel += 1;
        if ((tempoNivel%(750+(nivel*25)))==0){
            tempoNivel = 0;
            if (nivel < 7){
                levelClearedMessage = 24;
                nivel += 1;
                aviao.pontuacao += 500;
                if (nivel > 2){
                    horaDoHelicoptero = intervaloEntreHelicopteros - ((nivel-2)*17);
                }
                if(nivel > 3){
                    horaDoCombustivel = intervaloDoCombustivel + ((nivel-3)*15);
                    
                }
            }
            else aviao.pontuacao += 100;
        }
    }
    glutPostRedisplay();
    glutTimerFunc(tempoRolagem, movimentarPorTempo, 1);
}

int main(int argc, char **argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);

    int i, msg_submenu, color_submenu;

    for (i = 1; i < argc; i++) {
        if (!strcmp(argv[i], "-mono")) {
        font = GLUT_BITMAP_9_BY_15;
        }
    }

    glutInitWindowSize(janelaX, janelaY);
    glutInitWindowPosition(300, 100);
    glutCreateWindow("River Raid 3D");
    init();

    CarregaTextura("grama.bmp", texture_id1);
    CarregaTextura("agua.bmp", texture_id2);

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

    glutDisplayFunc(display);
    glutSpecialFunc(controle);
    glutTimerFunc(tempoRolagem, movimentarPorTempo, 1);
    glutMainLoop();

    return 0;
}
