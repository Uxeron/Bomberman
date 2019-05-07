#include "../include/powerupBomb.hpp"

PowerupBomb::PowerupBomb(Window& wind, GameLogic& logic, int x, int y): InteractiveObject(wind, logic, x, y) {
    setSprite(window.loadSurface("Sprites/powerupBomb.png"));
}

PowerupBomb::~PowerupBomb() {}

void PowerupBomb::process(float delta) {
    if (gameLogic.getObjectName(posX, posY) != name()) {
        gameLogic.addObjectnoList(this);
    }
}

void PowerupBomb::draw() { window.drawImage(sprite, &rect); }

void PowerupBomb::event(SDL_Event ev) {}
