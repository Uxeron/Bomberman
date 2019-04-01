#ifdef __linux__	// linux
	#include <SDL2/SDL.h>
    #include <SDL2/SDL_image.h>
#else 				// windows
    #include "SDL2/include/SDL.h"
	#include "SDL2/include/SDL_image.h"
#endif

#ifdef DEBUG
	#define debugWrite(message) std::cout << message << std::endl;
#else
	#define debugWrite(message);
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

std::list<InteractiveObject*> objList;

void stopGame() {
	// Free all leftover objects
	for (InteractiveObject *obj : objList)
		delete obj;
	objList.clear();

	// Destroy window
	delete window;

	// Quit SDL and SDL_image
	SDL_Quit();
	IMG_Quit(); // Stop SDL_img
}

int main(int argc, char *args[]) {
	SDL_Init(SDL_INIT_VIDEO);	// Start SDL
	IMG_Init(IMG_INIT_PNG);		// Start SDL_img

	debugWrite("Creating window");
	// Create the main window singleton
	window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	debugWrite("Creating characters");
	// Create the characters
	for (int i = 0; i < 1; i++) {
		Character *chr = new Character(window);
		chr->setSprite(window->loadSurface("Character_Stand_Down.png"));
		objList.push_back(chr);
	}

	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;
	debugWrite("Starting main loop");
	// While application is running
	while (!quit) {
		// Handle events on queue
		while (SDL_PollEvent(&e) != 0) {
			// User pressed x
			if (e.type == SDL_QUIT)
				quit = true;
			
			// Pass events to all objects
			for (InteractiveObject *obj : objList)
				obj->event(e);
		}

		// Call process for all objects
		for (InteractiveObject *obj : objList) {
			obj->process();
			if (obj->remove) {
				delete obj;
				objList.remove(obj);
			}
		}

		// Clear screen
		window->fillScreen(0, 127, 64);

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
