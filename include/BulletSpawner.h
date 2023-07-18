#pragma once
#include "Bullets.h"
#include <SDL2/SDL.h>
#include <vector>

class BulletSpawner {
public:
    BulletSpawner() {}
    ~BulletSpawner() {} 
    BulletPtr Spawn(const Position& playerPos, std::vector<SDL_Event>& events);
};
