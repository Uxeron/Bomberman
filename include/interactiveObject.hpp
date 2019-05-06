// The base class for any object that can be interacted with (characters, bombs, etc)
#pragma once

#include "object.hpp"
#include "gameLogic.hpp"

class InteractiveObject: public Object {
  protected:
    GameLogic& gameLogic;

  public:
   InteractiveObject(Window& wind, GameLogic& logic)
       : Object(wind, logic.getSqSize()), gameLogic(logic) {};
   InteractiveObject(Window& wind, GameLogic& logic, int x, int y)
       : Object(wind, logic.getSqSize(), x, y), gameLogic(logic) {};

   virtual void process(float delta) = 0;
   virtual void event(SDL_Event ev) = 0;
};
