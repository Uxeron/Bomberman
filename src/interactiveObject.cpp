#include "../include/interactiveObject.hpp"

InteractiveObject::~InteractiveObject() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}
