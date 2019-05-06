// Character class
#pragma once

#include "bomb.hpp"
#include "interactiveObject.hpp"
#include <string>

class Character: public InteractiveObject {
    static int count;
    int index = count++;

    float walkDelay = 0.2;
    float walkDelayCurr = 0;

    float bombDelay = 3.0;
    float bombDelayCurr = 0;

    int lastDir = 0; // 0 - down, 1 - left, 2 - up, 3 - right

  public:
    std::string name() { return "character"; }
    Character(Window& wind, GameLogic& logic);
    Character(Window& wind, GameLogic& logic, int x, int y);
    ~Character();
    void process(float delta);
    void event(SDL_Event ev);
    void draw();

    void move(int distX, int distY);

    static void resetCount() { count = 0; }
};
