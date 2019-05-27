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
    Vector2 pos;
    const int cellSize;

  public:
    virtual std::string name() const = 0;
    Object(Window& wind, int cellSize): window(wind), cellSize(cellSize) {};
    Object(Window& wind, int cellSize, Vector2 position)
        : window(wind), cellSize(cellSize) { setPos(position); };
    virtual ~Object();

    bool remove = false;
    void setWindow(Window& wind) { window = wind; };

    void setSprite(SDL_Surface* spr);
    SDL_Surface* getSprite() const { return sprite; };

    void setPos(int x, int y);
    void setPos(Vector2 position);
    Vector2 getPos() const { return pos; }
    int getX() const { return pos.x(); };
    int getY() const { return pos.y(); };

    virtual void draw() const = 0;
};
