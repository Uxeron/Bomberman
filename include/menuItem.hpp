#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_ttf.h"
#endif

#include <vector>
#include "vector2.hpp"
#include "exceptions.hpp"

#include <iostream>

#define debugWrite(message) std::cout << message << std::endl;

class MenuItem {
  public:
    SDL_Surface* sprite;
    TTF_Font* font;
    Vector2 textPos = Vector2(115, 35);
    int index;
    std::string path;
    std::vector< std::vector< int > > map;

    SDL_Color fgCol = { 255, 178, 127 };
    SDL_Color bgCol = { 109, 73, 50 };

    MenuItem(int ind, SDL_Surface* spr, TTF_Font* fnt, std::string pth) : index(ind), sprite(spr), font(fnt), path(pth) { writeName(); loadMap(); };
    ~MenuItem() { debugWrite("Im free! " << index); SDL_FreeSurface(sprite); }

    void writeName();
    void loadMap() {};
};
