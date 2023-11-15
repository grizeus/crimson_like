#include "../include/Texture.h"
#include <stdexcept>

Texture::Texture()
    : m_Texture(nullptr)
    , m_Width(0)
    , m_Height(0)
{}

Texture::Texture(Texture& other) 
    : m_Texture(other.m_Texture)
{ }

Texture::~Texture() { Destroy(); }

void Texture::Destroy() {
    if (m_Texture != nullptr) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
}

void Texture::SetTexture(SDL_Texture* texture) {
    Destroy();
    m_Texture = texture; 
}
