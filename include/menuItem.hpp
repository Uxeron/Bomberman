#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_ttf.h"
#endif

#include <vector>
#include "exceptions.hpp"

#include <iostream>

#define debugWrite(message) std::cout << message << std::endl;

class MenuItem {
  public:
    SDL_Surface* sprite;
    int index;
    std::vector< std::vector< int > > map;

    MenuItem(int ind, SDL_Surface* spr) : index(ind), sprite(spr) {};
    MenuItem(int ind, SDL_Surface* spr, const char* path) : index(ind), sprite(spr) { loadMap(path); };
    ~MenuItem() { debugWrite("Im free! " << index); SDL_FreeSurface(sprite); }

    void loadMap(const char* path) {};
};
