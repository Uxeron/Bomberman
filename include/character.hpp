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
    std::string name() { return "character"; }
    Character(Window *wind, int cellSize): InteractiveObject(wind, cellSize) {};
    Character(Window* wind, int cellSize, int x, int y): InteractiveObject(wind, cellSize, x, y) {};
    void process(float delta);
    void event(SDL_Event ev);
    void draw();

    void move(int distX, int distY);
};
