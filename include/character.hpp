// Character class
#pragma once

#include "bomb.hpp"
#include "interactiveObject.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "../SDL2/include/SDL.h"
#endif

class Character: public InteractiveObject {
    const int pivotOffsetX = -4;
    const int pivotOffsetY = 20;
    float walkDelay = 0.2;
    float walkDelayCurr = 0;

    float bombDelay = 3.0;
    float bombDelayCurr = 0;

  public:
    std::string name() { return "character"; }
    Character(Window& wind, GameGrid& grid)
        : InteractiveObject(wind, grid){};
    Character(Window& wind, GameGrid& grid, int x, int y)
        : InteractiveObject(wind, grid, x, y){};
    void process(float delta);
    void event(SDL_Event ev);
    void draw();

    void move(int distX, int distY);
};
