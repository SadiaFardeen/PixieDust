#include "shapes.h"
#include <GL/glut.h>
#include <math.h>

void RectangleM(float x, float y, float width, float height, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_POLYGON);
    glVertex2f(x - width / 2, y - height / 2);
    glVertex2f(x + width / 2, y - height / 2);
    glVertex2f(x + width / 2, y + height / 2);
    glVertex2f(x - width / 2, y + height / 2);
    glEnd();
}

void Circle(float a, float b, float r, float rColor, float gColor, float bColor) {
   float x = 0;
   float y = r;
   float d = 3 - 2 * r;

   glBegin(GL_POLYGON);
   glColor3f(rColor, gColor, bColor);
   while (x <= y) {
      glVertex2d(x+a, y+b);
      glVertex2d(-x+a, -y+b);
      glVertex2d(x+a, -y+b);
      glVertex2d(-x+a, y+b);
      glVertex2d(y+a, x+b);
      glVertex2d(-y+a, -x+b);
      glVertex2d(-y+a, x+b);
      glVertex2d(y+a, -x+b);

      if (d < 0) {
         d = d + 4 * x + 6;
      }
      else {
         d = d + 4 * (x - y) + 10;
         y--;
      }
      x++;
   }
   glEnd();
}

void Triangle(float x1, float y1, float x2, float y2, float x3, float y3, float r, float g, float b) {
    glColor3f(r, g, b);
    glBegin(GL_TRIANGLES);
    glVertex2f(x1, y1);
    glVertex2f(x2, y2);
    glVertex2f(x3, y3);
    glEnd();
}
