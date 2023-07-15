#include "../include/Player.h"
#include <stdexcept>

Player::Player()
    : m_Position(0, 0)
    , m_CollisionBox(20, 20)
    , m_Direction(IDLE)
    , m_Width(20)
    , m_Height(20)
    , m_Speed(0.0f)
    , m_Lives(MaxLives)
{}

Player::~Player()
{}

void Player::Move(Direction direction)
{
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
