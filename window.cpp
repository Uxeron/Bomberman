#include "Window.hpp"

Window::Window() {
	IMG_Init(IMG_INIT_PNG);		// Start SDL_img
}

Window* Window::getInstance(int screen_width = 0, int screen_height = 0, std::string name = "") {
	if (!instance) {
		instance = new Window;

		instance->gameWindow    = SDL_CreateWindow(name.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screen_width, screen_height, SDL_WINDOW_SHOWN);
		instance->screenSurface = SDL_GetWindowSurface(instance->gameWindow);
	}

	return instance;
   }


void Window::free() {
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;

	IMG_Quit();

    delete this;
}


SDL_Surface* Window::loadSurface(std::string path) {
	// The final optimized image
	SDL_Surface *optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	// Convert surface to screen format
	optimizedSurface = SDL_ConvertSurface(loadedSurface, screenSurface->format, 0);

	// Set colorkey for transparency
	SDL_SetColorKey(optimizedSurface, SDL_TRUE, SDL_MapRGB(screenSurface->format, 255, 0, 255));

	// Get rid of old loaded surface
	SDL_FreeSurface(loadedSurface);

	return optimizedSurface;
}


void Window::drawImage(SDL_Surface *image, int x, int y) {
	SDL_Rect rect = {x, y, image->w, image->h};	// Create temporary rect
	SDL_BlitSurface(image, NULL, screenSurface, &rect);	// Blit image at position
}

void Window::fillScreen(int r, int g, int b) {
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, r, g, b));
}

void Window::update() {
	SDL_UpdateWindowSurface(gameWindow);
}