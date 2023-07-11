#pragma once

struct Position
{
    Position()
        : x(0.0f)
        , y(0.0f)
    {}

    Position(float x, float y)
        : x(x)
        , y(y)
    {}

    float x;
    float y;
};

class Player
{
public:
    Player();
    ~Player();

    void Update();
    void Draw();

    static const int MaxLives = 3;
    static const int MaxAmmo = 150;

    inline Position GetPosition() const { return m_Position; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline int GetScore() const { return m_Score; }
    inline int GetLives() const { return m_Lives; }
    inline int GetAmmo() const { return m_Ammo; }

    inline void SetPosition(Position position) { m_Position = position; }
    inline void SetWidth(int width) { m_Width = width; }
    inline void SetHeight(int height) { m_Height = height; }
    inline void SetScore(int score) { m_Score = score; }
    inline void SetLives(int lives) { m_Lives = lives; }
    inline void SetAmmo(int ammo) { m_Ammo = ammo; }

private:
    Position m_Position;
    int m_Width;
    int m_Height;
    float m_Speed;
    int m_Score;
    int m_Lives;
    int m_Ammo;
};
