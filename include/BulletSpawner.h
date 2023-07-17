#pragma once
#include "Bullets.h"

class BulletSpawner {
public:
    BulletSpawner() {}
    ~BulletSpawner() {} 
    BulletPtr Spawn(const Position& playerPos);
};
