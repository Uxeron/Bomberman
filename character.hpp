// Character class
#ifndef CHARACTER_H_
    #define CHARACTER_H_

    #include "interactiveObject.hpp"

    #ifdef __linux__ // linux
        #include <SDL2/SDL.h>
    #else // windows
        #include "SDL2/include/SDL.h"
    #endif

    class Character: public InteractiveObject {
    public:
        Character(Window* wind);
        void process();
        void event(SDL_Event ev);
        void draw();
    };
#endif