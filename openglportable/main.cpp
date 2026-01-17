#include <GL/glut.h>
#include "Triangle.h"

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    DrawTriangle();

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitWindowSize(640, 360);
    glutCreateWindow("OpenGL 64bit");
    glutDisplayFunc(display);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}
