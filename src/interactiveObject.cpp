#include "../include/interactiveObject.hpp"
#include "../include/gameLogic.hpp"

InteractiveObject::InteractiveObject(Window& wind, GameLogic& logic)
    : Object(wind, GameLogic::getSqSize()), gameLogic(logic){};
InteractiveObject::InteractiveObject(Window& wind, GameLogic& logic, Vector2 position)
    : Object(wind, GameLogic::getSqSize(), position), gameLogic(logic){};

InteractiveObject::~InteractiveObject() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}
