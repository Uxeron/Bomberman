#include "../include/explosion.hpp"
#include "../include/gameLogic.hpp"

Explosion::Explosion(Window& wind, GameLogic& logic, Vector2 position)
    : InteractiveObject(wind, logic, position) {
    sprites[0] = window.loadSurface("Sprites/Explosion/0.png");
    sprites[1] = window.loadSurface("Sprites/Explosion/1.png");
    sprites[2] = window.loadSurface("Sprites/Explosion/2.png");
    sprites[3] = window.loadSurface("Sprites/Explosion/3.png");
    sprites[4] = window.loadSurface("Sprites/Explosion/4.png");
    sprites[5] = window.loadSurface("Sprites/Explosion/5.png");

    setSprite(sprites[0]);
    currTime = stepTime;
}

Explosion::~Explosion() {
    for(SDL_Surface* spr : sprites) {
        SDL_FreeSurface(spr);
    }
    sprite = NULL;
}

void Explosion::process(float delta) {
    currTime -= delta;
    if (currTime < 0.0) {
        currTime = stepTime;
        step++;
        if(step >= 6) {
            remove = true;
        } else {
            setSprite(sprites[step]);
        }
    }
}
