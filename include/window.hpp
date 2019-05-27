// Handles the main game Window, drawing to that Window and loading images
#pragma once 

#include <iostream>

#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_image.h"


struct Rect {
  int x;
  int y;
  int w;
  int h;
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
};
