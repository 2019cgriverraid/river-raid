#include <GL/glut.h>
#include <math.h>
#include <stdlib.h>
#include <time.h> 


#define NUM_TIROS 4
#define LIXO 20.0 
#define pi (3.14159265 / 360.0)

typedef struct Tiros
{
    float x;
    float y;
    int naTela;
} Tiros;

typedef struct Aeronave
{
    GLfloat x;
    GLfloat y;
    GLfloat rotX;
    GLfloat rotY;
    Tiros tiros[NUM_TIROS];

    GLint combustivel;
    GLint pontuacao;
} Aeronave;

typedef struct Objeto
{
    GLfloat posX;
    GLfloat posY;
    GLfloat specialMov;
    GLfloat movDist;
    int id;
    int tipo;
    struct Objeto *prox, *ant;
} Objeto;

typedef struct Lista
{
    struct Objeto *inicio, *fim;
} Lista;

// Inicializa a lista com NULL
void inicializarLista(Lista *lista)
{
    lista->inicio = NULL;
    lista->fim = NULL;
}

// Imprime lista para conferência, auxiliar
void imprimeLista(Lista *lista)
{
    Objeto *p = lista->inicio;
    while (p != NULL)
    {
        printf("(%.2f, %.2f)\n", p->posX, p->posY);
        p = p->prox;
    }
}
// Calcula a distância entre dois pontos (px, py) e (qx, qy)
float dist(GLfloat px, GLfloat py, GLfloat qx, GLfloat qy)
{
    //printf("px %2f py %2f qx %2f qy %2f \n", px, py, qx, qy);
    //printf("dist %f\n", sqrt(pow((px - qx), 2) + pow((py - qy), 2)) );
    return sqrt(pow((px - qx), 2) + pow((py - qy), 2));
}
// Verificar se o mesmo objeto nao esta sendo colocado no mesmo lugar que outro já existente
int verificarUnicidadeCoordenadas(Lista *lista, float x, float y)
{

    if (lista->inicio != NULL)
    {
        Objeto *p = lista->inicio;
        while (p != NULL)
        {
            if (dist(p->posX, p->posY, x, y)<5.0)
            {
                return 0; //já existe objeto com a mesma posição (é meio impossivel, função tá inutil)
            }
            p = p->prox;
        }
    }
    return 1; //posição é unica
}

// Insere um novo objeto na lista
void inserir(Lista *lista, int winX, int winY, int tipo, int width_wall)
{

    struct Objeto *novo = malloc(sizeof(Objeto));
    novo->prox = NULL;
    novo->tipo = tipo;

    do
    {
        srand(time(NULL)); 
        novo->posX = (rand() % ( (2 * winX) - (2 * width_wall) - 8) ) - winX + width_wall + 4.0; //calcula pra setar uma posição x aleatória dentro da parte azul
        novo->posY = winY+13.0;
        novo -> specialMov = 0.0;
        novo -> movDist = 0.0;
        //novo->tipo = //será definido o tipo do objeto, para que saibamos qual é a dimensão considerada para a colisão
    } while (!verificarUnicidadeCoordenadas(lista, novo->posX, novo->posY));

    if (lista->inicio == NULL)
    {
        novo->ant = NULL;
        lista->inicio = novo;
    }
    else
    {
        novo->ant = lista->fim;
        lista->fim->prox = novo;
    }
    lista->fim = novo;
    imprimeLista(lista);
}

// Remove o objeto que tem as posições enviadas por parâmetro da lista de objetos
void remover(Lista *lista, GLfloat posX, int winY)
{
    if (lista->inicio != NULL)
    {
        Objeto *p = lista->inicio;
        imprimeLista(lista);
        while (p != NULL)
        { //procura o objeto para remoção
            if ((p->posX == posX) && (p->posY == winY+LIXO))
            {
                printf("remover %2f %2f \n", posX, p->posX);
                if (p->ant != NULL)
                {
                    p->ant->prox = p->prox;
                   
                }
                if(p->prox != NULL){
                     p->prox->ant = p->ant;
                }
                if (p == lista->inicio){
                    if(p->prox != NULL)
                        lista->inicio = p->prox;
                    else{
                        lista->inicio = NULL;
                        lista->fim = NULL;
                    }

                }
                free(p);
                return;
            }
            p = p->prox;
        }
        imprimeLista(lista);
    }
    
}

void removerTudo(Lista *lista, int winY)
{
    Objeto *p = lista->inicio;
    while (p != NULL)
    {
        p->posY = winY + LIXO;
        remover(lista, p->posX, winY);
        p = p->prox;
    }
    lista->inicio = NULL;
    lista->fim = NULL;
}