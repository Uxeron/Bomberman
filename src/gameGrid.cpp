#include "../include/gameGrid.hpp"
#include "../include/object.hpp"

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
        debugWrite("object being checked is outside bounds " << x << " " << y)
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


bool GameGrid::addObject(int x, int y, Object *obj) {
    if (!withinBounds(x, y)) return false;

    if (grid[x][y] == NULL) {
        grid[x][y] = obj;
        debugWrite("Moved object to " << x << " " << y)
        return true;
    } else if (grid[x][y]->name() == "character" && obj->name() == "explosion") {
        grid[x][y]->remove = true;
        grid[x][y] = obj;
        debugWrite("Killed character sitting in cell")
        return true;
    } else if (grid[x][y]->name() == "explosion" && obj->name() == "character") {
        obj->remove = true;
        debugWrite("Killed character trying to move into cell")
    }

    debugWrite("Grid position already occupied")
    return false;
}

bool GameGrid::addObject(Object *obj) {
    return addObject(obj->getX(), obj->getY(), obj);
}


bool GameGrid::removeObject(int x, int y) {
    if (!withinBounds(x, y)) return false;

    grid[x][y] = NULL;
    return true;
}

bool GameGrid::removeObject(int x, int y, Object *obj) {
    if (!withinBounds(x, y)) return false;

    if (obj == grid[x][y]) 
        return removeObject(x, y);
    return false;
}

bool GameGrid::removeObject(Object *obj) {
    removeObject(obj->getX(), obj->getY(), obj);
}


bool GameGrid::moveObject(int currX, int currY, int x, int y, Object *obj) {
    if (addObject(x, y, obj)) {
        removeObject(currX, currY, obj);
        return true;
    }
    return false;
}

bool GameGrid::moveObject(int x, int y, Object *obj) {
    return moveObject(obj->getX(), obj->getY(), x, y, obj);
}


bool GameGrid::isOccupied(int x, int y) { return grid[x][y] != NULL; }


void GameGrid::clear() {
    std::vector<std::vector<Object *> >::iterator it;
    for (it = grid.begin(); it != grid.end(); it++) {
        it->clear();
    }
    grid.clear();
}


