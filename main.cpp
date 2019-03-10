#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
#endif

#include <string>
#include <stdio.h>
#include "window.hpp"

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;

const int CHAR_WIDTH 	= 23;
const int CHAR_HEIGHT 	= 56;

Window *Window::instance = 0;
Window *window = NULL;

// Character's image
SDL_Surface *Character = NULL;


void stop_game() {
	// Free character's image
	SDL_FreeSurface(Character);
	Character = NULL;

	// Destroy window
	window->free();

	// Quit SDL and SDL_image
	SDL_Quit();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);	// Start SDL

	// Create the main window singleton
	window = window->getInstance(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	// Load character image
	Character = window->loadSurface("Character_Stand_Down.png");

	// Character position
	int x = 0;
	int y = 0;

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	// While application is running
	while (!quit) {
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User pressed x
			if (e.type == SDL_QUIT)
				quit = true;

			// User presses a key
			else if (e.type == SDL_KEYDOWN) {
				switch (e.key.keysym.sym) {
					case SDLK_UP:
						y -= 5;
						if (y < 0) 
							y = 0;
						break;

					case SDLK_DOWN:
						y += 5;
						if (y + CHAR_HEIGHT > SCREEN_HEIGHT)
							y = SCREEN_HEIGHT - CHAR_HEIGHT;
						break;

					case SDLK_LEFT:
						x -= 5;
						if (x < 0)
							x = 0;
						break;

					case SDLK_RIGHT:
						x += 5;
						if (x + CHAR_WIDTH > SCREEN_WIDTH)
							x = SCREEN_WIDTH - CHAR_WIDTH;
						break;
				}
			}
		}

		// Clear screen
		window->fill_screen(0, 127, 64);

		// Draw character
		window->draw_image(Character, x, y);

		// Update the screen
		window->update();
	}

	stop_game();	// Stop the game
	
	return 0; 
}
