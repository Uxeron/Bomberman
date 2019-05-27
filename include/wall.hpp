#pragma once

#include "object.hpp"

class Wall: public Object {
  public:
    std::string name() const { return "wall"; }
    Wall(Window& wind, int cellSize, int x, int y);

    void draw() const { window.drawImage(sprite, rect); };
};
