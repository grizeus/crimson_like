#include "../include/Enemy.h"

Enemy::Enemy()
    : m_Position(0, 0)
    , m_Direction(Direction::IDLE)
    , m_CollisionBox(20, 20)
    , m_Width(20)
    , m_Height(20)
    , m_Speed(2.0f)
    , m_HP(1)
{
}

Enemy::~Enemy()
{}