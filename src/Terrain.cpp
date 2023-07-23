#include "../include/Terrain.h"
#include <fstream>
#include <iostream>
Terrain::Terrain(int width, int height, int tile_size)
    : m_Width(width)
    , m_Height(height)
    , m_TileSize(tile_size)
{ }

Terrain::~Terrain()
{ }

void Terrain::CreateTile(char ID, SDL_Rect coord) {
    m_Tiles[ID] = coord;
}
/*
w=20
h=10
aaaaaaaaaaaaaaaaaaaa
abbbbbbbbbbbbbbbbbba
abccccccccccccccccba
abccccccccccccccccba
abccccccccccccccccba
abccccccccccccccccba
abccccccccccccccccba
abccccccccccccccccba
abbbbbbbbbbbbbbbbbba
aaaaaaaaaaaaaaaaaaaa
*/
void Terrain::LoadMap(const std::string& path) {
    std::ifstream file(path.c_str());
    std::string line;
    int h = 0, w = 0, i = 0;
    while (std::getline(file, line)) {
        if (i == 0) {
            w = std::stoi(line.substr(2));
        }
        else if (i == 1) {
            std::cout << line << std::endl;
            h = std::stoi(line.substr(2));
            m_Terrain.reserve(w * h);
        }
        else {
            std::cout << "line " << line << std::endl;
            for (char const& c : line) {
                m_Terrain.push_back(&(m_Tiles[c]));
            }
        }
        i++;
    }
}

void Terrain::RenderTerrain(GraphicsSystem* graphic) {
    int x = 0, y = 0, i = 0;

    for (auto& tile : m_Terrain) {
        SDL_Rect dst = {x, y, m_TileSize, m_TileSize};
        SDL_RenderCopy(graphic->GetRenderer(), m_Texture->GetTexture(), tile, &dst);
        x += m_TileSize;
        i++;
        if (x > m_Width) {
            x = 0;
            y += m_TileSize;
        
        }
    }
}
