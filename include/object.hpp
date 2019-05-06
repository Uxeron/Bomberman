// The base class for any object
#pragma once

#include <queue>
#include <string>
#include "window.hpp"
#include "../SDL2/include/SDL.h"

class Object {
  protected:
    SDL_Surface* sprite = NULL;
    SDL_Rect rect;
    Window& window;
    int posX;
    int posY;
    const int cellSize;

  public:
    virtual std::string name() = 0;
    std::queue<Object*> objList;
    Object(Window& wind, int cellSize): window(wind), cellSize(cellSize) {};
    Object(Window& wind, int cellSize, int x, int y)
        : window(wind), cellSize(cellSize) { setPos(x, y); };
    ~Object();

    bool remove = false;
    void setWindow(Window& wind) { window = wind; };

    void setSprite(SDL_Surface* spr);
    SDL_Surface* getSprite() { return sprite; };

    void setPos(int x, int y);
    int getX() { return posX; };
    int getY() { return posY; };

    virtual void draw() = 0;
};
