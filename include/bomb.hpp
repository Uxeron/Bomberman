// Bomb class
#pragma once

#include "explosion.hpp"
#include "interactiveObject.hpp"


class Bomb: public InteractiveObject {
    bool up = true, down = true, left = true, right = true;
    bool exploding = false;
    SDL_Surface* sprites[2];
    // Bomb steps
    int step = 0;
    int explodeOnStep = 10;
    float stepTime = 0.2;
    float currTime;
    // Explosion steps
    int explosionStep = 0;
    int endExplosionStep = 5;
    float explosionStepTime = 0.025;

    void addExplosion(int x, int y, bool &condition);
    
  public:
    std::string name() { return "bomb"; }
    Bomb(Window& wind, GameLogic& logic, int x, int y);
    ~Bomb();
    void process(float delta);
    void event(SDL_Event ev);
    void draw();
};
