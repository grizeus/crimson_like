#include "../include/Texture.h"
#include <stdexcept>

Texture::Texture()
    : m_Texture(nullptr)
{ }
Texture::Texture(Texture& other) 
    : m_Texture(other.m_Texture)
{ }

Texture::~Texture() 
{ }

void Texture::Destroy() {
    if (m_Texture != nullptr) {
        SDL_DestroyTexture(m_Texture);
        m_Texture = nullptr;
    }
}
