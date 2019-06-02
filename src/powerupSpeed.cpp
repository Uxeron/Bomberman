#include "../include/powerupSpeed.hpp"
#include "../include/gameLogic.hpp"

PowerupSpeed::PowerupSpeed(Window& wind, GameLogic& logic, Vector2 position)
    : InteractiveObject(wind, logic, position) {
    setSprite(window.loadSurface("Sprites/powerupSpeed.png"));
}

PowerupSpeed::~PowerupSpeed() {}

void PowerupSpeed::process(float delta) {
    if (gameLogic.getObjectName(pos) != name()) {
        gameLogic.addObjectnoList(this);
    }
}
