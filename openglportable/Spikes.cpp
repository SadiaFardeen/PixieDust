#include "Spikes.h"
#include "Collision.h"

std::vector<Spike> spikes;

Spike::Spike(float xPos, float yPos) {
    x = xPos;
    y = yPos;
    width = 0.08f;
    height = 0.12f;
}

void Spike::draw() {
    glColor3f(1.0f, 0.0f, 0.0f);
    glBegin(GL_TRIANGLES);
    glVertex2f(x, y);
    glVertex2f(x + width, y);
    glVertex2f(x + width / 2.0f, y + height);
    glEnd();
}

void Spike::moveLeft(float speed) {
    x -= speed;
}

void initSpikes() {
    spikes.clear();
    spikes.push_back(Spike(0.8f, -0.3f));
}

void drawSpikes() {
    for (auto &s : spikes)
        s.draw();
}

void updateSpikes() {
    for (auto &s : spikes) {
        s.moveLeft(0.01f);
        if (s.x < -1.0f)
            s.x = 1.0f;
    }
}

bool spikeCollision(float px, float py, float pw, float ph) {
    for (auto &s : spikes) {
        if (checkAABBCollision(
            px, py, pw, ph,
            s.x, s.y, s.width, s.height
        )) {
            return true;
        }
    }
    return false;
}
