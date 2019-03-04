#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
#endif


//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//The window we'll be rendering to
SDL_Window *gWindow = NULL;

//The surface contained by the window
SDL_Surface *gScreenSurface = NULL;


void quit() {
	//Destroy window
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;

	// Quit SDL
	SDL_Quit();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO); // Start SDL

	// Create window and widow's surface
	gWindow = SDL_CreateWindow("Bomberman!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	gScreenSurface = SDL_GetWindowSurface(gWindow);

	SDL_Delay(2000);	// Wait 2 seconds

	quit();				// Stop the game
	
	return 0; 
}
