#include <GL/glut.h>
#include <vector>
#include <cstdlib>
#include <ctime>
#include "collisionDetection.cpp"

const float GROUND_Y = -200.0f;
const float SCROLL_SPEED = 1.8f;

struct Spike {
    float x;
    float y = GROUND_Y;
    float width = 28;
    float height = 45;
};

std::vector<Spike> spikes;
float groundOffset = 0.0f;

void initSpikes() {
    srand(time(0));
    // Initial spikes
    for (int i = 0; i < 6; i++) {
        Spike s;
        s.x = 200 + i * 220 + (rand() % 80);
        spikes.push_back(s);
    }
}

void drawGround() {
    groundOffset -= SCROLL_SPEED;
    if (groundOffset <= -800) groundOffset = 0;

    glBegin(GL_POLYGON);
    glColor3f(0.4, 0.25, 0.1); // brown ground
    glVertex2d(groundOffset - 800, -300);
    glVertex2d(groundOffset + 1600, -300);
    glVertex2d(groundOffset + 1600, GROUND_Y);
    glVertex2d(groundOffset - 800, GROUND_Y);
    glEnd();

    // Grass layer on top
    glBegin(GL_POLYGON);
    glColor3f(0.1, 0.6, 0.1);
    glVertex2d(groundOffset - 800, GROUND_Y - 2);
    glVertex2d(groundOffset + 1600, GROUND_Y - 2);
    glVertex2d(groundOffset + 1600, GROUND_Y + 8);
    glVertex2d(groundOffset - 800, GROUND_Y + 8);
    glEnd();
}

void drawSpikes() {
    for (auto& s : spikes) {
        s.x -= SCROLL_SPEED;  // move with ground

        // Recycle when off screen
        if (s.x + s.width < -400) {
            s.x = 400 + (rand() % 120);
        }

        glBegin(GL_TRIANGLES);
        glColor3f(0.7, 0.7, 0.7); // silver/gray spikes
        glVertex2d(s.x, s.y);
        glVertex2d(s.x + s.width, s.y);
        glVertex2d(s.x + s.width / 2, s.y + s.height);
        glEnd();
    }
}

void updateSpikes(int value) {
    glutPostRedisplay();
    glutTimerFunc(16, updateSpikes, 0);
}

// Helper for collision (used in player.cpp)
Rect getTestRect() {  // optional test rect
    return { -100, -100, 100, 100 };
}