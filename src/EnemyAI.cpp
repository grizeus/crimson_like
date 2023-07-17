#include "../include/EnemyAI.h"
#include <cmath>

void MoveToPlayer(EnemyPtr enemy, Player& player) {
    double distance = sqrt(pow(enemy->m_Position.x - player.GetPosition().x, 2) + pow(enemy->m_Position.y - player.GetPosition().y, 2));
    double time = distance / enemy->m_Speed;
    enemy->m_Position.x += (player.GetPosition().x - enemy->m_Position.x) / time;
    enemy->m_Position.y += (player.GetPosition().y - enemy->m_Position.y) / time;
}

void ProjectileToPoint(BulletPtr bullet) {
    double distance = sqrt(pow(bullet->m_StartPosition.x - bullet->m_FinishPosition.x, 2) + pow(bullet->m_StartPosition.y - bullet->m_FinishPosition.y, 2));
    double time = distance / bullet->m_Speed;
    bullet->m_StartPosition.x += (bullet->m_StartPosition.x - bullet->m_FinishPosition.x) / time;
    bullet->m_StartPosition.y += (bullet->m_StartPosition.y - bullet->m_FinishPosition.y) / time;
}
