#ifndef LEVEL_H
#define LEVEL_H

#include "shapes.h"
#include <vector>

class Level {
public:
    std::vector<GameObject> platforms;
    std::vector<GameObject> coins;
    std::vector<GameObject> enemies;
    std::vector<GameObject> shooters;
    std::vector<Bullet> bullets;
    std::vector<Cloud> clouds;

    // For Trees
    std::vector<Tree> trees;

    float cameraX;
    float worldEndX;

    Level();
    void update(float playerX);
    void draw();
    void drawCloudShape(float x, float y, float scale);

    void drawTreeShape(float x, float y, float scale);

    void generateChunk(float startX);
    bool checkCollision(float px, float py, float pw, float ph);
    int checkCoinCollection(float px, float py, float pw, float ph);

private:
    void initClouds();
    void initTrees();
};

#endif
