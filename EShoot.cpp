#include <windows.h>
#include <GL/glut.h>
#include <math.h>
#include "shapes.cpp"
#include <algorithm>

const float SPEED = 0.8f;// Bullet Movement speed
const float DESTROY_X = 300.0f;
float bulletPosX, bulletPosY;

// Bullet Struct
struct Bullet {
   float x;
   float y;
   float radius;
};

std::vector<Bullet> bullets;

// Update Bullet Movement
void updateBullet(int value) {
   for (int i = 0; i < bullets.size(); i++) {
      bullets[i].x -= SPEED;
   }

   // Remove bullets that reached destination
   bullets.erase(
      std::remove_if(bullets.begin(), bullets.end(),
         [](Bullet c) { return c.x <= bulletPosX-DESTROY_X; }),
      bullets.end()
   );

   glutPostRedisplay();
   glutTimerFunc(16, updateBullet, 0); // ~60 FPS
}

// Create Bullet Every 1 Second
void createBullet(int value) {
   Bullet c;
   c.x = bulletPosX;
   c.y = bulletPosY;
   c.radius = 5;

   bullets.push_back(c);

   glutTimerFunc(1500, createBullet, 0); // every 1.5 second
}


void EnemyShooter(float x, float y) {
   bresenhamCircle(x + 10, y + 30, 7, 1, 0, 0); // Head
   RectangleM(x + 10, y + 18, 7, 15, 1, 0, 0); // Body
   RectangleM(x + 3, y + 18, 28, 4, 1, 0, 0); // Gun
   RectangleM(x + 8, y + 6, 2, 12, 1, 0, 0); // Left Leg
   RectangleM(x + 12, y + 6, 2, 12, 1, 0, 0); // Right Leg
   bulletPosX = x;
   bulletPosY = y;

   for (auto &c : bullets) {
      bresenhamCircle(c.x-15, c.y+18, c.radius, 1, 1, 1);
   }
}
