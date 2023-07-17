#include "../include/BulletSpawner.h"
#include <SDL2/SDL.h>

BulletPtr BulletSpawner::Spawn(const Position& playerPos) {
    SDL_Event e;
    BulletPtr bullet = std::make_shared<Bullet>();
    bullet->m_StartPosition.x = playerPos.x;
    bullet->m_StartPosition.y = playerPos.y;
    bullet->m_FinishPosition.x = e.button.x;
    bullet->m_FinishPosition.y = e.button.y;
    return bullet;
}
