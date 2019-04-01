#include "bomb.hpp"

Bomb::Bomb(Window *wind, int x, int y): InteractiveObject(wind, x, y) {
    sprites[0] = window->loadSurface("Sprites/Bomb/0.png");
    sprites[1] = window->loadSurface("Sprites/Bomb/1.png");

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
                objList.push_back(new Explosion(window, getRect()->x + explosionStep * 32, getRect()->y));
                objList.push_back(new Explosion(window, getRect()->x - explosionStep * 32, getRect()->y));
                objList.push_back(new Explosion(window, getRect()->x, getRect()->y + explosionStep * 32));
                objList.push_back(new Explosion(window, getRect()->x, getRect()->y - explosionStep * 32));
            }
        } else {
            currTime = stepTime;
            step++;
            if (step >= explodeOnStep) {
                exploding = true;
                currTime = explosionStepTime;
                objList.push_back(new Explosion(window, getRect()->x, getRect()->y));
            }
            else {
                setSprite(sprites[step%2]);
            }
        }
    }
}

void Bomb::draw() {
    window->drawImage(sprite, &rect);
}

void Bomb::event(SDL_Event ev) {
}
