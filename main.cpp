#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
#endif

#include <iostream>
#include "window.hpp"
#include "character.hpp"

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;

const int FPS = 60;
const int FRAME_TIME = 1000 / FPS;

Uint32 prevTime = 0;

Window *window = NULL;

Character* characterList[4] = {NULL};
InteractiveObject* objectList[20] = {NULL};

void stopGame() {
	// Free all characters
	for (Character *chr : characterList)
		if (chr != NULL)
			chr->free();
	// Free all leftover objects
	for (InteractiveObject *obj : objectList)
		if (obj != NULL)
			obj->free();

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
	characterList[0] = new Character(window);
	characterList[0]->setSprite(loadSurface("Character_Stand_Down.png", *window));

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
			
			// Pass events to all characters
			for(Character* chr: characterList)
				if (chr != NULL)
					chr->event(e);
			// Pass events to all objects
			for (InteractiveObject *obj : objectList)
				if (obj != NULL)
					obj->event(e);
		}

		// Call process for all characters
		for (Character *chr : characterList) {
			if (chr != NULL) {
				chr->process();
				if (chr->remove) {
					chr->free();
					chr = NULL;
				}
			}
		}
		// Call process for all objects
		for (InteractiveObject *obj : objectList) {
			if (obj != NULL) {
				obj->process();
				if (obj->remove) {
					obj->free();
					obj = NULL;
				}
			}
		}

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw all characters
		for (Character *chr : characterList)
			if (chr != NULL)
				chr->draw();
		// Draw all objects
		for (InteractiveObject *obj : objectList)
			if (obj != NULL)
				obj->draw();

		// Update the screen
		window->update();

		// Limit framerate
		if (prevTime + FRAME_TIME > SDL_GetTicks())
			SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
		prevTime = SDL_GetTicks();
	}

	stopGame();	// Stop the game
	
	return 0; 
}
