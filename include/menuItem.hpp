#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_ttf.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_ttf.h"
#endif

#include <vector>
#include <fstream>
#include "vector2.hpp"
#include "exceptions.hpp"
#include "window.hpp"

class MenuItem {
  public:
    SDL_Surface* sprite;
    TTF_Font* font;
    Window& window;
    Vector2 textPos = Vector2(115, 35);
    const char* path;
    std::vector< std::vector< int > > map;
    Vector2 mapSize;
    int index;

    SDL_Color fgCol = { 255, 178, 127 };
    SDL_Color bgCol = { 109, 73, 50 };

    Uint32 mapColors[4] = {  window.MapRGB({  0, 127,  64}),
                             window.MapRGB({168, 146,  92}),
                             window.MapRGB({ 69,  40,  60}),
                             window.MapRGB({173,  13,  19}) };

    MenuItem(int ind, SDL_Surface* spr, TTF_Font* fnt, const char* pth, Window& wind);
    ~MenuItem() { SDL_FreeSurface(sprite); }

    void writeName();
    void drawIcon();
    void loadMap();

    void drawPixel(SDL_Surface* surface, int x, int y, Uint32 pixel);
};
