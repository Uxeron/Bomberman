#include "../include/gameLogic.hpp"
#include "../include/character.hpp"
#include "../include/wall.hpp"
#include "../include/wallDestr.hpp"

const int GameLogic::CELL_SIZE = 32;
const int GameLogic::SCREEN_WIDTH = 672;
const int GameLogic::SCREEN_HEIGHT = 480;
const int GameLogic::FPS = 60;
const int GameLogic::FRAME_TIME = 1000 / FPS;

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
    window = std::make_unique<Window> (SCREEN_WIDTH, SCREEN_HEIGHT, "Bomberman!");

	debugWrite("Loading game end sprites");
	for (int i = 0; i < 5; i++) sprites[i] = window->loadSurface(("Sprites/WinScreens/P" + std::to_string(i) + ".png").c_str());

	debugWrite("Creating grid")
	// Create game's grid
	grid = std::make_unique<GameGrid> (Vector2(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE), CELL_SIZE);

	debugWrite("Generating map")
	generateMap();
}


void GameLogic::stopGame() {
    debugWrite("Clearing all objects");
	// Free all leftover objects
	objList.clear();
	intObjList.clear();

	debugWrite("Freeing game ending sprites");
	for (int i = 0; i < 5; i++) SDL_FreeSurface(sprites[i]);

	debugWrite("Destroying grid")
	// Destroying grid
	grid->clear();

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
				objList.clear();

				debugWrite("Cleaning interactive objects");
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
			std::for_each(intObjList.begin(), intObjList.end(), [&](std::unique_ptr<InteractiveObject>& p) { p->event(e);});
		}

		if (gameStopped) {
			if (prevTime + FRAME_TIME > SDL_GetTicks())
				SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
			prevTime = SDL_GetTicks();
			continue;
		}

        // Call process for all objects
		intIt = intObjList.begin();
		while (intIt != intObjList.end()) {
			// Check if interactive object needs to be deleted
            if ((*intIt)->remove) {
                grid->removeObject((*intIt).get());
                intObjList.erase(intIt++);
				continue;
			}

			// Call process
            (*intIt)->process((SDL_GetTicks() - prevTime + FRAME_TIME) / 1000.0);

            // Check if there's only one character remaining
            if ((*intIt)->name() == "character" && Character::getCount() == 1) {
                gameStopped = true;
            }
			++intIt;
		}

		// All characters were removed, noone wins
		if (Character::getCount() == 0) { gameStopped = true; }

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw all objects
		std::for_each(intObjList.begin(), intObjList.end(), [&](std::unique_ptr<InteractiveObject>& p) { p->draw();});
		std::for_each(objList.begin(), objList.end(), [&](std::unique_ptr<Object>& p) { p->draw();});

		if (gameStopped) {
			auto it = std::find_if(intObjList.begin(), intObjList.end(), [&](std::unique_ptr<InteractiveObject>& p) { return (p->name() == "character");});
			if (it != intObjList.end()) {
				window->drawImage(sprites[dynamic_cast<Character*>((*it).get())->getIndex()], gameEndScreenRect);
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

bool GameLogic::addObject(Object* obj, Vector2 pos) {
    if (grid->addObject(obj, pos)) {
        if (dynamic_cast<InteractiveObject *>(obj)) {
			std::unique_ptr<InteractiveObject> intObj(dynamic_cast<InteractiveObject *>(obj));
            intObjList.push_back(std::move(intObj));
        } else {
            objList.push_back(std::move(std::unique_ptr<Object> (obj)));
		}
		return true;
    }
	return false;
}

bool GameLogic::addObject(Object* obj) {
    return addObject(obj, obj->getPos());
}

bool GameLogic::removeObject(Vector2 pos) {
	if (grid->isOccupied(pos)) {
		auto objPtr = grid->getObject(pos);

		if (dynamic_cast<InteractiveObject* > (objPtr)) {
			objPtr->remove = true;
		} else {
			auto it = std::find_if(objList.begin(), objList.end(), [&](std::unique_ptr<Object>& p) { return (p.get() == objPtr);});
			if (it == objList.end()) throw object_missing_error();
			objList.erase(it);
		}
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
				addObject(new Wall(*window.get(), CELL_SIZE, Vector2(x, y)));
			} else if (map[y][x] == '2') {
				addObject(new WallDestr(*window.get(), CELL_SIZE, Vector2(x, y)));
			} else if (map[y][x] == '3') {
				addObject(new Character(*window.get(), *this, Vector2(x, y)));
			} else {
				throw map_read_error(y, x);
			}
		}
	}
}
