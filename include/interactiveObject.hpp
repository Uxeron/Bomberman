// The base class for any object that can be interacted with (characters, bombs, etc)
#pragma once

#include "object.hpp"

class GameLogic;

class InteractiveObject : public Object {
   protected:
    GameLogic& gameLogic;

  public:
    InteractiveObject(Window& wind, GameLogic& logic);
    InteractiveObject(Window& wind, GameLogic& logic, Vector2 position);
    
    virtual ~InteractiveObject() = 0;

    virtual void process(float delta) = 0;
    virtual void event(SDL_Event const& ev) = 0;
};
