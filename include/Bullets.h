#pragma once
#include "CollisionBox.h"
#include <memory>

struct Bullet {
    Bullet();
    ~Bullet();

    Position m_StartPosition;
    Position m_FinishPosition;
    CollisionBox m_CollisionBox;
    int m_Width;
    int m_Height;
    int m_Damage;
    float m_Speed;
    int m_HP;
};

using BulletPtr = std::shared_ptr<Bullet>;
