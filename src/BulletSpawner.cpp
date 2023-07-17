#include "../include/BulletSpawner.h"
#include <SDL2/SDL.h>

BulletPtr BulletSpawner::Spawn(const Position& playerPos) {
    SDL_Event e;
    Position mousePos = {e.button.x, e.button.y};
    BulletPtr bullet = std::make_shared<Bullet>(playerPos, mousePos);
    return bullet;
}
