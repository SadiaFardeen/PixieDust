#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "collisionDetection.cpp"
#include "EShoot.cpp"
#include "player.cpp"
#include "ground_spikes.cpp"

float r = 1.0, g = 1.0, b = 1.0;

void display() {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    drawGround();           // Scrolling ground
    drawSpikes();           // Moving spikes
    drawPlayer();           // Main character

    // Test rectangle (optional - can be removed later)
    if (collision(playerRect(), getTestRect())) {
        r = 1.0; g = 0.0; b = 0.0;
    }
    else {
        r = 1.0; g = 1.0; b = 1.0;
    }
    Rectangle0(-200, -100, 100, 100, r, g, b);

    EnemyShooter(180, 50);  // Enemy shooter

    glutSwapBuffers();
    glutPostRedisplay();
}

void keyboardInput(unsigned char key, int x, int y) {
    // Player movement (WASD or arrows later)
    if (key == 'd' || key == 'D') player.x += 8;
    if (key == 'a' || key == 'A') player.x -= 8;
    if (key == ' ') {         // Jump
        if (!player.isJumping && !player.isDead) {
            player.velocityY = JUMP_VELOCITY;
            player.isJumping = true;
        }
    }

    glutPostRedisplay();
}

int winW = 800, winH = 600;

void reshape(int w, int h) {
    glViewport(0, 0, winW, winH);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-winW / 2, winW / 2, -winH / 2, winH / 2);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitWindowSize(winW, winH);
    glutCreateWindow("2D Side Scroller Game");

    initSpikes();           // Initialize some spikes

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboardInput);

    // Timers
    glutTimerFunc(16, updatePlayer, 0);
    glutTimerFunc(16, updateSpikes, 0);
    glutTimerFunc(16, updateBullet, 0);
    glutTimerFunc(1500, createBullet, 0);

    glutMainLoop();
    return 0;
}
