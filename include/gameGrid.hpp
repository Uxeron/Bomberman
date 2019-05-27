#pragma once

#include <iostream>
#include <vector>
#include "object.hpp"

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

    bool addObject(Object *obj, int x, int y);
    bool addObject(Object *obj);

    bool removeObject(int x, int y);
    bool removeObject(Object *obj, int x, int y);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, int currX, int currY, int x, int y);
    bool moveObject(Object *obj, int x, int y);

    bool isOccupied(int x, int y) const { return grid[x][y] != NULL; }

    std::string getObjectName(int x, int y) const;
    Object* getObject(int x, int y) const;

    int getSqSize() const { return squareSize; };

    void clear();
};
