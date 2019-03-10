// Character class
#ifndef CHARACTER_H_
    #define CHARACTER_H_

    #include "window.hpp"

    #ifdef __linux__ // linux
        #include <SDL2/SDL.h>
    #else // windows
        #include "SDL2/include/SDL.h"
    #endif

    class Character {
        SDL_Surface* sprite = NULL;
        SDL_Rect rect;
        Window* window;

    public:
        Character(Window* wind);

        void setSprite(SDL_Surface* spr);
        SDL_Surface* getSprite();

        void setPos(int x, int y);
        SDL_Rect* getRect();

        void process();
        void event(SDL_Event ev);
        void draw();

        void free();
    };
#endif