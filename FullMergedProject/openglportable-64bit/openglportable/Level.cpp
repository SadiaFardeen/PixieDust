#include "Level.h"
#include "shapes.h"
#include <cstdlib>
#include <windows.h>
#include <mmsystem.h>
#include <algorithm> // To sort the trees for parallax effect

Level::Level() {
    cameraX = 0;
    worldEndX = 0;

    initClouds();
    initTrees();

    generateChunk(worldEndX);
    generateChunk(worldEndX);
}

void Level::initClouds() {
    int numClouds = 8;
    for (int i = 0; i < numClouds; i++) {
        Cloud c;
        c.x = rand() % 1600;
        c.y = 400 + (rand() % 180);
        c.speed = 0.5f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 1.0f));
        c.scale = 0.8f + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / 0.7f));
        clouds.push_back(c);
    }
}

// Initialize random trees with varying depth
void Level::initTrees() {
    int numTrees = 15;
    for (int i = 0; i < numTrees; i++) {
        Tree t;
        t.x = rand() % 1600;

        float depth = static_cast<float>(rand()) / static_cast<float>(RAND_MAX);

        t.y = 60 + (depth * 60);
        t.scale = 1.3f - (depth * 0.6f);
        t.speed = 0.2f + (depth * 0.6f);

        trees.push_back(t);
    }

    std::sort(trees.begin(), trees.end(), [](const Tree& a, const Tree& b) {
        return a.scale < b.scale; // Draw small (far) trees first
    });
}

void Level::drawCloudShape(float x, float y, float scale) {
    float r = 0.95f, g = 0.95f, b = 1.0f;
    float baseRadius = 30 * scale;
    Circle(x, y, baseRadius, r, g, b);
    Circle(x - baseRadius * 0.8f, y - baseRadius * 0.3f, baseRadius * 0.7f, r, g, b);
    Circle(x + baseRadius * 0.8f, y - baseRadius * 0.3f, baseRadius * 0.7f, r, g, b);
}

// Draw trees
void Level::drawTreeShape(float x, float y, float scale) {
    float leafRadius = 45 * scale;
    float trunkW = 24 * scale;

    // Calculate the top of the trunk
    float trunkTopY = y + (70 * scale);
    float trunkBottomY = 0;

    float totalTrunkHeight = trunkTopY - trunkBottomY;
    float trunkCenterY = trunkBottomY + (totalTrunkHeight / 2.0f);

    // Tree Colors
    float tR = 0.4f, tG = 0.25f, tB = 0.1f; // Brown
    float lR = 0.1f, lG = 0.45f, lB = 0.1f; // Dark Green

    // Draw Trunks
    // Centered at trunkCenterY, with the calculated full height
    RectangleM(x, trunkCenterY, trunkW, totalTrunkHeight, tR, tG, tB);

    // Leafs
    Circle(x, trunkTopY + leafRadius * 0.1f, leafRadius, lR, lG, lB);
    Circle(x - leafRadius * 0.6f, trunkTopY - leafRadius * 0.3f, leafRadius * 0.8f, lR*0.9f, lG*0.9f, lB*0.9f);
    Circle(x + leafRadius * 0.6f, trunkTopY - leafRadius * 0.3f, leafRadius * 0.8f, lR*0.9f, lG*0.9f, lB*0.9f);
}

void Level::generateChunk(float startX) {
    // Generate the Main Ground
    GameObject ground = {startX + 400, 25, 800, 50, true, 0};
    platforms.push_back(ground);

    worldEndX += 800;

    // Calculate Difficulty Scaling
    // The further you travel (startX), the harder the game gets.
    // Every 1000 pixels traveled, add +2% spawn chance.
    int difficultyBonus = (int)(startX / 1000) * 2;

    // Cap the bonus at +40% so the game doesn't become impossible (Total max 60% spikes).
    if (difficultyBonus > 40) difficultyBonus = 40;

    // Calculate probability thresholds dynamically:
    // Base Spike Chance: 20% + Bonus
    int spikeThreshold = 20 + difficultyBonus;

    // Shooter Chance: Scales relative to spikes.
    // If spikes are 0-30%, shooters might be 30-40%.
    int shooterThreshold = spikeThreshold + 10 + difficultyBonus;


    // Segmented Platform Generation
    int numSegments = 4;
    float segmentWidth = 800.0f / numSegments;

    for (int i = 0; i < numSegments; i++) {
        // Calculate the start X of the current segment strip
        float segmentStart = startX + (i * segmentWidth);

        // Randomize X position WITHIN this segment.
        // We add +20 and subtract -40 padding so platforms don't touch the segment edges.
        float rx = segmentStart + 20 + (rand() % (int)(segmentWidth - 40));

        // Randomize Height (Y) between 100 and 250 pixels high.
        float ry = 100 + (rand() % 150);

        // Create the Floating Platform
        GameObject p = {rx, ry, 100, 20, true, 0};
        platforms.push_back(p);

        // Add a Coin floating above the platform
        GameObject c = {rx, ry + 30, 15, 15, true, 0};
        coins.push_back(c);

        // Enemy Spawning Logic
        int chance = rand() % 100; // Roll a number between 0 and 99

        if (chance < spikeThreshold) {
            // Spawn Static Spike Enemy
            GameObject e = {rx, ry + 25, 30, 30, true, 0};
            enemies.push_back(e);

            // Remove any coins inside the spikes
            coins.pop_back();
        }
        else if (chance >= spikeThreshold && chance < shooterThreshold) {
            // Spawn Shooter Enemy
            // This runs only if we missed the spike roll but hit the shooter roll.
            GameObject s = {rx, ry + 25, 30, 30, true, 0};
            shooters.push_back(s);

            // Remove the coin here too.
            coins.pop_back();
        }
        // If neither check passes, the platform stays safe with just a coin.
    }
}

void Level::update(float playerX) {
    // Old Camera Position
    float oldCameraX = cameraX;

    // Update Camera
    if (playerX > cameraX + 300) {
        cameraX = playerX - 300;
    }

    // Calculate how much the camera moved this frame
    float cameraDx = cameraX - oldCameraX;

    // World Generation
    if (playerX + 1000 > worldEndX) {
        generateChunk(worldEndX);
    }

    // Update Clouds
    for (auto &c : clouds) {
        c.x -= c.speed;
        if (c.x + (50 * c.scale) < cameraX) {
            c.x = cameraX + 850 + (rand() % 200);
            c.y = 400 + (rand() % 180);
        }
    }

    // Update Trees
    for (auto &t : trees) {
        //
        // to create the parallax effect
        t.x += cameraDx * t.speed;

        // Wrap around the trees for reuse
        if (t.x + (100 * t.scale) < cameraX) {
            // Move it to the right side of the screen
            t.x = cameraX + 850 + (rand() % 300);
        }
    }

    // Update Shooters
    for (size_t i = 0; i < shooters.size(); i++) {
        if (!shooters[i].active) continue;
        if (shooters[i].x > cameraX && shooters[i].x < cameraX + 800) {
            shooters[i].timer++;
            if (shooters[i].timer > 60) {
                shooters[i].timer = 0;
                Bullet b = {shooters[i].x - 20, shooters[i].y, 7.0f, true};
                bullets.push_back(b);
            }
        }
    }

    // Update Bullets
    for (size_t i = 0; i < bullets.size(); i++) {
        if (bullets[i].active) {
            bullets[i].x -= bullets[i].speed;
            if (bullets[i].x < cameraX) bullets[i].active = false;
        }
    }
}

void Level::draw() {
    // Draw Clouds
    for (const auto &c : clouds) drawCloudShape(c.x, c.y, c.scale);

    // Draw Trees
    for (const auto &t : trees) drawTreeShape(t.x, t.y, t.scale);

    // Draw Game World
    for (auto &p : platforms) {
        RectangleM(p.x, p.y, p.w, p.h, 0.2, 0.8, 0.2);
        RectangleM(p.x, p.y + p.h/2 - 2, p.w, 4, 0.1, 0.6, 0.1);
    }

    // Draw Coins
    for (auto &c : coins) {
        if (c.active) {
            Circle(c.x, c.y, c.w/2, 1.0, 0.8, 0.0);
            Circle(c.x - 2, c.y + 2, c.w/4, 1.0, 1.0, 0.8);
        }
    }

    // Draw Spikes
    for (auto &e : enemies) {
        if (e.active) {
            RectangleM(e.x, e.y - e.h/4, e.w, e.h/2, 0.5f, 0.0f, 0.0f);
            float spikeW = e.w / 3.0f;
            float startX = e.x - e.w / 2.0f;
            float baseY = e.y;
            float tipY = e.y + e.h / 2.0f;
            for(int k=0; k<3; k++) {
                Triangle(startX + (k*spikeW), baseY, startX + ((k+1)*spikeW), baseY, startX + (k*spikeW) + (spikeW/2.0f), tipY, 0.9f, 0.1f, 0.1f);
            }
        }
    }

    // Draw Shooters
    for (auto &s : shooters) {
        if (s.active) {
            RectangleM(s.x - 8, s.y - 10, 6, 15, 0.3, 0.3, 0.3);
            RectangleM(s.x + 8, s.y - 10, 6, 15, 0.3, 0.3, 0.3);
            RectangleM(s.x, s.y + 2, 24, 20, 0.5, 0.0, 0.5);
            RectangleM(s.x - 15, s.y + 2, 15, 8, 0.1, 0.1, 0.1);
            Circle(s.x - 22, s.y + 2, 3, 1.0, 0.5, 0.0);
            Circle(s.x, s.y + 16, 10, 0.6, 0.6, 0.6);
            Circle(s.x - 4, s.y + 16, 3, 1.0, 0.0, 0.0);
        }
    }

    // Draw Bullets
    for (auto &b : bullets) {
        if (b.active) {
            Circle(b.x, b.y, 6, 1.0, 0.3, 0.0);
            Circle(b.x, b.y, 3, 1.0, 1.0, 0.0);
        }
    }
}

// Check collision with coins
int Level::checkCoinCollection(float px, float py, float pw, float ph) {
    int scoreAdded = 0;
    for (auto &c : coins) {
        if (c.active && px + pw/2 > c.x - c.w/2 && px - pw/2 < c.x + c.w/2 &&
            py + ph/2 > c.y - c.h/2 && py - ph/2 < c.y + c.h/2) {
            c.active = false;
            scoreAdded += 10;
            PlaySound(TEXT("coin.wav"), NULL, SND_FILENAME | SND_ASYNC);
        }
    }
    return scoreAdded;
}

// Check collision with harmful objects
bool Level::checkCollision(float px, float py, float pw, float ph) {
    for (auto &e : enemies) {
        if (e.active && px + pw/2 > e.x - e.w/2 && px - pw/2 < e.x + e.w/2 &&
            py + ph/2 > e.y - e.h/2 && py - ph/2 < e.y + e.h/2) return true;
    }
    for (auto &s : shooters) {
        if (s.active && px + pw/2 > s.x - s.w/2 && px - pw/2 < s.x + s.w/2 &&
            py + ph/2 > s.y - s.h/2 && py - ph/2 < s.y + s.h/2) return true;
    }
    for (auto &b : bullets) {
        if (b.active && px + pw/2 > b.x - 5 && px - pw/2 < b.x + 5 &&
            py + ph/2 > b.y - 5 && py - ph/2 < b.y + 5) return true;
    }
    return false;
}
