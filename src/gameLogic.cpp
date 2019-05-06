#include "../include/gameLogic.hpp"

void GameLogic::startGame() {
    SDL_Init(SDL_INIT_VIDEO); // Start SDL
    IMG_Init(IMG_INIT_PNG);   // Start SDL_img

    debugWrite("Creating window");
    // Create the main window
    window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	debugWrite("Creating grid")
	// Create game's grid
	grid = new GameGrid(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE, CELL_SIZE);

    debugWrite("Creating characters");
    // Create the characters
    for (int i = 0; i < 1; i++) {
        Character *chr = new Character(*window, *grid, 1, 1);
        chr->setSprite(window->loadSurface("Sprites/Character/Walk_Down/3.png"));
        intObjList.push_back(chr);
        grid->addObject(chr);
    }

	generateMap();
}


void GameLogic::stopGame() {
    debugWrite("Clearing all interactive objects");
	// Free all leftover objects
	for (Object *obj : objList) delete obj;
	objList.clear();

	for (InteractiveObject *obj : intObjList) delete obj;
	intObjList.clear();

	debugWrite("Destroying grid")
	// Destroying grid
	grid->clear();
	delete grid;

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
			for (InteractiveObject *obj : intObjList) obj->event(e);
		}

		// Call process for all objects
		for (InteractiveObject *obj : intObjList) {
            obj->process((SDL_GetTicks() - prevTime + FRAME_TIME) / 1000.0);
			// Pull new objects from the current object's internal list
			for(int i = 0; i < obj->objList.size();) {
				Object* currObj = obj->objList.front();
				if (grid->addObject(currObj)) {
					if(dynamic_cast<InteractiveObject*>(currObj)) 
						intObjList.push_back(dynamic_cast<InteractiveObject*>(currObj));
					else
						objList.push_back(currObj);
				}
				obj->objList.pop();
			}
			// Check if object wants to move on the grid
			if (obj->deltaX != 0 || obj->deltaY != 0) {
				if (grid->moveObject(obj, obj->getX() + obj->deltaX, obj->getY() + obj->deltaY)) { // If moved successfully
					obj->setPos(obj->getX() + obj->deltaX, obj->getY() + obj->deltaY);
				}
				obj->deltaX = 0;
				obj->deltaY = 0;
			}
			// Check if object needs to be deleted
            if (obj->remove) {
                delete obj;
				intObjList.remove(obj);
				grid->removeObject(obj);
			}
		}

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw all objects
		for (Object *obj : objList) obj->draw();
		for (InteractiveObject *obj : intObjList) obj->draw();

		// Update the screen
		window->update();

		// Limit framerate
		if (prevTime + FRAME_TIME > SDL_GetTicks())
			SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
		prevTime = SDL_GetTicks();
	}
}

void GameLogic::generateMap() {
    const char *map[] = {
        "111111111111111111111",
        "100000000000000000001",
        "101010101010101010101",
        "100000000000000000001",
		"101010101010101010101",
		"100000000000000000001",
		"101010101010101010101",
		"100000000000000000001",
		"101010101010101010101",
		"100000000000000000001",
		"101010101010101010101",
		"100000000000000000001",
		"101010101010101010101",
		"100000000000000000001",
		"111111111111111111111",
    };

	for (int x = 0; x < SCREEN_WIDTH/CELL_SIZE; x++) {
		for (int y = 0; y < SCREEN_HEIGHT/CELL_SIZE; y++) {
			if (map[y][x] == '1') {
				Wall *wall = new Wall(*window, CELL_SIZE, x, y);
				objList.push_back(wall);
				grid->addObject(wall);
			}
		}
	}
}
