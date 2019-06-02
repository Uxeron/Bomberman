#pragma once

#include "interactiveObject.hpp"

class PowerupSpeed: public InteractiveObject {
  public:
    std::string name() const { return "powerupSpeed"; }
    PowerupSpeed(Window& wind, GameLogic& logic, Vector2 position);
    ~PowerupSpeed();

    void process(float delta);
    void event(SDL_Event const& ev){};
    void draw() const { window.drawImage(sprite, rect); };
};
