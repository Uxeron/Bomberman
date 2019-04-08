#pragma once

#include "../include/interactiveObject.hpp"
#include <vector>
#include <list>

class GameGrid {
    void refreshSize();

    std::vector< std::vector< std::list<InteractiveObject*> > > grid; // Main grid
    int sizeX;
    int sizeY;
    int squareSize;

  public:
    GameGrid(): sizeX(1), sizeY(1), squareSize(1) { refreshSize(); }
    GameGrid(int x, int y, int sq) : sizeX(x), sizeY(y), squareSize(sq) { refreshSize(); }
    ~GameGrid() { clear(); };

    void setSize(int x, int y, int sq);

    void addObject(int x, int y, InteractiveObject *obj);
    void addObject(InteractiveObject *obj);

    void removeObject(int x, int y, InteractiveObject *obj);
    void removeObject(InteractiveObject *obj);

    void moveObject(int currX, int currY, int x, int y, InteractiveObject *obj);
    void moveObject(int x, int y, InteractiveObject *obj);

    void clear(int x, int y);
    void clear();
};
