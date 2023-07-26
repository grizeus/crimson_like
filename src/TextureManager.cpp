#include "../include/TextureManager.h"
#include <stdexcept>
#include <iostream>

TextureManager* TextureManager::m_Instance = nullptr;

TextureManager::TextureManager()
{}

TextureManager* TextureManager::GetInstance() {
    if (!m_Instance)
        m_Instance = new TextureManager();
    return m_Instance;
}

uint32_t TextureManager::Loadtexture(const char* file_path) {

    SDL_Surface* surface = IMG_Load(file_path);
    if (!surface)
    {
        std::cout << "Failed load image at " << file_path << std::endl;
        return Error;
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicSystem::GetRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!texture)
        return Error;
    uint32_t ID = 0;
    auto spanesIt = m_IDSpanes.begin();
    if (spanesIt != m_IDSpanes.end())
    {
        ID = *spanesIt;
        m_IDSpanes.erase(spanesIt);
    }
    else
        ID = m_TextureMap.size();
    
    auto [it,success] = m_TextureMap.insert({ID, texture});
    if (success)
        return it->first;
    return Error;
}

uint32_t TextureManager::Loadtexture(const char* file_path, uint32_t ID) {
    SDL_Surface* surface = IMG_Load(file_path);
    if (!surface) {
        std::cout << "Failed load image at " << file_path << std::endl;
        return Error;
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 0xFF, 0xFF));
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicSystem::GetRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!texture)
        return Error;
    
    auto it = m_TextureMap.find(ID);
    if (it != m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        it->second = texture;
        return it->first;
    }
    m_TextureMap[ID] = texture;
    return ID;
}


uint32_t TextureManager::CreateTexture(const char* text, SDL_Color color) {
    
    SDL_Surface* surface = TTF_RenderText_Solid(GraphicSystem::GetFont(), text, color);
    if (!surface) {
        std::cout << "Failed to render text surface from: " << text << std::endl;
        return Error;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicSystem::GetRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!texture)
        return Error;

    uint32_t ID = 0;
    auto spanesIt = m_IDSpanes.begin();
    if (spanesIt != m_IDSpanes.end())
    {
        ID = *spanesIt;
        m_IDSpanes.erase(spanesIt);
    }
    else
        ID = m_TextureMap.size();
    
    auto [it,success] = m_TextureMap.insert({ID, texture});
    if (success)
        return it->first;
    return Error;
}

uint32_t TextureManager::CreateTexture(const char* text, uint32_t ID, SDL_Color color) {
    SDL_Surface* surface = TTF_RenderText_Solid(GraphicSystem::GetFont(), text, color);
    if (!surface) {
        std::cout << "Failed to render text surface from: " << text << std::endl;
        return Error;
    }
    SDL_Texture* texture = SDL_CreateTextureFromSurface(GraphicSystem::GetRenderer(), surface);
    SDL_FreeSurface(surface);
    if (!texture)
        return Error;
    
    auto it = m_TextureMap.find(ID);
    if (it != m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        it->second = texture;
        return it->first;
    }
    m_TextureMap[ID] = texture;
    return ID;
}

void TextureManager::DeleteTexture(uint32_t ID) {
    auto it = m_TextureMap.find(ID);
    if (it != m_TextureMap.end()) {
        SDL_DestroyTexture(it->second);
        m_IDSpanes.insert(ID);
    }
}
