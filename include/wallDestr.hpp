#pragma once

#include "object.hpp"

class WallDestr: public Object {
  public:
    std::string name() const { return "wallDestr"; }
    WallDestr(Window& wind, int cellSize, Vector2 position);

    void draw() const { window.drawImage(sprite, rect); };
};
