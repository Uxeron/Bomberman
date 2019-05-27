// Explosion class
#pragma once

#include "interactiveObject.hpp"

class Explosion: public InteractiveObject {
    SDL_Surface* sprites[6];
    int step = 0;
    float stepTime = 0.05;
    float currTime;

  public:
    std::string name() const { return "explosion"; }
    Explosion(Window& wind, GameLogic& logic, Vector2 position);
    ~Explosion();
    void process(float delta);
    void event(const SDL_Event& ev) {};
    void draw() const { window.drawImage(sprite, rect); };
};
