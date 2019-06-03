#include "../include/gameLogic.hpp"
#include "../include/character.hpp"
#include "../include/wall.hpp"
#include "../include/wallDestr.hpp"

const int GameLogic::CELL_SIZE = 32;
const int GameLogic::FPS = 60;
const int GameLogic::FRAME_TIME = 1000 / FPS;

void GameLogic::startGame() {
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
			if (!e.key.repeat && e.key.state == SDL_PRESSED && e.key.keysym.sym == SDLK_ESCAPE) 
				resetGame();

			// Pass events to all objects
			std::for_each(intObjList.begin(), intObjList.end(), [&](auto& p) { p->event(e);});
		}

		if (gameStopped) {
			limitFPS();
			continue;
		}

        // Call process for all objects
		intIt = intObjList.begin();
		while (intIt != intObjList.end()) {
			// Check if interactive object needs to be removed
            if ((*intIt)->remove) {
                grid->removeObject((*intIt).get());
                intObjList.erase(intIt++);
				continue;
			}

            // Check if there's only one character remaining
            if ((*intIt)->name() == "character" && Character::getCount() == 1) {
                gameStopped = true;
                wonCharIndex = dynamic_cast<Character*>((*intIt).get())->getIndex();
				break;
            }

			// Call process
            (*intIt++)->process((SDL_GetTicks() - prevTime + FRAME_TIME) / 1000.0);
		}

		// All characters were removed, noone wins
		if (Character::getCount() == 0) { 
			gameStopped = true; 
			wonCharIndex = 4;
		}

		// Clear screen
		window->fillScreen(0, 127, 64);

		// Draw all objects
		std::for_each(intObjList.begin(), intObjList.end(), [&](auto& p) { p->draw();});
		std::for_each(objList.begin(), objList.end(), [&](auto& p) { p->draw();});

		// Draw game win message
		if (gameStopped) {
			window->drawImage(sprites[wonCharIndex], gameEndScreenRect);
			debugWrite("Stopping game");
		}

		// Update the screen
		window->update();

		// Limit framerate
		limitFPS();
	}
}

void GameLogic::resetGame() {
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
    grid->setSize(Vector2(SCREEN_WIDTH / CELL_SIZE, SCREEN_HEIGHT / CELL_SIZE),
                  CELL_SIZE);
    debugWrite("Regenerating map");
    generateMap();
}

void GameLogic::limitFPS() {
    if (prevTime + FRAME_TIME > SDL_GetTicks())
        SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
    prevTime = SDL_GetTicks();
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
			auto it = std::find_if(objList.begin(), objList.end(), [&](auto& p) { return (p.get() == objPtr);});
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
	for (int y = 0; y < mapSize.y(); y++) {
		for (int x = 0; x < mapSize.x(); x++) {
			if (map[y][x] == 0) {
				continue;
			} else if (map[y][x] == 1) {
				addObject(new Wall(*window.get(), CELL_SIZE, Vector2(x, y)));
			} else if (map[y][x] == 2) {
				addObject(new WallDestr(*window.get(), CELL_SIZE, Vector2(x, y)));
			} else if (map[y][x] == 3) {
				addObject(new Character(*window.get(), *this, Vector2(x, y)));
			} else {
				throw map_read_error(y, x);
			}
		}
	}
}
