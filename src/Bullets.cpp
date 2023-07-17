#include "../include/Bullets.h"

Bullet::Bullet()
    : m_StartPosition(0, 0)
    , m_FinishPosition(0, 0)
    , m_CollisionBox(10, 10)
    , m_Width(10)
    , m_Height(10)
    , m_Damage(1)
    , m_Speed(3.0f)
    , m_HP(1)
{}

Bullet::~Bullet()
{}
