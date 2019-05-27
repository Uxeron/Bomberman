#pragma once

#include "interactiveObject.hpp"

class PowerupSpeed: public InteractiveObject {
  public:
    std::string name() const { return "powerupSpeed"; }
    PowerupSpeed(Window& wind, GameLogic& logic, int x, int y);
    ~PowerupSpeed();

    void process(float delta);
    void event(const SDL_Event& ev) {};
    void draw() const { window.drawImage(sprite, rect); };
};
