#include "../include/InputLogic.h"

Action InputHandler() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return QUIT;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE:
                        break;
                    case SDLK_UP:
                        return MOVE_UP;
                        break;
                    case SDLK_DOWN:
                        return MOVE_DOWN;
                        break;
                    case SDLK_LEFT:
                        return MOVE_LEFT;
                        break;
                    case SDLK_RIGHT:
                        return MOVE_RIGHT;
                        break;
                    default:
                        break;
                }
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        return FIRE;
                        break;
                    default:
                        break;
                } 
                break;
            default:
                break;
        }
    }
    return NONE;
}

void InputLogic(Action action, Player& player) {
    switch (action) {
        case MOVE_UP:
            player.SetDirection(UP);
            break;
        case MOVE_DOWN:
            player.SetDirection(DOWN);
            break;
        case MOVE_LEFT:
            player.SetDirection(LEFT);
            break;
        case MOVE_RIGHT:
            player.SetDirection(RIGHT);
            break;
        case FIRE:
            player.Fire();
            break;
        default:
            break;
    }
}
