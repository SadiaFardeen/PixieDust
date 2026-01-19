#include <windows.h>
#include <GL/glut.h>

// include cpp files (as you are using now)
#include "collisionDetection.h"
#include "shapes.cpp"
#include "player.cpp"
#include "ground_spikes.cpp"
#include "EShoot.cpp"

// ------------------- DISPLAY -------------------
void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGround();
    drawSpikes();
    drawPlayer();

    EnemyShooter(180, 50);   // enemy position

    glutSwapBuffers();
}

// ------------------- KEYBOARD -------------------
void keyboard(unsigned char key, int x, int y) {
    if (player.isDead) return;

    switch (key) {
    case 'a':
    case 'A':
        player.x -= 8;
        break;

    case 'd':
    case 'D':
        player.x += 8;
        break;

    case ' ':
        if (!player.isJumping) {
            player.velocityY = 14.0f;
            player.isJumping = true;
        }
        break;
    }
}

// ------------------- INIT -------------------
void init() {
    glClearColor(0.6f, 0.8f, 1.0f, 1.0f); // sky blue

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    // 2D camera
    gluOrtho2D(-400, 400, -300, 300);

    initSpikes();
}

// ------------------- MAIN -------------------
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pixel Dash");

    init();

    glutDisplayFunc(display);
    glutKeyboardFunc(keyboard);

    // timers (game loop)
    glutTimerFunc(16, updatePlayer, 0);
    glutTimerFunc(16, updateSpikes, 0);
    glutTimerFunc(16, updateBullet, 0);
    glutTimerFunc(1500, createBullet, 0);

    glutMainLoop();
    return 0;
}

