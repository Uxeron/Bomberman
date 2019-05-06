#include "../include/Object.hpp"

Object::~Object() {
    SDL_FreeSurface(sprite);
    sprite = NULL;
}

void Object::setWindow(Window &wind) { window = wind; }

void Object::setSprite(SDL_Surface *spr) {
    sprite = spr;

    rect.w = spr->w;
    rect.h = spr->h;
}

SDL_Surface *Object::getSprite() { return sprite; }

void Object::setPos(int x, int y) {
    posX = x;
    posY = y;

    rect.x = x * CELL_SIZE;
    rect.y = y * CELL_SIZE;
}

int Object::getX() { return posX; }

int Object::getY() { return posY; }
