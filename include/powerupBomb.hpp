#pragma once

#include "interactiveObject.hpp"

class PowerupBomb: public InteractiveObject {
  public:
    std::string name() const { return "powerupBomb"; }
    PowerupBomb(Window& wind, GameLogic& logic, int x, int y);
    ~PowerupBomb();

    void process(float delta);
    void event(const SDL_Event& ev) {};
    void draw() const { window.drawImage(sprite, rect); };
};
