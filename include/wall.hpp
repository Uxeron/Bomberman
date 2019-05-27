#pragma once

#include "object.hpp"

class Wall: public Object {
  public:
    std::string name() const { return "wall"; }
    Wall(Window& wind, int cellSize, Vector2 position);

    void draw() const { window.drawImage(sprite, rect); };
};
