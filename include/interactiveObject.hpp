// The base class for any object that can be interacted with (characters, bombs, etc)
#pragma once

#include "object.hpp"

class InteractiveObject: public Object {
  public:
    InteractiveObject(Window* wind, int cellSize): Object(wind, cellSize) {};
    InteractiveObject(Window* wind, int cellSize, int x, int y): Object(wind, cellSize, x, y) {};

    int deltaX = 0; // How much the object wants to move on the grid along the X axis
    int deltaY = 0; // How much the object wants to move on the grid along the Y axis

    virtual void process(float delta) = 0;
    virtual void event(SDL_Event ev) = 0;
};
