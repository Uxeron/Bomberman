#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#else 				// windows
    #include "../SDL2/include/SDL.h"
	#include "../SDL2/include/SDL_image.h"
#endif

#include <iostream>
#include <list>
#include "../include/character.hpp"
#include "../include/window.hpp"

#define debugWrite(message) std::cout << message << std::endl;

class GameLogic {
    const int SCREEN_WIDTH 	= 640;
    const int SCREEN_HEIGHT = 480;
    const int FPS = 60;
    const int FRAME_TIME = 1000 / FPS;
    Uint32 prevTime = 0;
    Window *window = NULL;
    std::list<InteractiveObject*> objList;

  public:
    void startGame();
    void mainLoop();
    void stopGame();
};
