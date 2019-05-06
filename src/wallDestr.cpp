#include "../include/wallDestr.hpp"

WallDestr::WallDestr(Window& wind, int cellSize, int x, int y): Object(wind, cellSize, x, y) {
    setSprite(window.loadSurface("Sprites/WallDestructible.png"));
}

void WallDestr::draw() { window.drawImage(sprite, &rect); }
