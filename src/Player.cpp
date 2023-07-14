#include "../include/Player.h"
#include <stdexcept>

Player::Player()
    : m_Position(0, 0)
    , m_CollisionBox(0, 0, 0, 0)
    , m_Width(20)
    , m_Height(20)
    , m_Speed(0.0f)
    , m_Score(0)
    , m_Lives(MaxLives)
{}

Player::~Player()
{}

void Player::Update()
{}
