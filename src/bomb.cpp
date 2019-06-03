#include "../include/bomb.hpp"
#include "../include/gameLogic.hpp"

Bomb::Bomb(Window& wind, GameLogic& logic, Vector2 position): InteractiveObject(wind, logic, position) {
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
                addExplosion(Vector2(explosionStep, 0), right);
                addExplosion(Vector2(-explosionStep, 0), left);
                addExplosion(Vector2(0, explosionStep), down);
                addExplosion(Vector2(0, -explosionStep), up);
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

void Bomb::addExplosion(Vector2 position, bool &condition) {
    if (!condition) return;
    
    position += pos;
    if (!gameLogic.isOccupied(position)) {
        gameLogic.addObject(new Explosion(window, gameLogic, position));
    } else {
        if (std::find(destructibleObjects.begin(), destructibleObjects.end(), gameLogic.getObjectName(position)) != destructibleObjects.end()) {
            gameLogic.removeObject(position);
            if (rand() % 7 == 0) {
                if (rand() % 3 == 0) {
                    gameLogic.addObject(new PowerupSpeed(window, gameLogic, position));
                } else {
                    gameLogic.addObject(new PowerupBomb(window, gameLogic, position));
                }
            } else {
                gameLogic.addObject(new Explosion(window, gameLogic, position));
            }
        } else {
            condition = false;
        }
    }
}
