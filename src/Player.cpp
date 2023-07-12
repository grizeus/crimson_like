#include "../include/Player.h"
#include <stdexcept>

Player::Player(ToolsPtr drawer)
    : m_Drawable(drawer, Position(0, 0), 10, 10)
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
}
