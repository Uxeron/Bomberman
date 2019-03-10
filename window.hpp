// Handles the main game Window, drawing to that Window and loading images
// Window is a singleton (wouldn't want multiple windows)
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

    class Window {
        Window();
        static Window* instance;
        SDL_Window*   gameWindow    = NULL;
        SDL_Surface*  ScreenSurface = NULL;
        public:
            static Window* getInstance(int screen_width, int screen_height, std::string name);
            SDL_Surface *loadSurface(std::string path);
            void free();
            void draw_image(SDL_Surface *image, int x, int y);
            void fill_screen(int r, int g, int b);
            void update();
    };
#endif