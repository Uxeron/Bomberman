// Character class
#pragma once 

#include "interactiveObject.hpp"
#include "bomb.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "SDL2/include/SDL.h"
#endif

class Character: public InteractiveObject {
    const int pivotOffsetX = -4;
    const int pivotOffsetY = 20;

  public:
    Character(Window *wind): InteractiveObject(wind) {};
    void process(float delta);
    void event(SDL_Event ev);
    void draw();

    void move(int dist_x, int dist_y);
};
