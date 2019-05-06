#include "../include/wall.hpp"

Wall::Wall(Window& wind, int cellSize, int x, int y): Object(wind, cellSize, x, y) {
    setSprite(window.loadSurface("Sprites/Wall.png"));
}

void Wall::draw() { window.drawImage(sprite, &rect); }
