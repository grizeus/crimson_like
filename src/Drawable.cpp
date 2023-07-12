#include "../include/Drawable.h"

Drawable::Drawable(ToolsPtr drawer)
    : m_Drawer(drawer)
{}

Drawable::~Drawable()
{}

void Drawable::Draw()
{
    m_Drawer->Draw();
}
