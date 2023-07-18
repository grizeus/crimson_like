#include "../include/BulletSpawner.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_events.h>

BulletPtr BulletSpawner::Spawn(const Position& playerPos, std::vector<SDL_Event>& events) {
    BulletPtr bullet = nullptr;
    for (auto& e : events) {
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT) {
                float dirX = static_cast<float>(e.button.x - playerPos.x);
                float dirY = static_cast<float>(e.button.y - playerPos.y);
                // Normalize the direction vector
                float magnitude = std::sqrt(dirX * dirX + dirY * dirY);
                dirX /= magnitude;
                dirY /= magnitude;
                Position directionVector = {dirX, dirY};
                bullet = std::make_shared<Bullet>(playerPos, directionVector);
            }
    }
    return bullet;
}
