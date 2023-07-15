#pragma once
#include "CollisionBox.h"
#include <memory>

struct Enemy {
    Enemy();
    ~Enemy();

    Position m_Position;
    Direction m_Direction;
    CollisionBox m_CollisionBox;
    int m_Width;
    int m_Height;
    float m_Speed;
};

using EnemyPtr = std::shared_ptr<Enemy>;
