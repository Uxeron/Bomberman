#include "../include/gameGrid.hpp"

void GameGrid::refreshSize() {
    grid.resize(size.x());
    std::vector<std::vector<Object *> >::iterator it;
    std::vector<Object *>::iterator it1;
    for (it = grid.begin(); it != grid.end(); it++) {
        it->resize(size.y());
        for (it1 = it->begin(); it1 != it->end(); it1++) {
            *it1 = NULL;
        }
    }
}

bool GameGrid::withinBounds(Vector2 pos) {
    if (pos.x() < 0 || pos.y() < 0 || pos.x() >= size.x() || pos.y() >= size.y()) {
        debugWrite("Object being checked is outside bounds " << pos.x() << " " << pos.y())
        return false;
    }
    return true;
}


void GameGrid::setSize(Vector2 gridSize, int sq) {
    size = gridSize;
    squareSize = sq;
    refreshSize();
}

bool GameGrid::addObject(Object *obj, Vector2 pos) {
    if (!withinBounds(pos)) return false;

    if (grid[pos.x()][pos.y()] == NULL) {
        grid[pos.x()][pos.y()] = obj;
        obj->setPos(pos);
        return true;
    }

    return false;
}

bool GameGrid::addObject(Object *obj) {
    return addObject(obj, obj->getPos());
}


bool GameGrid::removeObject(Vector2 pos) {
    if (!withinBounds(pos)) return false;
    if (!isOccupied(pos)) return false;

    grid[pos.x()][pos.y()] = NULL;
    return true;
}

bool GameGrid::removeObject(Object *obj, Vector2 pos) {
    if (!withinBounds(pos)) return false;

    if (obj == grid[pos.x()][pos.y()]) 
        return removeObject(pos);
    return false;
}

bool GameGrid::removeObject(Object *obj) {
    return removeObject(obj->getPos());
}

bool GameGrid::moveObject(Object *obj, Vector2 currPos, Vector2 pos) {
    if (addObject(obj, pos)) {
        removeObject(obj, currPos);
        return true;
    }
    return false;
}

bool GameGrid::moveObject(Object *obj, Vector2 pos) {
    return moveObject(obj, obj->getPos(), pos);
}

std::string GameGrid::getObjectName(Vector2 pos) const {
    if (isOccupied(pos))
        return grid[pos.x()][pos.y()]->name();
    else
        return "";
}

Object* GameGrid::getObject(Vector2 pos) const {
    if (isOccupied(pos)) 
        return grid[pos.x()][pos.y()];
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


