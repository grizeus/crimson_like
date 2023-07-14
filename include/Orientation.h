#pragma once

enum Direction {
    Up,
    Down,
    Left,
    Right,
    Idle = 69
};

struct Position {
    Position(int x, int y)
        : x(x)
        , y(y)
    {}

    int x;
    int y;
};
