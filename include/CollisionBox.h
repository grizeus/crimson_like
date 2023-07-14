#pragma once
#include "Position.h"

struct CollisionBox {
    CollisionBox(int x, int y, int width, int height)
        : position(x, y)
        , width(width)
        , height(height)
    {}

    Position position;
    int width;
    int height;
};
