#include "../include/wall.hpp"

Wall::Wall(Window& wind, int cellSize, Vector2 position)
    : Object(wind, cellSize, position) {
    setSprite(window.loadSurface("Sprites/Wall.png"));
}
