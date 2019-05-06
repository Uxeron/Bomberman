// The base class for any object that can be interacted with (characters, bombs, etc)
#pragma once

#include "gameGrid.hpp"
#include "object.hpp"

class InteractiveObject: public Object {
  protected:
    GameGrid& gameGrid;

  public:
    InteractiveObject(Window& wind, GameGrid& grid)
        : Object(wind, grid.getSqSize()), gameGrid(grid) {};
    InteractiveObject(Window& wind, GameGrid& grid, int x, int y)
        : Object(wind, grid.getSqSize(), x, y), gameGrid(grid){};

    int deltaX = 0; // How much the object wants to move on the grid along the X axis
    int deltaY = 0; // How much the object wants to move on the grid along the Y axis

    

    virtual void process(float delta) = 0;
    virtual void event(SDL_Event ev) = 0;
};
