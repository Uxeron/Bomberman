#include "window.hpp"

window* window::create(int screen_width, int screen_height, std::string name) {
	window* win = new window;

	win->gameWindow = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
	win->ScreenSurface = SDL_GetWindowSurface(win->gameWindow);

    return win;
}


void window::free() {
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;

    delete this;
}


SDL_Surface* window::loadSurface(std::string path) {
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


void window::draw_image(SDL_Surface *image, int x, int y) {
	SDL_Rect rect = {x, y, image->w, image->h};	// Create temporary rect
	SDL_BlitSurface(image, NULL, ScreenSurface, &rect);	// Blit image at position
}

void window::fill_screen(int r, int g, int b) {
	SDL_FillRect(ScreenSurface, NULL, SDL_MapRGB(ScreenSurface->format, r, g, b));
}

void window::update() {
	SDL_UpdateWindowSurface(gameWindow);
}