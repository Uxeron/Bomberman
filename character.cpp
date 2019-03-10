#include "character.hpp"

Character::Character(Window* wind) {
    window = wind;
}

void Character::process() {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W]) {
        rect.y -= 2;
        if (rect.y < 0)
            rect.y = 0;
    }
    if (currentKeyStates[SDL_SCANCODE_S]) {
        rect.y += 2;
        if (rect.y + rect.h > window->getHeight())
            rect.y = window->getHeight() - rect.h;
    }
    if (currentKeyStates[SDL_SCANCODE_A]) {
        rect.x -= 2;
        if (rect.x < 0)
            rect.x = 0;
    }
    if (currentKeyStates[SDL_SCANCODE_D]){
        rect.x += 2;
        if (rect.x + rect.w > window->getWidth())
            rect.x = window->getWidth() - rect.w;
    }
}

void Character::draw() {
    window->drawImage(sprite, &rect);
}

void Character::event(SDL_Event ev) {}
