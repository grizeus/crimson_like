#include "../include/InputLogic.h"

void InputHandler(std::vector<SDL_Event>& events) {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                events.push_back(e);
                break;
            case SDL_MOUSEBUTTONDOWN:
                switch (e.button.button) {
                    case SDL_BUTTON_LEFT:
                        events.push_back(e);
                        break;
                    default:
                        break;
                } 
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_w:
                        events.push_back(e);
                        break;
                    case SDLK_a:
                        events.push_back(e);
                        break;
                    case SDLK_s:
                        events.push_back(e);
                        break;
                    case SDLK_d:
                        events.push_back(e);
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
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
