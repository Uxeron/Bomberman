// Explosion class
#pragma once

#include "interactiveObject.hpp"

class Explosion: public InteractiveObject {
    SDL_Surface* sprites[6];
    int step = 0;
    float stepTime = 0.025;
    float currTime;

  public:
    std::string name() { return "explosion"; }
    Explosion(Window& wind, GameLogic& logic, int x, int y);
    ~Explosion();
    void process(float delta);
    void event(SDL_Event ev);
    void draw();
};
