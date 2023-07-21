#pragma once
#include "Bullets.h"
#include "CollisionBox.h"

class Player {
public:
    Player(int width, int height);
    ~Player();

    void Move(Direction direction, int width, int height);
    void Fire();

    static const int MaxLives = 3;

    inline const Position& GetPosition() const { return m_Position; }
    inline const CollisionBox& GetCollisionBox() const { return m_CollisionBox; }
    inline Direction GetDirection() const { return m_Direction; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetLives() const { return m_Lives; }

    inline void SetPosition(const Position& position) { m_Position = position; }
    inline void SetCollisionBox(const CollisionBox& collision) { m_CollisionBox = collision; }
    inline void SetDirection(Direction direction) { m_Direction = direction; }
    inline void SetWidth(int width) { m_Width = width; } 
    inline void SetHeight(int height) { m_Height = height; } 
    inline void SetLives(int lives) { m_Lives = lives; }

private:
    Position m_Position;
    CollisionBox m_CollisionBox;
    Direction m_Direction;
    int m_Width;
    int m_Height;
    float m_Speed;
    int m_Lives;
};
