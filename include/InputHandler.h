#pragma once
#include <SDL2/SDL.h>

enum Action {
    NONE,
    UP,
    DOWN,
    LEFT,
    RIGHT,
    FIRE,
    QUIT
};

Action InputHandler();
