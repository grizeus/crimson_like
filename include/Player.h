#pragma once
#include "CollisionBox.h"

class Player {
public:
    Player();
    ~Player();

    void Update();

    static const int MaxLives = 3;

    inline const Position& GetPosition() const { return m_Position; }
    inline const CollisionBox& GetCollisionBox() const { return m_CollisionBox; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetScore() const { return m_Score; }
    inline int GetLives() const { return m_Lives; }

    inline void SetPosition(Position position) { m_Position = position; }
    inline void SetCollisionBox(CollisionBox collision) { m_CollisionBox = collision; }
    inline void SetWidth(int width) { m_Width = width; } 
    inline void SetHeight(int height) { m_Height = height; } 
    inline void SetScore(int score) { m_Score = score; }
    inline void SetLives(int lives) { m_Lives = lives; }

private:
    Position m_Position;
    CollisionBox m_CollisionBox;
    int m_Width;
    int m_Height;
    float m_Speed;
    int m_Score;
    int m_Lives;
};
