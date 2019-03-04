#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
	#include <SDL2/SDL_image.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
	#include "SDL2/include/SDL_image.h"
#endif

#include <string>
#include <stdio.h>

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;

SDL_Window *Window = NULL;

// The surface contained by the window
SDL_Surface *ScreenSurface = NULL;

// Character's image
SDL_Surface *Character = NULL;

SDL_Surface *loadSurface(std::string path)
{
	// The final optimized image
	SDL_Surface *optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	
	// Convert surface to screen format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, ScreenSurface->format, 0);

	// Set colorkey for transparency
	SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(ScreenSurface->format, 255, 0, 255));

	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}


void draw_image(SDL_Surface *image, int x, int y)
{
	SDL_Rect rect = {x, y, image->w, image->h};	// Create temporary rect
	SDL_BlitSurface(image, NULL, ScreenSurface, &rect);	// Blit image at position
}


void quit() {
	// Free character's image
	SDL_FreeSurface(Character);
	Character = NULL;

	// Destroy window
	SDL_DestroyWindow(Window);
	Window = NULL;

	// Quit SDL and SDL_image
	IMG_Quit();
	SDL_Quit();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);	// Start SDL
	IMG_Init(IMG_INIT_PNG);		// Start SDL_imag

	// Create window and widow's surface
	Window = SDL_CreateWindow("Bomberman!", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	ScreenSurface = SDL_GetWindowSurface(Window);

	// Set background to white
	SDL_FillRect(ScreenSurface, NULL, SDL_MapRGB(ScreenSurface->format, 255, 255, 255));

	// Load character image
	Character = loadSurface("Character_Stand_Down.png");
	
	draw_image(Character, 100, 10);

	// Update the surface
	SDL_UpdateWindowSurface(Window);

	SDL_Delay(2000);	// Wait 2 seconds

	quit();				// Stop the game
	
	return 0; 
}
