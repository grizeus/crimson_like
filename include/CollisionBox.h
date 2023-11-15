#pragma once
#include "Orientation.h"

struct CollisionBox {
    CollisionBox( int width, int height)
        : m_Width(width)
        , m_Height(height)
    {}

    int m_Width;
    int m_Height;
};
