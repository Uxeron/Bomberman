#include "../include/bomb.hpp"

Bomb::Bomb(Window& wind, GameGrid& grid, int x, int y): InteractiveObject(wind, grid, x, y) {
    sprites[0] = window.loadSurface("Sprites/Bomb/0.png");
    sprites[1] = window.loadSurface("Sprites/Bomb/1.png");

    setSprite(sprites[0]);
    currTime = stepTime;
}

Bomb::~Bomb() {
    for (SDL_Surface *spr : sprites){
        SDL_FreeSurface(spr);
    }
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
                objList.push(new Explosion(window, gameGrid, posX + explosionStep, posY));
                objList.push(new Explosion(window, gameGrid, posX - explosionStep, posY));
                objList.push(new Explosion(window, gameGrid, posX, posY + explosionStep));
                objList.push(new Explosion(window, gameGrid, posX, posY - explosionStep));
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

void Bomb::draw() {
    window.drawImage(sprite, &rect);
}

void Bomb::event(SDL_Event ev) {
}
