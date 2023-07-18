#include "../include/EnemyAI.h"
#include <cmath>

void MoveToPlayer(EnemyPtr enemy, Player& player) {
    int centredX = player.GetPosition().x + player.GetCollisionBox().m_Width / 2;
    int centredY = player.GetPosition().y + player.GetCollisionBox().m_Height / 2;
    int enemyX = enemy->m_Position.x;
    int enemyY = enemy->m_Position.y;
    double distance = std::sqrt(std::pow(enemyX - centredX, 2) + std::pow(enemyY - centredY, 2));
    double time = distance / enemy->m_Speed;
    enemy->m_Position.x = enemyX + (centredX - enemyX) / time;
    enemy->m_Position.y = enemyY + (centredY - enemyY) / time;
}

