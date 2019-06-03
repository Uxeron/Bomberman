// Handles the main game Window, drawing to that Window and loading images
#pragma once 

#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_image.h"
#endif

#include <iostream>
#include "vector2.hpp"
#include "exceptions.hpp"

struct Rect {
  Vector2 position;
  Vector2 size;
};

class Window {
    SDL_Window*   gameWindow    = NULL;
    SDL_Surface*  screenSurface = NULL;
    int width;
    int height;
public:
    Window();
    Window(int w, int h, const char* name);
    ~Window();
    SDL_Surface *loadSurface(const char* path) const;
    void drawImage(SDL_Surface *image, int x, int y);
    void drawImage(SDL_Surface *image, const Rect &rect);
    void fillScreen(int r, int g, int b);
    void update();
    int getWidth() const { return width; }
    int getHeight() const { return height; }
    Uint32 MapRGB(SDL_Color col) { return SDL_MapRGB(screenSurface->format, col.r, col.g, col.b); }
};
