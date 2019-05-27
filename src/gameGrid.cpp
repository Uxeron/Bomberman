#include "../include/gameGrid.hpp"

void GameGrid::refreshSize() {
    grid.resize(sizeX);
    std::vector<std::vector<Object *> >::iterator it;
    std::vector<Object *>::iterator it1;
    for (it = grid.begin(); it != grid.end(); it++) {
        it->resize(sizeY);
        for (it1 = it->begin(); it1 != it->end(); it1++) {
            *it1 = NULL;
        }
    }
}

bool GameGrid::withinBounds(int x, int y) {
    if (x < 0 || y < 0 || x >= sizeX || y >= sizeY) {
        debugWrite("Object being checked is outside bounds " << x << " " << y)
        return false;
    }
    return true;
}


void GameGrid::setSize(int x, int y, int sq) {
    sizeX = x;
    sizeY = y;
    squareSize = sq;
    refreshSize();
}

bool GameGrid::addObject(Object *obj, int x, int y) {
    if (!withinBounds(x, y)) return false;

    if (grid[x][y] == NULL) {
        grid[x][y] = obj;
        obj->setPos(x, y);
        return true;
    }

    debugWrite("Grid position already occupied")
    return false;
}

bool GameGrid::addObject(Object *obj) {
    return addObject(obj, obj->getX(), obj->getY());
}


bool GameGrid::removeObject(int x, int y) {
    if (!withinBounds(x, y)) return false;
    if (!isOccupied(x, y)) return false;

    grid[x][y] = NULL;
    return true;
}

bool GameGrid::removeObject(Object *obj, int x, int y) {
    if (!withinBounds(x, y)) return false;

    if (obj == grid[x][y]) 
        return removeObject(x, y);
    return false;
}

bool GameGrid::removeObject(Object *obj) {
    return removeObject(obj->getX(), obj->getY());
}

bool GameGrid::moveObject(Object *obj, int currX, int currY, int x, int y) {
    if (addObject(obj, x, y)) {
        removeObject(obj, currX, currY);
        return true;
    }
    return false;
}

bool GameGrid::moveObject(Object *obj, int x, int y) {
    return moveObject(obj, obj->getX(), obj->getY(), x, y);
}

std::string GameGrid::getObjectName(int x, int y) const {
    if (isOccupied(x, y))
        return grid[x][y]->name();
    else
        return "";
}

Object* GameGrid::getObject(int x, int y) const {
    if (isOccupied(x, y)) 
        return grid[x][y];
    else 
        return NULL;
}

void GameGrid::clear() {
    std::vector<std::vector<Object *> >::iterator it;
    for (it = grid.begin(); it != grid.end(); it++) {
        it->clear();
    }
    grid.clear();
}


