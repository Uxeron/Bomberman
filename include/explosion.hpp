// Explosion class
#pragma once

#include "../include/interactiveObject.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "../SDL2/include/SDL.h"
#endif

class Explosion: public InteractiveObject {
    SDL_Surface* sprites[6];
    int step = 0;
    float stepTime = 0.2;
    float currTime;

  public:
    Explosion(Window* wind, int x, int y);
    ~Explosion();
    void process(float delta);
    void event(SDL_Event ev);
    void draw();
};
