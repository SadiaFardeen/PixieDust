#include "Coins.h"
#include <math.h>

Coin coins[3];

Coin::Coin(float x_new, float y_new) {
    x = x_new;
    y = y_new;
    size = 0.04f;
    isCollected = false;
}

void Coin::draw() {
    if (isCollected) return;

    glColor3f(1.0f, 0.8f, 0.0f);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 360; i++) {
        float rad = i * 3.14159 / 180;
        glVertex2f(x + cos(rad) * size, y + sin(rad) * size);
    }
    glEnd();
}

void Coin::moveLeft(float speed) {
    x -= speed;
    if (x < -1.2f) {
        x = 1.2f;
        isCollected = false;
    }
}

void initCoins() {
    coins[0] = Coin(-0.3f, -0.3f);
    coins[1] = Coin(0.6f, 0.0f);
    coins[2] = Coin(1.5f, 0.4f);
}

void drawCoins() {
    for (int i = 0; i < 3; i++) {
        coins[i].draw();
    }
}

void updateCoins() {
    for (int i = 0; i < 3; i++) {
        coins[i].moveLeft(0.005f);
    }
}
