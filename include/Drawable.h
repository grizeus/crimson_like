#include "SDL_Tools.h"
#include <memory>

using ToolsPtr = std::shared_ptr<SDL_Tools>;

class Drawable {
public:
    Drawable() = default;
    Drawable(ToolsPtr drawer);
    ~Drawable();

    void Draw();
private:
    ToolsPtr m_Drawer;
};
