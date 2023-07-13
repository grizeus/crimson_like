#include "../include/Player.h"
#include <stdexcept>

Player::Player(ToolsPtr drawer)
    : m_Drawable(drawer, Position(static_cast<float>(drawer->m_WindowWidth / 2), static_cast<float>(drawer->m_WindowHeight / 2)), 10, 10)
    , m_Speed(0.0f)
    , m_Score(0)
    , m_Lives(0)
    , m_Ammo(0)
{}

Player::~Player()
{}

void Player::Update()
{}

void Player::Draw(const std::string& texturePath) {
    SDL_RenderClear(m_Drawable.GetDrawer()->m_Renderer);
    m_Drawable.Draw(texturePath);
    SDL_RenderPresent(m_Drawable.GetDrawer()->m_Renderer);
}
