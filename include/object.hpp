// The base class for any object
#pragma once

#include <queue>
#include <string>
#include "../include/window.hpp"
#include "../SDL2/include/SDL.h"

class Object {
  protected:
    SDL_Surface* sprite = NULL;
    SDL_Rect rect;
    Window* window = NULL;
    int posX;
    int posY;
    int CELL_SIZE;

  public:
    virtual std::string name() = 0;
    std::queue<Object*> objList;
    Object(Window* wind, int cellSize): window(wind), CELL_SIZE(cellSize){};
    Object(Window* wind, int cellSize, int x, int y): window(wind), CELL_SIZE(cellSize) { setPos(x, y); };
    ~Object();

    bool remove = false;
    void setWindow(Window* window);

    void setSprite(SDL_Surface* spr);
    SDL_Surface* getSprite();

    void setPos(int x, int y);
    int getX();
    int getY();

    virtual void draw() = 0;
};
