#include "Environment.h"

Platform platforms[3];

Platform::Platform(float l, float r, float t, float b, float rd, float gn, float bl) {
    left = l; right = r; top = t; bottom = b;
    red = rd; green = gn; blue = bl;
}

void Platform::draw() {
    glColor3f(red, green, blue);
    glBegin(GL_POLYGON);
        glVertex2f(left, top);
        glVertex2f(left, bottom);
        glVertex2f(right, bottom);
        glVertex2f(right, top);
    glEnd();
}

void Platform::moveLeft(float speed) {
    left -= speed;
    right -= speed;
    if (right < -1.2f) {
        float width = right - left;
        left = 1.2f;
        right = left + width;
    }
}

void initEnvironment() {
    platforms[0] = Platform(-0.6f, 0.0f, -0.4f, -0.5f, 0.4f, 0.2f, 0.0f);
    platforms[1] = Platform(0.3f, 0.9f, -0.1f, -0.2f, 0.5f, 0.3f, 0.1f);
    platforms[2] = Platform(1.2f, 1.8f, 0.3f, 0.2f, 0.4f, 0.2f, 0.0f);
}

void drawEnvironment() {
    glBegin(GL_QUADS);
        glColor3f(0.4f, 0.6f, 1.0f);
        glVertex2f(-1.0f, 1.0f);
        glVertex2f(1.0f, 1.0f);
        glColor3f(1.0f, 1.0f, 1.0f);
        glVertex2f(1.0f, -1.0f);
        glVertex2f(-1.0f, -1.0f);
    glEnd();

    for (int i = 0; i < 3; i++) {
        platforms[i].draw();
    }
}

void updateEnvironment() {
    for (int i = 0; i < 3; i++) {
        platforms[i].moveLeft(0.005f);
    }
}
