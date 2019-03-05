// Handles the main game window, drawing to that window and loading images
#ifndef WINDOW_H_
    #define WINDOW_H_

    #include <string>

    #ifdef __linux__	// linux
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
    #else 				// windows
        #include "SDL2/include/SDL.h"
        #include "SDL2/include/SDL_image.h"
    #endif

    class window {
        SDL_Window  *gameWindow = NULL;
        SDL_Surface *ScreenSurface = NULL;
        public:
            static window* create(int screen_width, int screen_height, std::string name);
            void free();
            SDL_Surface *loadSurface(std::string path);
            void draw_image(SDL_Surface *image, int x, int y);
            void fill_screen(int r, int g, int b);
            void update();
    };
#endif