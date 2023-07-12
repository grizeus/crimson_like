#pragma once
#include "Drawable.h"

class Player
{
public:
    Player(ToolsPtr drawer);
    ~Player();

    void Update();
    void Draw();

    static const int MaxLives = 3;
    static const int MaxAmmo = 150;

    inline const Position& GetPosition() const { return m_Drawable.GetPosition(); }
    inline int GetWidth() const { return m_Drawable.GetWidth(); }
    inline int GetHeight() const { return m_Drawable.GetHeight(); }
    inline ToolsPtr GetDrawer() const { return m_Drawable.GetDrawer(); }
    inline int GetScore() const { return m_Score; }
    inline int GetLives() const { return m_Lives; }
    inline int GetAmmo() const { return m_Ammo; }

    inline void SetPosition(Position position) { m_Drawable.SetPosition(position); }
    inline void SetWidth(int width) { m_Drawable.SetWidth(width); } 
    inline void SetHeight(int height) { m_Drawable.SetHeight(height); } 
    inline void SetDrawer(ToolsPtr drawer) { m_Drawable.SetDrawer(drawer); }
    inline void SetScore(int score) { m_Score = score; }
    inline void SetLives(int lives) { m_Lives = lives; }
    inline void SetAmmo(int ammo) { m_Ammo = ammo; }

private:
    Drawable m_Drawable;
    float m_Speed;
    int m_Score;
    int m_Lives;
    int m_Ammo;
};
