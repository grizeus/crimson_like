#include "../include/CheckCollision.h"

bool IsCollision(const CollisionBox& box1, const Position& pos1, const CollisionBox& box2, const Position& pos2) {
    if ((pos1.x <= pos2.x + box2.m_Width) &&
        (pos1.x + box1.m_Width >= pos2.x) &&
        (pos1.y <= pos2.y + box2.m_Height) &&
        (pos1.y + box1.m_Height >= pos2.y)) {
            return true;
    }
    return false;
}

void CheckCollision(Player& player, Enemy* enemy) {
    if (IsCollision(player.GetCollisionBox(), player.GetPosition(), enemy->m_CollisionBox, enemy->m_Position)) {
        player.SetLives(player.GetLives() - 1);
        enemy->m_HP = 0;
    }
}

void CheckCollision(Enemy* enemy1, Enemy* enemy2) {
    if (IsCollision(enemy1->m_CollisionBox, enemy1->m_Position, enemy2->m_CollisionBox, enemy2->m_Position)) {
        if (enemy1->m_Position.x < enemy2->m_Position.x && enemy1->m_Position.y < enemy2->m_Position.y) {
            enemy1->m_Position.x -= 1;
            enemy1->m_Position.y -= 1;
            enemy2->m_Position.x += 1;
            enemy2->m_Position.y += 1;
        } else if (enemy1->m_Position.x < enemy2->m_Position.x && enemy1->m_Position.y > enemy2->m_Position.y) {
            enemy1->m_Position.x -= 1;
            enemy1->m_Position.y += 1;
            enemy2->m_Position.x += 1;
            enemy2->m_Position.y -= 1;
        } else if (enemy1->m_Position.x > enemy2->m_Position.x && enemy1->m_Position.y < enemy2->m_Position.y) {
            enemy1->m_Position.x += 1;
            enemy1->m_Position.y -= 1;
            enemy2->m_Position.x -= 1;
            enemy2->m_Position.y += 1;
        } else if (enemy1->m_Position.x > enemy2->m_Position.x && enemy1->m_Position.y > enemy2->m_Position.y) {
            enemy1->m_Position.x += 1;
            enemy1->m_Position.y += 1;
            enemy2->m_Position.x -= 1;
            enemy2->m_Position.y -= 1;
        }
    }
}

void CheckCollision(Enemy* enemy, Bullet* bullet) {
   if (IsCollision(enemy->m_CollisionBox, enemy->m_Position, bullet->m_CollisionBox, bullet->m_StartPosition)) {
       enemy->m_HP -= bullet->m_Damage;
       bullet->m_HP = 0;
   }
}
