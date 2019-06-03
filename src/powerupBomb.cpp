#include "../include/powerupBomb.hpp"
#include "../include/gameLogic.hpp"

PowerupBomb::PowerupBomb(Window& wind, GameLogic& logic, Vector2 position)
    : InteractiveObject(wind, logic, position) {
    setSprite(window.loadSurface("Sprites/powerupBomb.png"));
}

PowerupBomb::~PowerupBomb() {}
