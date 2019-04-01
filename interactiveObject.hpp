// The base class for any object that can be interacted with (characters, bombs, etc)
#pragma once 

#include "window.hpp"

#ifdef __linux__ // linux
    #include <SDL2/SDL.h>
#else // windows
    #include "SDL2/include/SDL.h"
#endif

class InteractiveObject {
protected:
    SDL_Surface* sprite = NULL;
    SDL_Rect rect;
    Window* window = NULL;

public:
    InteractiveObject();
    InteractiveObject(Window* wind): window(wind) {};
    ~InteractiveObject();

    bool remove = false;
    void setWindow(Window* window);

    void setSprite(SDL_Surface* spr);
    SDL_Surface* getSprite();

    void setPos(int x, int y);
    SDL_Rect* getRect();

    virtual void process() = 0;
    virtual void event(SDL_Event ev) = 0;
    virtual void draw() = 0;
};
