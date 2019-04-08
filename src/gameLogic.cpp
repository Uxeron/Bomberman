#include "../include/gameLogic.hpp"

void GameLogic::startGame() {
    SDL_Init(SDL_INIT_VIDEO); // Start SDL
    IMG_Init(IMG_INIT_PNG);   // Start SDL_img

    debugWrite("Creating window");
    // Create the main window
    window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

    debugWrite("Creating characters");
    // Create the characters
    for (int i = 0; i < 1; i++) {
        Character *chr = new Character(window);
		chr->setPos(0, 0);
        chr->setSprite(window->loadSurface("Sprites/Character_Stand_Down.png"));
        objList.push_back(chr);
    }
}


void GameLogic::stopGame() {
    debugWrite("Clearing all interactive objects");
	// Free all leftover objects
	for (InteractiveObject *obj : objList)
		delete obj;
	objList.clear();

    debugWrite("Destroying window");
    // Destroy window
	delete window;

    debugWrite("Stopping SDL and SDL_IMG");
    SDL_Quit(); // Quit SDL
    IMG_Quit(); // Quit SDL_img
}


void GameLogic::mainLoop() {
	// Main loop flag
	bool quit = false;

	// Event handler
	SDL_Event e;

	debugWrite("Starting main loop");
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
            obj->process((SDL_GetTicks() - prevTime + FRAME_TIME) / 100.0);
			// Pull new objects from the current object's internal list
			for(int i = 0; i < obj->objList.size();) {
				objList.push_back(obj->objList.front());
				obj->objList.pop();
			}
			// Check if object needs to be deleted
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
}
