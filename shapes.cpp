#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#define M_PI 3.14159265358979323846

void bresenhamCircle(int a, int b, int r, float rColor, float gColor, float bColor) {
    int x = 0;
    int y = r;
    int d = 3 - 2 * r;

    glBegin(GL_POLYGON);
    glColor3f(rColor, gColor, bColor);
    while (x <= y) {
        glVertex2d(x + a, y + b);
        glVertex2d(-x + a, -y + b);
        glVertex2d(x + a, -y + b);
        glVertex2d(-x + a, y + b);
        glVertex2d(y + a, x + b);
        glVertex2d(-y + a, -x + b);
        glVertex2d(-y + a, x + b);
        glVertex2d(y + a, -x + b);

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

void Rectangle0(int x, int y, int width, int height, float r, float g, float b) {
    glBegin(GL_POLYGON);
    glColor3f(r, g, b);
    glVertex2d(x, y);
    glVertex2d(x + width, y);
    glVertex2d(x + width, y + height);
    glVertex2d(x, y + height);
    glEnd();
}

// You can keep your other shape functions (RectangleM, Ellipse, etc.)