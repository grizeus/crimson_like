#include "../include/Drawable.h"
#include <stdexcept>

Drawable::Drawable(ToolsPtr drawer, Position pos, int w, int h)
    : m_Drawer(drawer)
    , m_Position(pos)
    , m_Width(w)
    , m_Height(h)
    , m_Texture(new Texture(drawer))
{}

Drawable::~Drawable()
{}

void Drawable::Draw(const std::string& texturePath)
{
    SDL_Renderer* renderer = m_Drawer->m_Renderer;
    m_Texture->LoadFromFile(texturePath);
    if (!m_Texture) 
        throw std::runtime_error(SDL_GetError());
    SDL_Rect rect = { static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), m_Width, m_Height };
    m_Texture->Render(static_cast<int>(m_Position.x), static_cast<int>(m_Position.y), &rect);
}
