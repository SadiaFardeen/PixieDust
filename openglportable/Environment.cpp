#include "Environment.h"
#include <math.h>

Platform platforms[3];
float cloudOffset = 0.0f;

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

void drawCloud(float cx, float cy, float scale) {
    glColor3f(1.0f, 1.0f, 1.0f);
    float currentX = cx - cloudOffset;
    if (currentX < -1.5f) currentX += 3.0f;

    float x_offsets[] = {0.0f, 0.05f, -0.05f, 0.08f, -0.08f};
    float y_offsets[] = {0.0f, 0.02f, 0.01f, -0.01f, -0.01f};
    float sizes[] = {0.07f, 0.05f, 0.05f, 0.04f, 0.04f};

    for (int j = 0; j < 5; j++) {
        glBegin(GL_POLYGON);
        float r = sizes[j] * scale;
        float finalX = currentX + (x_offsets[j] * scale);
        float finalY = cy + (y_offsets[j] * scale);

        for (int i = 0; i < 360; i += 15) {
            float rad = i * 3.14159 / 180;
            glVertex2f(finalX + cos(rad) * r, finalY + sin(rad) * r);
        }
        glEnd();
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

    drawCloud(-0.5f, 0.7f, 1.2f);
    drawCloud(0.4f, 0.8f, 0.8f);
    drawCloud(0.9f, 0.6f, 1.0f);

    for (int i = 0; i < 3; i++) {
        platforms[i].draw();
    }
}

void updateEnvironment() {
    cloudOffset += 0.001f;
    if (cloudOffset > 3.0f) cloudOffset -= 3.0f;

    for (int i = 0; i < 3; i++) {
        platforms[i].moveLeft(0.005f);
    }
}
