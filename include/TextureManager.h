#pragma once
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <map>
#include <set>
#include "GraphicSystem.h"
#include <limits>

class TextureManager {
public:
    TextureManager(TextureManager&) = delete;
    void operator=(TextureManager&) = delete;
    static TextureManager* GetInstance();

    uint32_t Loadtexture(const char* file_path);
    uint32_t Loadtexture(const char* file_path, uint32_t ID);
    uint32_t CreateTexture(const std::string& text, SDL_Color color);
    uint32_t CreateTexture(const std::string& text, uint32_t ID, SDL_Color color);
    void RenderTexture(uint32_t ID, SDL_Rect* src = nullptr, SDL_Rect* dst = nullptr);
    void DeleteTexture(uint32_t ID);
    void Clear();

    static constexpr uint32_t Error = std::numeric_limits<uint32_t>::max();
private:
    TextureManager();
    static TextureManager* m_Instance;
    std::map<uint32_t, SDL_Texture*> m_TextureMap;
    std::set<uint32_t> m_IDSpanes;
};
