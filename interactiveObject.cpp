#include "interactiveObject.hpp"

InteractiveObject::~InteractiveObject() {
    SDL_FreeSurface(sprite);
    sprite = NULL;
}

void InteractiveObject::setWindow(Window* wind) {
    window = wind;
}

void InteractiveObject::setSprite(SDL_Surface *spr) {
    sprite = spr;

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
