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
#include "exceptions.hpp"

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
    Window* window = NULL;
    std::list<Object*> objList;
    std::list<InteractiveObject*> intObjList;
    GameGrid* grid = NULL;
    SDL_Surface* sprites[5];

    static const int GAME_END_SCREEN_SIZE_X = 400;
    static const int GAME_END_SCREEN_SIZE_Y = 300;
    Rect gameEndScreenRect;

    bool gameStopped = false;

    void generateMap();

  public:
    void startGame();
    void mainLoop();
    void stopGame();

    bool addObject(Object *obj, Vector2 pos);
    bool addObject(Object *obj);
    bool addObjectnoList(Object *obj) const { return grid->addObject(obj); }

    bool removeObject(Vector2 pos);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, Vector2 pos) const { return grid->moveObject(obj, pos); }

    bool isOccupied(Vector2 pos) const { return grid->isOccupied(pos); }

    std::string getObjectName(Vector2 pos) const { return grid->getObjectName(pos); }

    static int getSqSize() { return CELL_SIZE; };

    static void deleteObj(Object *obj) { delete obj; };
    static bool isCharacter(Object *obj) { return obj->name() == "character"; };
};
