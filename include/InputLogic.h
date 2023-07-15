#pragma once
#include <SDL2/SDL.h>
#include "Player.h"

enum Action {
    NONE,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    FIRE,
    QUIT
};

Action InputHandler();
void InputLogic(Action, Player&);
