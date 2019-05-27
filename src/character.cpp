#include "../include/character.hpp"

int Character::count = 0;

Character::Character(Window& wind, GameLogic& logic) : InteractiveObject(wind, logic) {
    setSprite(window.loadSurface(("Sprites/Character/" + std::to_string(index) + "/Walk_Down/3.png").c_str()));
}
Character::Character(Window& wind, GameLogic& logic, Vector2 position): InteractiveObject(wind, logic, position) {
    setSprite(window.loadSurface(("Sprites/Character/" + std::to_string(index) + "/Walk_Down/3.png").c_str()));
    lastPos = position;
}

Character::~Character() {
    if (sprite != NULL) SDL_FreeSurface(sprite);
    sprite = NULL;
}

void Character::process(float delta) {
    if (bombDelayCurr > 0) bombDelayCurr -= delta;

    if (walkDelayCurr <= 0) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[SDL_SCANCODE_W]) {
            if (move(Vector2(0, -1))) {
                lastDir = 0;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[SDL_SCANCODE_S]) {
            if (move(Vector2(0, 1))) {
                lastDir = 2;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[SDL_SCANCODE_A]) {
            if (move(Vector2(-1, 0))) {
                lastDir = 3;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[SDL_SCANCODE_D]) {
            if (move(Vector2(1, 0))) {
                lastDir = 1;
                walkDelayCurr = walkDelay;
            }
        }
    }

    if (walkDelayCurr > 0) {
        walkDelayCurr -= delta;
        if (walkDelayCurr < 0) walkDelayCurr = 0;
        moveAnimationOffset = (lastPos - pos) * cellSize * (walkDelayCurr / walkDelay);
    } else {
        moveAnimationOffset *= 0;
    }
}

bool Character::move(Vector2 dist) {
    if (!gameLogic.moveObject(this, pos + dist)) {
        if (gameLogic.getObjectName(pos + dist) == "powerupSpeed") {
            if (walkDelay > 0.03) walkDelay -= 0.02;
            gameLogic.removeObject(pos + dist);
            if (gameLogic.moveObject(this, pos + dist)) {
                lastPos = pos - dist;
                return true;
            }
        } else if (gameLogic.getObjectName(pos + dist) == "powerupBomb") {
            bombStepAdjust += 1;
            gameLogic.removeObject(pos + dist);
            if (gameLogic.moveObject(this, pos + dist)) {
                lastPos = pos - dist;
                return true;
            }
        }
    } else {
        lastPos = pos - dist;
        return true;
    }
    return false;
}

void Character::draw() const {
    Rect tmpRect = Rect(rect);
    tmpRect.position += moveAnimationOffset;
    window.drawImage(sprite, tmpRect);
}

void Character::event(const SDL_Event& ev) {
    if (ev.type == SDL_KEYDOWN) {
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == SDLK_e) {
            if (bombDelayCurr <= 0) {
                Vector2 bombPos = pos;
                switch (lastDir) {
                    case 0:
                        bombPos.y(pos.y() + 1);
                        break;
                    case 1:
                        bombPos.x(pos.x() - 1);
                        break;
                    case 2:
                        bombPos.y(pos.y() - 1);
                        break;
                    case 3:
                        bombPos.x(pos.x() + 1);
                        break;
                }
                Bomb* bomb = new Bomb(window, gameLogic, bombPos);
                bomb->adjustDelay(bombStepAdjust);
                gameLogic.addObject(bomb);
                bombDelayCurr = bombDelay;
            }
        }
    }
}
