//#include "../include/gameLogic.hpp"
#include "../include/character.hpp"
#include "../include/wall.hpp"
#include "../include/wallDestr.hpp"

void GameLogic::startGame() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) // Start SDL
		throw SDL_init_error();

    if (IMG_Init(IMG_INIT_PNG) == 0)   // Start SDL_img
		throw SDL_Image_init_error();

	gameEndScreenRect.position.x((SCREEN_WIDTH - GAME_END_SCREEN_SIZE_X) / 2);
	gameEndScreenRect.position.y((SCREEN_HEIGHT - GAME_END_SCREEN_SIZE_Y) / 2);
	gameEndScreenRect.size.x(GAME_END_SCREEN_SIZE_X);
	gameEndScreenRect.size.y(GAME_END_SCREEN_SIZE_Y);

    debugWrite("Creating window");
    // Create the main window
    window = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	debugWrite("Loading game end sprites");
	for (int i = 0; i < 5; i++) sprites[i] = window->loadSurface(("Sprites/WinScreens/P" + std::to_string(i) + ".png").c_str());

	debugWrite("Creating grid")
	// Create game's grid
	grid = new GameGrid(Vector2(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE), CELL_SIZE);

	debugWrite("Generating map")
	generateMap();
}


void GameLogic::stopGame() {
    debugWrite("Clearing all interactive objects");
	// Free all leftover objects
	std::for_each(objList.begin(), objList.end(), deleteObj);
	objList.clear();

	std::for_each(intObjList.begin(), intObjList.end(), deleteObj);
	intObjList.clear();

	for (int i = 0; i < 5; i++) SDL_FreeSurface(sprites[i]);

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
				gameStopped = false;
				debugWrite("Cleaning objects");
				std::for_each(objList.begin(), objList.end(), deleteObj);
				objList.clear();

				debugWrite("Cleaning interactive objects");
				std::for_each(intObjList.begin(), intObjList.end(), deleteObj);
				intObjList.clear();

				debugWrite("Cleaning grid");
				grid->clear();

				debugWrite("Resetting counter");
				Character::resetCount();

				debugWrite("Reseting grid");
				grid->setSize(Vector2(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE), CELL_SIZE);
				debugWrite("Regenerating map");
				generateMap();
			}

			// Pass events to all objects
			for (InteractiveObject *obj : intObjList) obj->event(e);
		}

		if (gameStopped) {
			if (prevTime + FRAME_TIME > SDL_GetTicks())
				SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
			prevTime = SDL_GetTicks();
			continue;
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
			} else {
				if (obj->name() == "character" && Character::getCount() == 1) {	// The last character remaining, wins game
					gameStopped = true;
				}
            }
		}

		if (Character::getCount() == 0) {	// All characters were removed, noone wins
			gameStopped = true;
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

		if (gameStopped) {
			std::list<InteractiveObject*>::iterator it = std::find_if(intObjList.begin(), intObjList.end(), isCharacter);
			if (it != intObjList.end()) {
				window->drawImage(sprites[dynamic_cast<Character*>(*it)->getIndex()], gameEndScreenRect);
			} else {
				window->drawImage(sprites[4], gameEndScreenRect);
			}
			debugWrite("Stopping game");
		}

		// Update the screen
		window->update();

		// Limit framerate
		if (prevTime + FRAME_TIME > SDL_GetTicks())
			SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
		prevTime = SDL_GetTicks();
	}
}

bool GameLogic::addObject(Object *obj, Vector2 pos) {
    if (grid->addObject(obj, pos)) {
        if (dynamic_cast<InteractiveObject *>(obj)) {
            intObjList.push_back(dynamic_cast<InteractiveObject *>(obj));
		} else {
            objList.push_back(obj);
		}
		return true;
    }
	return false;
}

bool GameLogic::addObject(Object *obj) {
    return addObject(obj, obj->getPos());
}

bool GameLogic::removeObject(Vector2 pos) {
	if (grid->isOccupied(pos)) {
		grid->getObject(pos)->remove = true;
		grid->removeObject(pos);
		return true;
	}
	return false;
}

bool GameLogic::removeObject(Object *obj) {
    return removeObject(obj->getPos());
}


void GameLogic::generateMap() {
    const char* map[] = {
        "111111111111111111111",
        "130222222222222222031",
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
		"130222222222222222031",
		"111111111111111111111",
    };

	for (int y = 0; y < SCREEN_HEIGHT/CELL_SIZE; y++) {
		for (int x = 0; x < SCREEN_WIDTH/CELL_SIZE; x++) {
			if (map[y][x] == '0') {
				continue;
			} else if (map[y][x] == '1') {
				Wall *wall = new Wall(*window, CELL_SIZE, Vector2(x, y));
				objList.push_back(wall);
				grid->addObject(wall);
			} else if (map[y][x] == '2') {
				WallDestr *wall = new WallDestr(*window, CELL_SIZE, Vector2(x, y));
				objList.push_back(wall);
				grid->addObject(wall);
			} else if (map[y][x] == '3') {
				addObject(new Character(*window, *this, Vector2(x, y)));
			} else {
				throw map_read_error(y, x);
			}
		}
	}
}
