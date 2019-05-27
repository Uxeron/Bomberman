// Character class
#pragma once

#include "bomb.hpp"
#include "interactiveObject.hpp"
#include <string>

class Character: public InteractiveObject {
    static int count;
    int index = count++;

    int bombStepAdjust = 0;

    float walkDelay = 0.2;
    float walkDelayCurr = 0;

    float bombDelay = 3.0;
    float bombDelayCurr = 0;

    Vector2 moveAnimationOffset;

    Vector2 lastPos;

    int lastDir = 0; // 0 - down, 1 - left, 2 - up, 3 - right

  public:
    std::string name() const { return "character"; }
    Character(Window& wind, GameLogic& logic);
    Character(Window& wind, GameLogic& logic, Vector2 position);
    ~Character();
    void process(float delta);
    void event(const SDL_Event& ev);
    void draw() const;

    bool move(Vector2 dist);

    static void resetCount() { count = 0; }
};
