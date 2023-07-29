#include "../include/BulletSpawner.h"
#include <SDL2/SDL.h>

BulletPtr BulletSpawner::Spawn(const Player& player, std::vector<SDL_Event>& events, const SDL_Rect& camera) {
    BulletPtr bullet = nullptr;
    float startX = player.GetPosition().x;
    float startY = player.GetPosition().y;
    for (auto& e : events) {
        if (e.type == SDL_MOUSEBUTTONDOWN)
            if (e.button.button == SDL_BUTTON_LEFT) {
                float dirX = static_cast<float>(e.button.x + camera.x - startX);
                float dirY = static_cast<float>(e.button.y + camera.y - startY);
                // Normalize the direction vector
                float magnitude = std::sqrt(dirX * dirX + dirY * dirY);
                dirX /= magnitude;
                dirY /= magnitude;
                Position directionVector = {dirX, dirY};
                Position startPos = {startX, startY};
                bullet = std::make_shared<Bullet>(startPos, directionVector);
            }
    }
    return bullet;
}
