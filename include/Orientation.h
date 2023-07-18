#pragma once

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IDLE = 69
};

struct Position {
    Position(float x, float y)
        : x(x)
        , y(y)
    {}

    float x;
    float y;
};
