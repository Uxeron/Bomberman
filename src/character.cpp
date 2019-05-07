#include "../include/character.hpp"

int Character::count = 0;

Character::Character(Window& wind, GameLogic& logic) : InteractiveObject(wind, logic) {
    setSprite(window.loadSurface(("Sprites/Character/" + std::to_string(index) + "/Walk_Down/3.png").c_str()));
}
Character::Character(Window& wind, GameLogic& logic, int x, int y): InteractiveObject(wind, logic, x, y) {
    setSprite(window.loadSurface(("Sprites/Character/" + std::to_string(index) + "/Walk_Down/3.png").c_str()));
}

Character::~Character() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}

void Character::process(float delta) {
    if (bombDelayCurr > 0) bombDelayCurr -= delta;

    if (walkDelayCurr > 0) walkDelayCurr -= delta;

    if (walkDelayCurr <= 0) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            move(0, -1);
            lastDir = 0;
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_S]) {
            move(0, 1);
            lastDir = 2;
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_A]) {
            move(-1, 0);
            lastDir = 3;
            walkDelayCurr = walkDelay;
        } else if (currentKeyStates[SDL_SCANCODE_D]) {
            move(1, 0);
            lastDir = 1;
            walkDelayCurr = walkDelay;
        }
    }
}

void Character::move(int distX, int distY) {
    if (!gameLogic.moveObject(this, posX + distX, posY + distY)) {
        if (gameLogic.getObjectName(posX + distX, posY + distY) == "powerupSpeed") {
            if (walkDelay > 0.03) walkDelay -= 0.02;
            gameLogic.removeObject(posX + distX, posY + distY);
            gameLogic.moveObject(this, posX + distX, posY + distY);
        } else if (gameLogic.getObjectName(posX + distX, posY + distY) == "powerupBomb") {
            bombStepAdjust += 1;
            gameLogic.removeObject(posX + distX, posY + distY);
            gameLogic.moveObject(this, posX + distX, posY + distY);
        }
    }
}

void Character::draw() {
    window.drawImage(sprite, &rect);
}

void Character::event(SDL_Event ev) {
    if (ev.type == SDL_KEYDOWN) {
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_e) {
            if (bombDelayCurr <= 0) {
                Bomb* bomb;
                switch (lastDir) {
                    case 0:
                        bomb = new Bomb(window, gameLogic, posX, posY + 1);
                        bomb->adjustDelay(bombStepAdjust);
                        gameLogic.addObject(bomb);
                        break;
                    case 1:
                        bomb = new Bomb(window, gameLogic, posX - 1, posY);
                        bomb->adjustDelay(bombStepAdjust);
                        gameLogic.addObject(bomb);
                        break;
                    case 2:
                        bomb = new Bomb(window, gameLogic, posX, posY - 1);
                        bomb->adjustDelay(bombStepAdjust);
                        gameLogic.addObject(bomb);
                        break;
                    case 3:
                        bomb = new Bomb(window, gameLogic, posX + 1, posY);
                        bomb->adjustDelay(bombStepAdjust);
                        gameLogic.addObject(bomb);
                        break;

                    default:
                        break;
                }
                
                bombDelayCurr = bombDelay;
            }
        }
    }
}
