#include "../include/Player.h"
#include <stdexcept>

Player::Player(int width, int height)
    : m_Position(static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f)
    , m_CollisionBox(100, 100)
    , m_Direction(IDLE)
    , m_Width(100)
    , m_Height(100)
    , m_Speed(5.0f)
    , m_Lives(MaxLives)
{}

Player::~Player()
{}

void Player::Move(Direction direction) {
    switch (direction) {
        case UP:
            m_Position.y -= m_Speed;
            break;
        case DOWN:
            m_Position.y += m_Speed;
            break;
        case LEFT:
            m_Position.x -= m_Speed;
            break;
        case RIGHT:
            m_Position.x += m_Speed;
            break;
        default:
            break;
    }
}

void Player::Fire() {
    // TODO: implement
}
