// Bomb class
#pragma once

#include <set>
#include <algorithm>
#include "explosion.hpp"
#include "interactiveObject.hpp"
#include "powerupBomb.hpp"
#include "powerupSpeed.hpp"


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
    int endExplosionStep = 3;
    float explosionStepTime = 0.025;

    const std::set<std::string> destructibleObjects = {"character", "wallDestr"};

    void addExplosion(int x, int y, bool &condition);
    
  public:
    std::string name() const { return "bomb"; }
    Bomb(Window& wind, GameLogic& logic, int x, int y);
    ~Bomb();
    void adjustDelay(int amount) { endExplosionStep += amount; }
    void process(float delta);
    void event(const SDL_Event& ev) {};
    void draw() const { window.drawImage(sprite, rect); };
};
