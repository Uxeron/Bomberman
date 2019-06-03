#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
#else
  #include "../SDL2/include/SDL.h"
#endif

#include <vector>
#include "exceptions.hpp"

class MenuItem {
  public:
    SDL_Surface* sprite;
    int index;
    std::vector< std::vector< int > > map;

    MenuItem(SDL_Surface* spr) : sprite(spr) {};
    MenuItem(SDL_Surface* spr, const char* path) : sprite(spr) { loadMap(path); };
    ~MenuItem() { SDL_FreeSurface(sprite); }

    void loadMap(const char* path);
};
