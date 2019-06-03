#pragma once

#include "interactiveObject.hpp"

class PowerupBomb: public InteractiveObject {
  public:
    std::string name() const { return "powerupBomb"; }
    PowerupBomb(Window& wind, GameLogic& logic, Vector2 position);
    ~PowerupBomb();

    void process(float delta) {};
    void event(SDL_Event const& ev) {};
    void draw() const { window.drawImage(sprite, rect); };
};
