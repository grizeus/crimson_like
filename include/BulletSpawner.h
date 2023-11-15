#pragma once
#include "Bullets.h"
#include "Player.h"
#include <SDL.h>
#include <vector>

class BulletSpawner {
public:
    BulletSpawner() {}
    ~BulletSpawner() {} 
    BulletPtr Spawn(const Player& player, std::vector<SDL_Event>& events, const SDL_Rect& camera);
};
