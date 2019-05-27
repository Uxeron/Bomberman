#include "../include/wallDestr.hpp"

WallDestr::WallDestr(Window& wind, int cellSize, Vector2 position)
    : Object(wind, cellSize, position) {
    setSprite(window.loadSurface("Sprites/WallDestructible.png"));
}
