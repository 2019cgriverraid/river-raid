#include <stdio.h>
#include <GL/glut.h>
#include <math.h>

struct Coordenadas acionarSetas(int key, GLfloat panX, GLfloat panY, int win){
  switch(key){
//    case GLUT_KEY_UP:
//      panY += 1;
//      break;
//    case GLUT_KEY_DOWN:
//      panY -= 1;
//      break;
    case GLUT_KEY_RIGHT:
      if(panX+4<win) panX += 1;
      break;
    case GLUT_KEY_LEFT:
      if(panX-4>-win) panX -= 1;
      break;
  }
  struct Coordenadas coordenadas = { .panX = panX, .panY = panY };
  return coordenadas;
}

GLfloat acionarLetra(unsigned char key, GLfloat anglex){
  switch(key){
    case '4':
      anglex += 5;
      break;
    case '6':
      anglex -= 5;
      break;
    default:
      break;
  }
  return anglex;
}