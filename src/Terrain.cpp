#include "../include/Terrain.h"
#include <fstream>
#include <iostream>
Terrain::Terrain(uint32_t id, int tile_size)
    : m_ID(id)
    , m_Width(0)
    , m_Height(0)
    , m_TileSize(tile_size)
{ }

Terrain::~Terrain()
{ }

void Terrain::CreateTile(char ID, SDL_Rect coord) {
    m_Tiles[ID] = coord;
}

void Terrain::LoadMap(const std::string& path) {
    std::ifstream file(path.c_str());
    std::string line;
    int i = 0;
    while (std::getline(file, line)) {
        if (i == 0) {
            m_Width = std::stoi(line.substr(2)) * m_TileSize;
        }
        else if (i == 1) {
            m_Height = std::stoi(line.substr(2)) * m_TileSize;
        }
        else {
            for (char const& c : line)
                m_Terrain.push_back(&(m_Tiles[c]));
        }
        i++;
    }
}

void Terrain::RenderTerrain(const SDL_Rect& camera) {
    int x = 0, y = 0;
    for (auto& tile : m_Terrain) {
        std::cout << x << " " << y;
        if (x >= camera.x && x < camera.x + camera.w && y >= camera.y && y < camera.y + camera.h) {
            SDL_Rect dst = {x, y, m_TileSize, m_TileSize};
            TextureManager::GetInstance()->RenderTexture(m_ID, tile, &dst);
            std::cout << "! ";
        }
        else
            std::cout << "  ";
        x += m_TileSize;
        if (x > m_Width) {
            std::cout << "\n";
            x = 0;
            y += m_TileSize;
        }
    }
}

int Terrain::GetWidth() const { return m_Width; }

int Terrain::GetHeight() const { return m_Height; }
