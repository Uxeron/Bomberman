#include "../include/character.hpp"

void Character::process(float delta) {
    if (bombDelayCurr > 0) bombDelayCurr -= delta;

    if (walkDelayCurr > 0) walkDelayCurr -= delta;

    if (walkDelayCurr <= 0) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            move(0, -1);
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_S]) {
            move(0, 1);
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_A]) {
            move(-1, 0);
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_D]) {
            move(1, 0);
            walkDelayCurr = walkDelay;
        }

        if (deltaX != 0 || deltaY != 0) {
            gameLogic.moveObject(this, posX + deltaX, posY + deltaY);
            deltaX = 0;
            deltaY = 0;
        }
    }
}

void Character::move(int distX, int distY) {
    deltaX += distX;
    deltaY += distY;
}

void Character::draw() {
    window.drawImage(sprite, &rect);
}

void Character::event(SDL_Event ev) {
    if (ev.type == SDL_KEYDOWN) {
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_SPACE) {
                const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
                if (currentKeyStates[SDL_SCANCODE_W])
                    move(0, -4);
                
                if (currentKeyStates[SDL_SCANCODE_S]) 
                    move(0, 4);
                
                if (currentKeyStates[SDL_SCANCODE_A]) 
                    move(-4, 0);
                
                if (currentKeyStates[SDL_SCANCODE_D])
                    move(4, 0);
        }
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_e) {
            if (bombDelayCurr <= 0) {
                gameLogic.addObject(new Bomb(window, gameLogic, posX, posY + 1));
                bombDelayCurr = bombDelay;
            }
        }
    }
}
