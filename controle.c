#include <stdio.h>
#include <GL/glut.h>
#include <string.h>
#include <math.h>

void *font = GLUT_BITMAP_9_BY_15;
char defaultMessage[] = "abcdefghijklmnop";
char *message = defaultMessage;

void
output(int x, int y, char *string)
{
  int len, i;

  glRasterPos3f(x, y, 10.0);
  len = (int) strlen(string);
  for (i = 0; i < len; i++) {
    glutBitmapCharacter(font, string[i]);
  }
}
