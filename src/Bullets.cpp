#include "../include/Bullets.h"

Bullet::Bullet(Position startPos, Position directionVector)
    : m_StartPosition(startPos)
    , m_DirectionVector(directionVector)
    , m_CollisionBox(10, 10)
    , m_Width(10)
    , m_Height(10)
    , m_Damage(1)
    , m_Speed(3.0f)
    , m_HP(1)
{}

Bullet::~Bullet()
{}

void Bullet::Move() {
    m_StartPosition.x += m_DirectionVector.x * m_Speed;
    m_StartPosition.y += m_DirectionVector.y * m_Speed;
}
