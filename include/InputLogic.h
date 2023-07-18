#pragma once
#include <SDL2/SDL.h>
#include "Player.h"
#include <vector>

enum Action {
    NONE,
    MOVE_UP,
    MOVE_DOWN,
    MOVE_LEFT,
    MOVE_RIGHT,
    FIRE,
    QUIT
};

void InputHandler(std::vector<SDL_Event>& events);
void InputLogic(Player& player);
