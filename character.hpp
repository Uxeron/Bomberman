// Character class
#pragma once 

#include "interactiveObject.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "SDL2/include/SDL.h"
#endif

class Character: public InteractiveObject {
public:
    Character(Window* wind): InteractiveObject(wind) {};
    void process();
    void event(SDL_Event ev);
    void draw();

    void move(int dist_x, int dist_y);
};
