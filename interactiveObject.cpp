#include "interactiveObject.hpp"

void InteractiveObject::free() {
    SDL_FreeSurface(sprite);
    sprite = NULL;

    delete this;
}

void InteractiveObject::setSprite(SDL_Surface *spr) {
    sprite = spr;

    rect.x = 0;
    rect.y = 0;
    rect.w = spr->w;
    rect.h = spr->h;
}

SDL_Surface *InteractiveObject::getSprite() {
    return sprite;
}

void InteractiveObject::setPos(int x, int y) {
    rect.x = x;
    rect.y = y;
}

SDL_Rect* InteractiveObject::getRect() {
    return &rect;
}