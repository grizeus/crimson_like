#include "SDL_Tools.h"
#include "Texture.h"

struct Position
{
    float x;
    float y;

    Position(float x, float y)
        : x(x)
        , y(y)
    {}

    Position(Position& pos)
        : x(pos.x)
        , y(pos.y)
    {}

    Position& operator=(const Position& pos)
    {
        x = pos.x;
        y = pos.y;
        return *this;
    }
};

class Drawable {
public:
    Drawable(ToolsPtr, Position, int, int);
    ~Drawable();

    void Draw(const std::string&);

    inline const Position& GetPosition() const { return m_Position; }
    inline int GetWidth() const { return m_Width; }
    inline int GetHeight() const { return m_Height; }
    inline ToolsPtr GetDrawer() const { return m_Drawer; }

    inline void SetPosition(const Position& position) { m_Position = position; }
    inline void SetWidth(int width) { m_Width = width; }
    inline void SetHeight(int height) { m_Height = height; }
    inline void SetDrawer(const ToolsPtr& drawer) { m_Drawer = drawer; }

private: 
    Position m_Position;
    int m_Width;
    int m_Height;
    ToolsPtr m_Drawer;
    Texture* m_Texture;
};
