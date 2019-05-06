#include "../SDL2/include/SDL.h"
#include "../SDL2/include/SDL_image.h"

#include <iostream>
#include <list>
#include "gameGrid.hpp"
#include "window.hpp"

class Object;
class InteractiveObject;

#define debugWrite(message) std::cout << message << std::endl;

class GameLogic {
    static const int CELL_SIZE = 32;
    const int SCREEN_WIDTH 	= 672;
    const int SCREEN_HEIGHT = 480;
    const int FPS = 60;
    const int FRAME_TIME = 1000 / FPS;
    Uint32 prevTime = 0;
    Window *window = NULL;
    std::list<Object*> objList;
    std::list<InteractiveObject*> intObjList;
    GameGrid *grid = NULL;

    void generateMap();

  public:
    void startGame();
    void mainLoop();
    void stopGame();

    bool addObject(Object *obj, int x, int y);
    bool addObject(Object *obj);

    bool removeObject(int x, int y);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, int x, int y) { return grid->moveObject(obj, x, y); };

    bool isOccupied(int x, int y) { return grid->isOccupied(x, y); }

    std::string getObjectName(int x, int y) { return grid->getObjectName(x, y); };

    static int getSqSize() { return CELL_SIZE; };
};
