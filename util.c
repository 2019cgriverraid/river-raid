#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>

#define NUM_TIROS 30
#define pi (3.14159265/360.0)

typedef struct Tiros{
    float x;
    float y;
    int naTela;
}Tiros;

typedef struct Aeronave{
  GLfloat x;
  GLfloat y;
  GLfloat rotX;
  GLfloat rotY;
  Tiros tiros[30];
}Aeronave;

typedef struct Coordenadas{
  GLfloat panX;
  GLfloat panY;
}Coordenadas;

/*
typedef struct Objeto{
  GLfloat posX;
  GLfloat posY;
  int id;
  int tipo;
  struct Objeto *prox;
}Objeto;

typedef struct Lista{
  struct Objeto *inicio, *fim;
}Lista;

void inicializaLista(Lista *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
}

int verificaUnicidadeCoordenadas(Lista *lista, float x, float y){
  //verificar se o mesmo objeto nao esta sendo colocado no mesmo lugar que outro já existente
  //talvez seja bom considerar se ele não está em um lugar muito próximo, inclusive

  //return 1 //se for única
  //return 0 //caso contrário
}

void insere(Lista *lista, int winX, int winY){
  struct Objeto *novo = malloc(sizeof(Objeto));
  novo->prox = NULL;

  do {
    //id pode ser a tupla da posição:
    novo->posX = rand() % (2*winX) - winX; //reconsiderar quando as paredes forem corretamente desenhadas
    novo->posY = rand() % (2*winY) - winY;
    //novo->tipo = //será definido o tipo do objeto, para que saibamos qual é a dimensão considerada para a colisão
  }while(verificaUnicidadeCoordenadas(lista, novo->posX, novo->posY));
  
  if(lista->inicio == NULL)
    lista->inicio = novo;
  else
    lista->fim->prox = novo;
  lista->fim = novo;
}

void remove(Lista *lista){

}*/

float dist(GLfloat px, GLfloat py, GLfloat qx, GLfloat qy){
    printf("px %2f qx %2f py %2f qy %2f \n", px, qx, py, qy);
    return sqrt(pow((px - qx), 2) + pow((py - qy), 2));
}