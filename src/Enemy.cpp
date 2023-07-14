#include "../include/Enemy.h"

Enemy::Enemy()
    : m_Position(0, 0)
    , m_Direction(Direction::Idle)
    , m_CollisionBox(20, 20)
    , m_Width(20)
    , m_Height(20)
    , m_Speed(1.0f)
{
}

Enemy::~Enemy()
{}