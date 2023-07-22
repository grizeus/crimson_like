#include "../include/Player.h"
#include <stdexcept>

Player::Player(int width, int height)
    : m_Position(static_cast<float>(width) / 2.0f, static_cast<float>(height) / 2.0f)
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
            m_Position.y -= m_Speed;
            if (m_Position.y < 0)
                m_Position.y = 0;
            break;
        case DOWN:
            m_Position.y += m_Speed;
            if (m_Position.y > height - m_Height)
                m_Position.y = height - m_Height;
            break;
        case LEFT:
            m_Position.x -= m_Speed;
            if (m_Position.x < 0)
                m_Position.x = 0;
            break;
        case RIGHT:
            m_Position.x += m_Speed;
            if (m_Position.x > width - m_Width)
                m_Position.x = width - m_Width;
            break;
        default:
            break;
    }
}

void Player::Fire() {
    // TODO: implement
}
