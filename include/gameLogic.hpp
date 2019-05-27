#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_image.h"
#endif

#include <iostream>
#include <list>
#include <algorithm>
#include "gameGrid.hpp"
#include "window.hpp"

class Object;
class InteractiveObject;

#define debugWrite(message) std::cout << message << std::endl;

class GameLogic {
    static const int CELL_SIZE = 32;
    static const int SCREEN_WIDTH 	= 672;
    static const int SCREEN_HEIGHT = 480;
    static const int FPS = 60;
    static const int FRAME_TIME = 1000 / FPS;
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
    bool addObjectnoList(Object *obj) const { return grid->addObject(obj); }

    bool removeObject(int x, int y);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, int x, int y) const { return grid->moveObject(obj, x, y); }

    bool isOccupied(int x, int y) const { return grid->isOccupied(x, y); }

    std::string getObjectName(int x, int y) const { return grid->getObjectName(x, y); }

    static int getSqSize() { return CELL_SIZE; };

    static void deleteObj(Object *obj) { delete obj; };
};
