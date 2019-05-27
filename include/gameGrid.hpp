#pragma once

#include <iostream>
#include <vector>
#include "object.hpp"

#define debugWrite(message) std::cout << message << std::endl;

class GameGrid {
    void refreshSize();
    bool withinBounds(Vector2 pos);

    std::vector< std::vector< Object* > > grid; // Main grid
    Vector2 size;
    int squareSize;

  public:
    GameGrid(): size(1, 1), squareSize(1) { refreshSize(); }
    GameGrid(Vector2 gridSize, int sq) : size(gridSize), squareSize(sq) { refreshSize(); }
    ~GameGrid() { clear(); };

    void setSize(Vector2 gridSize, int sq);

    bool addObject(Object *obj, Vector2 pos);
    bool addObject(Object *obj);

    bool removeObject(Vector2 pos);
    bool removeObject(Object *obj, Vector2 pos);
    bool removeObject(Object *obj);

    bool moveObject(Object *obj, Vector2 currPos, Vector2 pos);
    bool moveObject(Object *obj, Vector2 pos);

    bool isOccupied(Vector2 pos) const { return grid[pos.x()][pos.y()] != NULL; }

    std::string getObjectName(Vector2 pos) const;
    Object* getObject(Vector2 pos) const;

    int getSqSize() const { return squareSize; };

    void clear();
};
