#pragma once
#include <vector>
#include <map>
#include "Texture.h"
#include "GraphicSystem.h"
#include "TextureManager.h"
#include "CheckCollision.h"
#include <memory>

class Terrain {
public:
    Terrain(uint32_t id, int tile_size);
    ~Terrain();
    inline void SetTexture(uint32_t id) { m_ID = id; }
    void CreateTile(char ID, SDL_Rect coord);
    void LoadMap(const std::string& path);
    void RenderTerrain(const SDL_Rect& camera);
    int GetWidth() const;
    int GetHeight() const;
private:
    std::map<char, SDL_Rect> m_Tiles;
    std::vector<SDL_Rect*> m_Terrain;
    uint32_t m_ID;
    int m_Width;
    int m_Height;
    int m_TileSize;
};