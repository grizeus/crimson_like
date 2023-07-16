#include "../include/InputLogic.h"

Action InputHandler() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                return QUIT;
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

void InputLogic( Player& player) {
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W])
        player.Move(UP);
    if (keys[SDL_SCANCODE_A])
        player.Move(LEFT);
    if (keys[SDL_SCANCODE_S])
        player.Move(DOWN);
    if (keys[SDL_SCANCODE_D])
        player.Move(RIGHT);
}
