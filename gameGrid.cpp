#include "gameGrid.hpp"

void GameGrid::refreshSize() {
    grid.resize(sizeX);
    for(auto column : grid) {
        column.resize(sizeY);
    }
}


void GameGrid::setSize(int x, int y, int sq) {
    sizeX = x;
    sizeY = y;
    squareSize = sq;
    refreshSize();
}


void GameGrid::addObject(int x, int y, InteractiveObject *obj) {
    grid[x][y].push_back(obj);
}

void GameGrid::addObject(InteractiveObject *obj) {
    grid[obj->getX()][obj->getY()].push_back(obj);
}


void GameGrid::removeObject(int x, int y, InteractiveObject *obj) {
    grid[x][y].remove(obj);
}

void GameGrid::removeObject(InteractiveObject *obj) {
    grid[obj->getX()][obj->getY()].remove(obj);
}


void GameGrid::moveObject(int currX, int currY, int x, int y, InteractiveObject *obj) {
    removeObject(currX, currY, obj);
    addObject(x, y, obj);
}
void GameGrid::moveObject(int x, int y, InteractiveObject *obj) {
    removeObject(obj->getX(), obj->getY(), obj);
    addObject(x, y, obj);
}


void GameGrid::clear(int x, int y) {
    grid[x][y].clear();
}

void GameGrid::clear() {
    for (auto column : grid) {
        for (auto cell : column) {
            cell.clear();
        }
    }
}
