#include <GL/glut.h>

struct Rect {
    float x;
    float y;
    float width;
    float height;
};

bool collision(const Rect& a, const Rect& b) {
    bool collisionX = a.x + a.width > b.x && b.x + b.width > a.x;
    bool collisionY = a.y + a.height > b.y && b.y + b.height > a.y;
    return collisionX && collisionY;
}