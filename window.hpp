// Handles the main game Window, drawing to that Window and loading images
// Window is a singleton (wouldn't want multiple windows)
#pragma once 

#include <iostream>

#ifdef __linux__	// linux
    #include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
    #include "SDL2/include/SDL_image.h"
#endif

class Window {
    SDL_Window*   gameWindow    = NULL;
    SDL_Surface*  screenSurface = NULL;
    int width;
    int height;
public:
    Window();
    Window(int posX, int posY, const char* name);
    ~Window();
    SDL_Surface *loadSurface(const char* path);
    void drawImage(SDL_Surface *image, int x, int y);
    void drawImage(SDL_Surface *image, SDL_Rect *rect);
    void fillScreen(int r, int g, int b);
    void update();
    int getWidth();
    int getHeight();
};