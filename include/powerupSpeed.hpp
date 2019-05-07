#pragma once

#include "interactiveObject.hpp"

class PowerupSpeed: public InteractiveObject {
  public:
    std::string name() { return "powerupSpeed"; }
    PowerupSpeed(Window& wind, GameLogic& logic, int x, int y);
    ~PowerupSpeed();

    void draw();
    void process(float delta);
    void event(SDL_Event ev);
};
