#include "character.hpp"

void Character::process(float delta) {
    const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
    if (currentKeyStates[SDL_SCANCODE_W])
        move(0, -2);
    
    if (currentKeyStates[SDL_SCANCODE_S]) 
        move(0, 2);
    
    if (currentKeyStates[SDL_SCANCODE_A]) 
        move(-2, 0);
    
    if (currentKeyStates[SDL_SCANCODE_D])
        move(2, 0);
}

void Character::move(int dist_x, int dist_y) {
    rect.x += dist_x;
    rect.y += dist_y;

    if (rect.x < 0)
        rect.x = 0;

    if (rect.y < 0)
        rect.y = 0;

    if (rect.x + rect.w > window->getWidth())
        rect.x = window->getWidth() - rect.w;   

    if (rect.y + rect.h > window->getHeight())
        rect.y = window->getHeight() - rect.h;
}

void Character::draw() {
    window->drawImage(sprite, &rect);
}

void Character::event(SDL_Event ev) {
    if (ev.type == SDL_KEYDOWN) {
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_SPACE) {
                const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_W])
                    move(0, -100);
                
                if (currentKeyStates[SDL_SCANCODE_S]) 
                    move(0, 100);
                
                if (currentKeyStates[SDL_SCANCODE_A]) 
                    move(-100, 0);
                
                if (currentKeyStates[SDL_SCANCODE_D])
                    move(100, 0);
        }
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_e) {
            objList.push_back(new Bomb(window, getRect()->x + pivotOffsetX, getRect()->y + pivotOffsetY));
        }
    }
}
