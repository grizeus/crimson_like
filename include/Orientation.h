#pragma once

enum Direction {
    UP,
    DOWN,
    LEFT,
    RIGHT,
    IDLE = 69
};

struct Position {
    Position(int x, int y)
        : x(x)
        , y(y)
    {}

    int x;
    int y;
};
