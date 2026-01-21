#define GLUT_DISABLE_ATEXIT_HACK
#include <GL/glut.h>
#include "Player.h"
#include "Level.h"
#include <cstdio>
#include <windows.h>
#include <mmsystem.h>

Player player;
Level level;
int score = 0;

bool isGameOver = false;

bool keyLeft = false, keyRight = false;

void init() {
    glClearColor(0.5, 0.8, 1.0, 1.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 600);
    glMatrixMode(GL_MODELVIEW);
}

void renderText(float x, float y, const char* text, float r, float g, float b) {
    glColor3f(r, g, b);
    glRasterPos2f(x, y);
    for (const char* c = text; *c != '\0'; c++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);
    }
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glLoadIdentity();
    glPushMatrix();
    glTranslatef(-level.cameraX, 0, 0);

    level.draw(); // Draw clouds, trees, platforms, enemies
    if (!isGameOver) player.draw();

    glPopMatrix();

    // Draw UI (Static)
    // Reseting the matrix so the text stays fixed on the screen
    glLoadIdentity();

    // Score
    char scoreStr[50];
    sprintf(scoreStr, "Score: %d", score);
    renderText(20, 570, scoreStr, 0, 0, 0);

    // Game Over
    if (isGameOver) {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
        glColor4f(0, 0, 0, 0.7);
        glBegin(GL_QUADS);
            glVertex2f(0, 0); glVertex2f(800, 0);
            glVertex2f(800, 600); glVertex2f(0, 600);
        glEnd();
        glDisable(GL_BLEND);

        renderText(350, 350, "GAME OVER", 1, 0, 0);

        char finalScoreStr[50];
        sprintf(finalScoreStr, "Final Score: %d", score);
        renderText(340, 320, finalScoreStr, 1, 1, 1);

        renderText(300, 280, "Press 'R' to Restart", 1, 1, 0);
    }

    glutSwapBuffers();
}

void timer(int) {
    if (!isGameOver) {
        if (keyRight) player.moveRight();

        if (keyLeft) {
            if (player.x - (player.width / 2) > level.cameraX) { // Prevent going out of left frame
                player.moveLeft();
            }
        }

        player.update(level.platforms);
        level.update(player.x);

        score += level.checkCoinCollection(player.x, player.y, player.width, player.height);

        if (level.checkCollision(player.x, player.y, player.width, player.height)) {
            PlaySound(TEXT("dead.wav"), NULL, SND_FILENAME | SND_ASYNC);
            isGameOver = true;
        }
    }

    glutPostRedisplay();
    glutTimerFunc(1000/60, timer, 0); // roughly 16.6 milliseconds.
}

void keyboardDown(unsigned char key, int x, int y) {
    if (isGameOver) {
        if (key == 'r' || key == 'R') {
            // Reset Game
            player.x = 100; player.y = 200; player.velocityY = 0;
            level.cameraX = 0; score = 0; isGameOver = false;

            // Clear vectors
            level.platforms.clear(); level.coins.clear();
            level.enemies.clear(); level.shooters.clear();
            level.bullets.clear(); level.clouds.clear(); level.trees.clear();

            // Re-init
            level = Level();
        }
        return;
    }

    if (key == 'a') keyLeft = true;
    if (key == 'd') keyRight = true;
    if (key == 'w') player.jump();
    if (key == 's') player.duck(true);
}

void keyboardUp(unsigned char key, int x, int y) {
    if (key == 'a') keyLeft = false;
    if (key == 'd') keyRight = false;
    if (key == 's') player.duck(false);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Pixel Runner");

    init();

    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutKeyboardFunc(keyboardDown);
    glutKeyboardUpFunc(keyboardUp);

    glutMainLoop();
    return 0;
}
