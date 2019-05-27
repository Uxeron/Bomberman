#include "../include/powerupSpeed.hpp"

PowerupSpeed::PowerupSpeed(Window& wind, GameLogic& logic, int x, int y): InteractiveObject(wind, logic, x, y) {
    setSprite(window.loadSurface("Sprites/powerupSpeed.png"));
}

PowerupSpeed::~PowerupSpeed() {}

void PowerupSpeed::process(float delta) {
    if (gameLogic.getObjectName(posX, posY) != name()) {
        gameLogic.addObjectnoList(this);
    }
}
