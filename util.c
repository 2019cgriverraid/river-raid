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
  Tiros tiros[NUM_TIROS];
}Aeronave;

typedef struct Coordenadas{
  GLfloat panX;
  GLfloat panY;
}Coordenadas;

typedef struct Objeto{
  GLfloat posX;
  GLfloat posY;
  int id;
  int tipo;
  struct Objeto *prox, *ant;
}Objeto;

typedef struct Lista{
  struct Objeto *inicio, *fim;
}Lista;

// Inicializa a lista com NULL
void inicializarLista(Lista *lista){
  lista->inicio = NULL;
  lista->fim = NULL;
}

// Imprime lista para conferência, auxiliar
void imprimeLista(Lista *lista){
  Objeto *p = lista->inicio;
  while(p!=NULL){
    printf("(%.2f, %.2f)\n", p->posX, p->posY);
    p = p->prox;
  }
}

// Verificar se o mesmo objeto nao esta sendo colocado no mesmo lugar que outro já existente
int verificarUnicidadeCoordenadas(Lista *lista, float x, float y){

  if(lista->inicio != NULL){
    Objeto *percorre = lista->inicio;
    while(percorre != NULL){
      if(percorre->posX == x && percorre->posY == y){
        return 0; //já existe objeto com a mesma posição (é meio impossivel, função tá inutil)
      }
      percorre = percorre->prox;
    }
  }
  return 1; //posição é unica

}

// Insere um novo objeto na lista
void inserir(Lista *lista, int winX, int winY, int width_wall){
  struct Objeto *novo = malloc(sizeof(Objeto));
  novo->prox = NULL;

  do{
    novo->posX = (rand() % (2*winX - 2*width_wall)) - winX + width_wall; //calcula pra setar uma posição x aleatória dentro da parte azul
    novo->posY = winY;
    //novo->tipo = //será definido o tipo do objeto, para que saibamos qual é a dimensão considerada para a colisão
  }while(!verificarUnicidadeCoordenadas(lista, novo->posX, novo->posY));
  
  if(lista->inicio == NULL){
    novo->ant = NULL;
    lista->inicio = novo;
  }
  else{
    novo->ant = lista->fim;
    lista->fim->prox = novo;
  }
  lista->fim = novo;
  imprimeLista(lista);
}

// Remove o objeto que tem as posições enviadas por parâmetro da lista de objetos
void remover(Lista *lista, int posX, int posY){
  if(lista->inicio != NULL){
    Objeto *percorre = lista->inicio;

    while(percorre != NULL){ //procura o objeto para remoção
      if(percorre->posX == posX && percorre->posY == 37.0){
        percorre->ant->prox = percorre->prox;
        percorre->prox->ant = percorre->ant;
        free(percorre);
        return;
      }
      percorre = percorre->prox;
    }
  }
}

// Calcula a distância entre dois pontos (px, py) e (qx, qy)
float dist(GLfloat px, GLfloat py, GLfloat qx, GLfloat qy){
    //printf("px %2f py %2f qx %2f qy %2f \n", px, py, qx, qy);
    //printf("dist %f\n", sqrt(pow((px - qx), 2) + pow((py - qy), 2)) );
    return sqrt(pow((px - qx), 2) + pow((py - qy), 2));
}