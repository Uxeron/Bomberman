#pragma once

#include <iostream>
#include <vector>

class Object;

#define debugWrite(message) std::cout << message << std::endl;

class GameGrid {
    void refreshSize();
    bool withinBounds(int x, int y);

    std::vector< std::vector< Object* > > grid; // Main grid
    int sizeX;
    int sizeY;
    int squareSize;

  public:
    GameGrid(): sizeX(1), sizeY(1), squareSize(1) { refreshSize(); }
    GameGrid(int x, int y, int sq) : sizeX(x), sizeY(y), squareSize(sq) { refreshSize(); }
    ~GameGrid() { clear(); };

    void setSize(int x, int y, int sq);

    bool addObject(int x, int y, Object *obj);
    bool addObject(Object *obj);

    bool removeObject(int x, int y);
    bool removeObject(int x, int y, Object *obj);
    bool removeObject(Object *obj);

    bool moveObject(int currX, int currY, int x, int y, Object *obj);
    bool moveObject(int x, int y, Object *obj);

    bool isOccupied(int x, int y);

    int getSqSize() { return squareSize; };

    void clear();
};
