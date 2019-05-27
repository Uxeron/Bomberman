#include "../include/powerupBomb.hpp"

PowerupBomb::PowerupBomb(Window& wind, GameLogic& logic, Vector2 position)
    : InteractiveObject(wind, logic, position) {
    setSprite(window.loadSurface("Sprites/powerupBomb.png"));
}

PowerupBomb::~PowerupBomb() {}

void PowerupBomb::process(float delta) {
    if (gameLogic.getObjectName(pos) != name()) {
        gameLogic.addObjectnoList(this);
    }
}
