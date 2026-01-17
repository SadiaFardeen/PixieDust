#include <GL/glut.h>

void DrawTriangle() {
    glBegin(GL_POLYGON);
        glColor3f(0, 0, 1);
        glVertex2f(0.5, -0.5);

        glColor3f(0, 1, 0);
        glVertex2f(-0.5, -0.5);

        glColor3f(0, 1, 1);
        glVertex2f(-0.5, 0.5);
    glEnd();
}
