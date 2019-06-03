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

    float bombDelay = 2.5;
    float bombDelayCurr = 0;

    Vector2 moveAnimationOffset;
    Vector2 lastPos;

    float animFrameDelay = 0.1;
    float currAnimFrameDelay = animFrameDelay;
    int animIndex = 4;

    SDL_Surface* sprites[4][5];

    int keys[5];

    int lastDir = 2; // 0 - down, 1 - left, 2 - up, 3 - right

    void loadSprites();
    void selectControls();

  public:
    std::string name() const { return "character"; }
    Character(Window& wind, GameLogic& logic);
    Character(Window& wind, GameLogic& logic, Vector2 position);
    ~Character();
    void process(float delta);
    void event(SDL_Event const& ev);
    void draw() const;

    bool move(Vector2 dist);

    static void resetCount() { count = 0; }
    static int getCount() { return count; }
    int getIndex() const { return index; }
};
