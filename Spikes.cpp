#include "Spikes.h"

Spike spikes[3];

Spike::Spike() {
    x = 0.0f;
    y = -0.5f;
    width = 0.06f;
    height = 0.1f;
}

Spike::Spike(float x_new, float y_new) {
    x = x_new;
    y = y_new;
    width = 0.06f;
    height = 0.1f;
}

// Draw spike as triangle
void Spike::draw() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
        glVertex2f(x, y);
        glVertex2f(x + width, y);
        glVertex2f(x + width / 2, y + height);
    glEnd();
}

// Move spike like platforms & coins
void Spike::moveLeft(float speed) {
    x -= speed;
    if (x < -1.2f) {
        x = 1.2f;
    }
}

// Initialize spikes on ground
void initSpikes() {
    spikes[0] = Spike(0.4f, -0.5f);
    spikes[1] = Spike(1.0f, -0.5f);
    spikes[2] = Spike(1.6f, -0.5f);
}

void drawSpikes() {
    for (int i = 0; i < 3; i++) {
        spikes[i].draw();
    }
}

void updateSpikes() {
    for (int i = 0; i < 3; i++) {
        spikes[i].moveLeft(0.005f); // same speed as platforms
    }
}

// Player–Spike collision
bool spikeCollision(float px, float py, float pw, float ph) {
    for (int i = 0; i < 3; i++) {
        bool collideX = px + pw > spikes[i].x &&
                        px < spikes[i].x + spikes[i].width;

        bool collideY = py < spikes[i].y + spikes[i].height &&
                        py + ph > spikes[i].y;

        if (collideX && collideY)
            return true;
    }
    return false;
}

