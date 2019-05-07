#pragma once

#include "interactiveObject.hpp"

class PowerupBomb: public InteractiveObject {
  public:
    std::string name() { return "powerupBomb"; }
    PowerupBomb(Window& wind, GameLogic& logic, int x, int y);
    ~PowerupBomb();

    void draw();
    void process(float delta);
    void event(SDL_Event ev);
};
