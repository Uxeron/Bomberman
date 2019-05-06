#pragma once

#include "object.hpp"

class WallDestr: public Object {
  public:
    std::string name() { return "wallDestr"; }
    WallDestr(Window& wind, int cellSize, int x, int y);

    void draw();
};
