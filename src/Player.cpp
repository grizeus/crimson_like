#include "../include/Player.h"
#include <stdexcept>

Player::Player()
    : m_Position(0.0f, 0.0f)
    , m_Width(10)
    , m_Height(10)
    , m_Speed(0.0f)
    , m_Score(0)
    , m_Lives(0)
    , m_Ammo(0)
{}

Player::~Player()
{}

void Player::Update()
{}

void Player::Draw() {
    SDL_Renderer* renderer = m_Drawer->GetRenderer();
    SDL_Surface* surface = m_Drawer->GetSurface();
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_FreeSurface(surface);
    if (texture == nullptr) 
        throw std::runtime_error(SDL_GetError());
    SDL_Rect rect = { static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), m_Width, m_Height };
    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
