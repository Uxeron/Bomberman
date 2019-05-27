// The base class for any object
#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
#else
  #include "../SDL2/include/SDL.h"
#endif

#include <string>
#include "window.hpp"


class Object {
  protected:
    SDL_Surface* sprite = NULL;
    Rect rect;
    Window& window;
    int posX;
    int posY;
    const int cellSize;

  public:
    virtual std::string name() const = 0;
    Object(Window& wind, int cellSize): window(wind), cellSize(cellSize) {};
    Object(Window& wind, int cellSize, int x, int y)
        : window(wind), cellSize(cellSize) { setPos(x, y); };
    virtual ~Object();

    bool remove = false;
    void setWindow(Window& wind) { window = wind; };

    void setSprite(SDL_Surface* spr);
    SDL_Surface* getSprite() const { return sprite; };

    void setPos(int x, int y);
    int getX() const { return posX; };
    int getY() const { return posY; };

    virtual void draw() const = 0;
};
