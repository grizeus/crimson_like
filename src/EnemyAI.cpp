#include "../include/EnemyAI.h"
#include <cmath>

void MoveToPlayer(EnemyPtr enemy, Player& player) {
    double distance = sqrt(pow(enemy->m_Position.x - player.GetPosition().x, 2) + pow(enemy->m_Position.y - player.GetPosition().y, 2));
    double time = distance / enemy->m_Speed;
    enemy->m_Position.x += (player.GetPosition().x - enemy->m_Position.x) / time;
    enemy->m_Position.y += (player.GetPosition().y - enemy->m_Position.y) / time;
}
