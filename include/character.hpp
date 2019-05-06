// Character class
#pragma once

#include "bomb.hpp"
#include "interactiveObject.hpp"

class Character: public InteractiveObject {
    float walkDelay = 0.2;
    float walkDelayCurr = 0;

    float bombDelay = 3.0;
    float bombDelayCurr = 0;

  public:
    static std::string name() { return "character"; }
    Character(Window& wind, GameGrid& grid)
        : InteractiveObject(wind, grid){};
    Character(Window& wind, GameGrid& grid, int x, int y)
        : InteractiveObject(wind, grid, x, y){};
    void process(float delta);
    void event(SDL_Event ev);
    void draw();

    void move(int distX, int distY);
};
