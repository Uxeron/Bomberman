#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
#endif

#include <iostream>
#include "window.hpp"
#include "character.hpp"
#include <list>

const int SCREEN_WIDTH 	= 640;
const int SCREEN_HEIGHT = 480;

const int FPS = 60;
const int FRAME_TIME = 1000 / FPS;

Uint32 prevTime = 0;

Window *window = NULL;

std::list<Character*> chrList;
std::list<InteractiveObject*> objList;

void stopGame() {
	// Free all characters
	for (Character *chr : chrList)
		chr->free();
	chrList.clear();
	// Free all leftover objects
	for (InteractiveObject *obj : objList)
		obj->free();
	objList.clear();

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

	// Create the characters
	for (int i = 0; i < 1; i++) {
		Character *chr = new Character(window);
		chr->setSprite(loadSurface("Character_Stand_Down.png", *window));
		chrList.push_back(chr);
	}

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
			for (Character *chr : chrList)
				chr->event(e);
			// Pass events to all objects
			for (InteractiveObject *obj : objList)
				obj->event(e);
		}

		// Call process for all characters
		for (Character *chr : chrList) {
			chr->process();
			if (chr->remove) {
				chr->free();
				chrList.remove(chr);
			}
		}
		// Call process for all objects
		for (InteractiveObject *obj : objList) {
			obj->process();
			if (obj->remove) {
				obj->free();
				objList.remove(obj);
			}
		}

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw all characters
		for (Character *chr : chrList)
			chr->draw();
		// Draw all objects
		for (InteractiveObject *obj : objList)
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
