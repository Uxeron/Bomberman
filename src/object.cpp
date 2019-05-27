#include "../include/object.hpp"

Object::~Object() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}

void Object::setSprite(SDL_Surface *spr) {
    sprite = spr;

    rect.size.x(spr->w);
    rect.size.y(spr->w);
}

void Object::setPos(int x, int y) {
    pos.x(x);
    pos.y(y);

    rect.position.x(x * cellSize);
    rect.position.y(y * cellSize);
}

void Object::setPos(Vector2 position) {
    pos = position;

    rect.position.x(position.x() * cellSize);
    rect.position.y(position.y() * cellSize);
    //rect.position *= cellSize;
}
