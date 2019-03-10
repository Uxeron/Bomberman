#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
#endif

#include <string>
#include <iostream>
#include "window.hpp"
#include "character.hpp"

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;

const int FPS = 60;
const int FRAME_TIME = 1000 / FPS;

Uint32 prevTime = 0;

Window *window = NULL;

// Main character
Character *character = NULL;


void stopGame() {
	// Free main character
	character->free();

	// Destroy window
	window->free();

	// Quit SDL and SDL_image
	SDL_Quit();
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);	// Start SDL

	// Create the main window singleton
	window = Window::getInstance();
	window->create(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	// Create the main character
	character = new Character(window);
	character->setSprite(loadSurface("Character_Stand_Down.png", *window));

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
			
			character->event(e);
		}

		// Process character's functions
		character->process();

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw character
		character->draw();

		// Update the screen
		window->update();

		if (prevTime + FRAME_TIME > SDL_GetTicks())
			SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
		prevTime = SDL_GetTicks();
	}

	stopGame();	// Stop the game
	
	return 0; 
}
