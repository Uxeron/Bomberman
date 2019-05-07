#include "../include/bomb.hpp"

Bomb::Bomb(Window& wind, GameLogic& logic, int x, int y): InteractiveObject(wind, logic, x, y) {
    sprites[0] = window.loadSurface("Sprites/Bomb/0.png");
    sprites[1] = window.loadSurface("Sprites/Bomb/1.png");

    setSprite(sprites[0]);
    currTime = stepTime;
}

Bomb::~Bomb() {
    for (SDL_Surface *spr : sprites){
        SDL_FreeSurface(spr);
    }
    sprite = NULL;
}

void Bomb::process(float delta) {
    currTime -= delta;
    if (currTime < 0.0) {
        if (exploding) {
            currTime = explosionStepTime;
            explosionStep++;
            if (explosionStep >= endExplosionStep) {
                remove = true;
            } else {
                addExplosion(posX + explosionStep, posY, right);
                addExplosion(posX - explosionStep, posY, left);
                addExplosion(posX, posY + explosionStep, down);
                addExplosion(posX, posY - explosionStep, up);
            }
        } else {
            currTime = stepTime;
            step++;
            if (step >= explodeOnStep) {
                exploding = true;
                currTime = explosionStepTime;
            }
            else {
                setSprite(sprites[step%2]);
            }
        }
    }
}

void Bomb::addExplosion(int x, int y, bool &condition) {
    if (condition) {
        if (!gameLogic.isOccupied(x, y)) {
            gameLogic.addObject(new Explosion(window, gameLogic, x, y));
        } else {
            if (destructibleObjects.find(gameLogic.getObjectName(x, y)) != destructibleObjects.end()) {
                gameLogic.removeObject(x, y);
                if (rand() % 7 == 0) {
                    if (rand() % 2 == 0) {
                        gameLogic.addObject(new PowerupBomb(window, gameLogic, x, y));
                    } else {
                        gameLogic.addObject(new PowerupSpeed(window, gameLogic, x, y));
                    }
                } else {
                    gameLogic.addObject(new Explosion(window, gameLogic, x, y));
                }
            } else {
                condition = false;
            }
        }
    }
}

void Bomb::draw() {
    window.drawImage(sprite, &rect);
}

void Bomb::event(SDL_Event ev) {
}
