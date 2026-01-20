#include <GL/glut.h>
#include "Environment.h"
#include "Coins.h"
#include "player.h"

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawEnvironment();
    drawCoins();
    drawHead();
    drawBody();
    drawShoes();

    glutSwapBuffers();
}

void timer(int value) {
    updateEnvironment();
    updateCoins();

    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(640, 360);
    glutCreateWindow("PixeDust");

    initEnvironment();
    initCoins();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard);
    glutTimerFunc(0, timer, 0);
    glutTimerFunc(0, update, 0);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glutMainLoop();
    return 0;
}

