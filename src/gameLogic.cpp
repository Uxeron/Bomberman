//#include "../include/gameLogic.hpp"
#include "../include/character.hpp"
#include "../include/wall.hpp"
#include "../include/wallDestr.hpp"

void GameLogic::startGame() {
    SDL_Init(SDL_INIT_VIDEO); // Start SDL
    IMG_Init(IMG_INIT_PNG);   // Start SDL_img

    debugWrite("Creating window");
    // Create the main window
    window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	debugWrite("Creating grid")
	// Create game's grid
	grid = new GameGrid(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE, CELL_SIZE);

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
			
			// Reset game
			if (!e.key.repeat && e.key.state == SDL_PRESSED && e.key.keysym.sym == SDLK_r) {
				for (Object *obj : objList) delete obj;
				objList.clear();

				for (InteractiveObject *obj : intObjList) delete obj;
				intObjList.clear();

				grid->clear();

				Character::resetCount();

				grid->setSize(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE, CELL_SIZE);
				generateMap();
			}
			
			// Pass events to all objects
			for (InteractiveObject *obj : intObjList) obj->event(e);
		}

		// Call process for all objects
		for (InteractiveObject *obj : intObjList) {
			// Check if object needs to be deleted
            if (obj->remove) {
				intObjList.remove(obj);
				grid->removeObject(obj);
                delete obj;
				continue;
			}

			// Call process
            obj->process((SDL_GetTicks() - prevTime + FRAME_TIME) / 1000.0);

			// Check again if object needs to be deleted
            if (obj->remove) {
				intObjList.remove(obj);
				grid->removeObject(obj);
                delete obj;
			}
		}

		for (Object *obj : objList) {
			// Check if object needs to be deleted
            if (obj->remove) {
				objList.remove(obj);
				grid->removeObject(obj);
                delete obj;
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

bool GameLogic::addObject(Object *obj, int x, int y) {
    if (grid->addObject(obj)) {
        if (dynamic_cast<InteractiveObject *>(obj))
            intObjList.push_back(dynamic_cast<InteractiveObject *>(obj));
        else
            objList.push_back(obj);
		return true;
    }
	return false;
}

bool GameLogic::addObject(Object *obj) {
    return addObject(obj, obj->getX(), obj->getY());
}

bool GameLogic::removeObject(int x, int y) {
	if (grid->isOccupied(x, y)) {
		grid->getObject(x, y)->remove = true;
		grid->removeObject(x, y);
		return true;
	}
	return false;
}

bool GameLogic::removeObject(Object *obj) {
    return removeObject(obj->getX(), obj->getY());
}


void GameLogic::generateMap() {
    const char *map[] = {
        "111111111111111111111",
        "130222222222222222001",
        "101212121212121212101",
        "122222222222222222221",
		"121212121212121212121",
		"122222222222222222221",
		"121212121212121212121",
		"122222222222222222221",
		"121212121212121212121",
		"122222222222222222221",
		"121212121212121212121",
		"122222222222222222221",
		"101212121212121212101",
		"100222222222222222001",
		"111111111111111111111",
    };

	for (int x = 0; x < SCREEN_WIDTH/CELL_SIZE; x++) {
		for (int y = 0; y < SCREEN_HEIGHT/CELL_SIZE; y++) {
			if (map[y][x] == '1') {
				Wall *wall = new Wall(*window, CELL_SIZE, x, y);
				objList.push_back(wall);
				grid->addObject(wall);
			} else if (map[y][x] == '2') {
				WallDestr *wall = new WallDestr(*window, CELL_SIZE, x, y);
				objList.push_back(wall);
				grid->addObject(wall);
			} else if (map[y][x] == '3') {
				Character *chr = new Character(*window, *this, x, y);
				chr->setSprite(window->loadSurface("Sprites/Character/Walk_Down/3.png"));
				intObjList.push_back(chr);
				grid->addObject(chr);
			}
		}
	}
}
