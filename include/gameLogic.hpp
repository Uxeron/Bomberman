#pragma once

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
#include <memory>
#include "gameGrid.hpp"
#include "window.hpp"
#include "exceptions.hpp"
#include "interactiveObject.hpp"

#define debugWrite(message) std::cout << message << std::endl;

class GameLogic {
    static const int CELL_SIZE;
    static const int FPS;
    static const int FRAME_TIME;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    Uint32 prevTime = 0;
    std::unique_ptr<Window> window;
    std::list<std::unique_ptr<Object> > objList;
    std::list<std::unique_ptr<InteractiveObject> > intObjList;
    std::unique_ptr<GameGrid> grid;
    SDL_Surface* sprites[5];

    std::list<std::unique_ptr<Object> >::iterator objIt;
    std::list<std::unique_ptr<InteractiveObject> >::iterator intIt;

    static const int GAME_END_SCREEN_SIZE_X = 400;
    static const int GAME_END_SCREEN_SIZE_Y = 300;
    Rect gameEndScreenRect;

    bool gameStopped = false;
    int wonCharIndex = 0;

    Vector2 mapSize;
    std::vector< std::vector< int > > map;

    void generateMap();
    void resetGame();
    void limitFPS();

  public:

    GameLogic(std::vector< std::vector< int > > mapTemp, Vector2 size) : 
        map(mapTemp), mapSize(size), SCREEN_WIDTH(size.x() * CELL_SIZE), SCREEN_HEIGHT(size.y() * CELL_SIZE) {};

    void startGame();
    void mainLoop();
    void stopGame();

    bool addObject(Object *obj, Vector2 pos);
    bool addObject(Object *obj);

    bool removeObject(Vector2 pos);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, Vector2 pos) const { return grid->moveObject(obj, pos); }

    bool isOccupied(Vector2 pos) const { return grid->isOccupied(pos); }

    std::string getObjectName(Vector2 pos) const { return grid->getObjectName(pos); }

    static int getSqSize() { return CELL_SIZE; };
};
