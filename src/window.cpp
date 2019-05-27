#include "../include/window.hpp"

Window::Window(int w, int h, const char* name): width(w), height(h) {
	gameWindow = SDL_CreateWindow(name, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(gameWindow);
}

Window::Window(): width(640), height(480) {
	gameWindow = SDL_CreateWindow("Window", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	screenSurface = SDL_GetWindowSurface(gameWindow);
}

Window::~Window() {
	SDL_DestroyWindow(gameWindow);
	gameWindow = NULL;
}


SDL_Surface* Window::loadSurface(const char* path) const {
	// The final optimized image
	SDL_Surface *optimizedSurface = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path);

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

void Window::drawImage(SDL_Surface *image, const Rect &rect) {
	SDL_Rect rect_c = {rect.position.x(), rect.position.y(), rect.size.x(), rect.size.y()};	// Create temporary rect
	SDL_BlitSurface(image, NULL, screenSurface, &rect_c); // Blit image at position
}

void Window::fillScreen(int r, int g, int b) {
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, r, g, b));
}

void Window::update() {
	SDL_UpdateWindowSurface(gameWindow);
}

