// Handles the main game Window, drawing to that Window and loading images
// Window is a singleton (wouldn't want multiple windows)
#ifndef WINDOW_H_
    #define WINDOW_H_

    #include <string>
    #include <iostream>

    #ifdef __linux__	// linux
        #include <SDL2/SDL.h>
        #include <SDL2/SDL_image.h>
    #else 				// windows
        #include "SDL2/include/SDL.h"
        #include "SDL2/include/SDL_image.h"
    #endif

    class Window {
        Window();
        static Window* instance;
        SDL_Window*   gameWindow    = NULL;
        SDL_Surface*  screenSurface = NULL;
        public:
            static Window* getInstance(int screenWidth, int screenHeight, std::string name);
            friend SDL_Surface *loadSurface(std::string path);
            void free();
            void drawImage(SDL_Surface *image, int x, int y);
            void fillScreen(int r, int g, int b);
            void update();
    };
#endif