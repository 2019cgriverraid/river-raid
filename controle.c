#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

void *font = GLUT_BITMAP_9_BY_15;
char defaultMessage[] = "abcdefghijklmnop";
char *message = defaultMessage;

void
gameOver(int x, int y, char *string){
  int len, i;
  glColor3f(1.0, 1.0, 1.0);
  glRasterPos3f(x, y, 15.0);
  len = (int) strlen(string);
  font = GLUT_BITMAP_TIMES_ROMAN_24;
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}
void
output(int x, int y, char *string)
{
  int len, i;
  glColor3f(1.0, 1.0, 1.0);
  font = GLUT_BITMAP_9_BY_15;
  glRasterPos3f(x, y, 15.0);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}
