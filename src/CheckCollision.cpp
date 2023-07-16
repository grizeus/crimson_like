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
        switch (enemy1->m_Direction) {
            case UP:
                enemy1->m_Direction = DOWN;
                break;
            case DOWN:
                enemy1->m_Direction = UP;
                break;
            case LEFT:
                enemy1->m_Direction = RIGHT;
                break;
            case RIGHT:
                enemy1->m_Direction = LEFT;
                break;
            default:
                break;
        }
        switch (enemy2->m_Direction) {
            case UP:
                enemy2->m_Direction = DOWN;
                break;
            case DOWN:
                enemy2->m_Direction = UP;
                break;
            case LEFT:
                enemy2->m_Direction = RIGHT;
                break;
            case RIGHT:
                enemy2->m_Direction = LEFT;
                break;
            default:
                break;
        }
    }
}
