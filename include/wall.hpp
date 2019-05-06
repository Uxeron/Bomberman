#pragma once

#include "object.hpp"

class Wall: public Object {
  public:
    static std::string name() { return "wall"; }
    Wall(Window& wind, int cellSize, int x, int y);

    void draw();
};
