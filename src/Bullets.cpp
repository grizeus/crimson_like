#include "../include/Bullets.h"

Bullet::Bullet(Position startPos, Position finishPos)
    : m_StartPosition(startPos)
    , m_FinishPosition(finishPos)
    , m_CollisionBox(10, 10)
    , m_Width(10)
    , m_Height(10)
    , m_Damage(1)
    , m_Speed(3.0f)
    , m_HP(1)
{}

Bullet::~Bullet()
{}
