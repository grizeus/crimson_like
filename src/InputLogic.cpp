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

void MoveLogic( Player& player, int levelWidth, int levelHeight) {
    const Uint8* keys = SDL_GetKeyboardState(nullptr);
    if (keys[SDL_SCANCODE_W])
        player.Move(UP, levelWidth, levelHeight);
    if (keys[SDL_SCANCODE_A])
        player.Move(LEFT, levelWidth, levelHeight);
    if (keys[SDL_SCANCODE_S])
        player.Move(DOWN, levelWidth, levelHeight);
    if (keys[SDL_SCANCODE_D])
        player.Move(RIGHT, levelWidth, levelHeight);
}

bool Quit(std::vector<SDL_Event>& events) {
    for (auto& e : events) {
        if (e.type == SDL_QUIT)
            return true;
    }
    return false;
}
