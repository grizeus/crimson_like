#pragma once
#include "Orientation.h"

struct CollisionBox {
    CollisionBox(int x, int y, int width, int height)
        : m_Position(x, y)
        , m_Width(width)
        , m_Height(height)
    {}

    Position m_Position;
    int m_Width;
    int m_Height;
};
