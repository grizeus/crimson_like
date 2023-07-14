#include "../include/InputHandler.h"

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
                        return UP;
                        break;
                    case SDLK_DOWN:
                        return DOWN;
                        break;
                    case SDLK_LEFT:
                        return LEFT;
                        break;
                    case SDLK_RIGHT:
                        return RIGHT;
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
