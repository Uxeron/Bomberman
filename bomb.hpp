// Bomb class
#pragma once 

#include "interactiveObject.hpp"
#include "explosion.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "SDL2/include/SDL.h"
#endif

class Bomb: public InteractiveObject {
    bool exploding = false;
    SDL_Surface* sprites[2];
    // Bomb steps
    int step = 0;
    int explodeOnStep = 10;
    float stepTime = 1.0;
    float currTime;
    // Explosion steps
    int explosionStep = 0;
    int endExplosionStep = 5;
    float explosionStepTime = 0.2;
    
  public:
    Bomb(Window* wind, int x, int y);
    ~Bomb();
    void process(float delta);
    void event(SDL_Event ev);
    void draw();
};