#include "../include/object.hpp"

Object::~Object() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}

void Object::setSprite(SDL_Surface *spr) {
    sprite = spr;

    rect.w = spr->w;
    rect.h = spr->h;
}

void Object::setPos(int x, int y) {
    posX = x;
    posY = y;

    rect.x = x * cellSize;
    rect.y = y * cellSize;
}
