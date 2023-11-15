#include "../include/EnemyAI.h"
#include <cmath>

void MoveTo(EnemyPtr enemy, Player& player) {
    float centredX = player.GetPosition().x + player.GetCollisionBox().m_Width / 2.0f;
    float centredY = player.GetPosition().y + player.GetCollisionBox().m_Height / 2.0f;
    float enemyX = enemy->m_Position.x;
    float enemyY = enemy->m_Position.y;
    float distance = static_cast<float>(std::sqrt((enemyX - centredX) * (enemyX - centredX) + (enemyY - centredY) * (enemyY - centredY)));
    float time = distance / enemy->m_Speed;
    enemy->m_Position.x = enemyX + (centredX - enemyX) / time;
    enemy->m_Position.y = enemyY + (centredY - enemyY) / time;
}

