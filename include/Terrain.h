#pragma once
#include <vector>
#include <map>
#include "Texture.h"
#include "GraphicSystem.h"
#include <memory>

class Terrain {
public:
    Terrain(int width, int height, int tile_size);
    ~Terrain();
    inline void SetTexture(std::shared_ptr<Texture> texture) { m_Texture = texture; }
    void CreateTile(char ID, SDL_Rect coord);
    void LoadMap(const std::string& path);
    void RenderTerrain(GraphicSystem* graphic, std::shared_ptr<Texture> final, SDL_Rect* camera, int width, int height);
private:
    std::map<char, SDL_Rect> m_Tiles;
    std::vector<SDL_Rect*> m_Terrain;
    std::shared_ptr<Texture> m_Texture;
    int m_Width;
    int m_Height;
    int m_TileSize;
};