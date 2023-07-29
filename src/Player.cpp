#include "../include/Player.h"
#include <stdexcept>

Player::Player(int width, int height)
    : m_Position(static_cast<float>(width), static_cast<float>(height))
    , m_CollisionBox(100, 100)
    , m_Direction(IDLE)
    , m_Width(100)
    , m_Height(100)
    , m_Speed(10.0f)
    , m_Lives(MaxLives)
{}

Player::~Player()
{}

void Player::Move(Direction direction, int width, int height) {
    switch (direction) {
        case UP:
            if (m_Position.y - m_Height / 2.0f > 0)
                m_Position.y -= m_Speed;
            break;
        case DOWN:
            if (m_Position.y < height - m_Height / 2.0f)
                m_Position.y += m_Speed;
            break;
        case LEFT:
            if (m_Position.x - m_Width / 2.0f > 0)
                m_Position.x -= m_Speed;
            break;
        case RIGHT:
            if (m_Position.x < width - m_Width / 2.0f)
                m_Position.x += m_Speed;
            break;
        default:
            break;
    }
}

void Player::Fire() {
    // TODO: implement
}
