#include "../include/character.hpp"
#include "../include/gameLogic.hpp"

int Character::count = 0;

Character::Character(Window& wind, GameLogic& logic) : InteractiveObject(wind, logic) {
    loadSprites();
    selectControls();
}

Character::Character(Window& wind, GameLogic& logic, Vector2 position): InteractiveObject(wind, logic, position) {
    loadSprites();
    selectControls();
    lastPos = position;
}

Character::~Character() {
    count--;

    for (int i = 0; i < 4; i++)
        for (SDL_Surface* spr : sprites[i])
            SDL_FreeSurface(spr);

    sprite = NULL;
}

void Character::process(float delta) {
    if (bombDelayCurr > 0) bombDelayCurr -= delta;

    if (walkDelayCurr <= 0) {
        const Uint8 *currentKeyStates = SDL_GetKeyboardState(NULL);
        if (currentKeyStates[keys[0]]) {
            if (move(Vector2(0, -1))) {
                lastDir = 0;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[keys[1]]) {
            if (move(Vector2(-1, 0))) {
                lastDir = 1;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[keys[2]]) {
            if (move(Vector2(0, 1))) {
                lastDir = 2;
                walkDelayCurr = walkDelay;
            }
        } else if (currentKeyStates[keys[3]]) {
            if (move(Vector2(1, 0))) {
                lastDir = 3;
                walkDelayCurr = walkDelay;
            }
        }
    }

    if (walkDelayCurr > 0) {
        walkDelayCurr -= delta;
        if (walkDelayCurr < 0) walkDelayCurr = 0;
        moveAnimationOffset = (lastPos - pos) * cellSize * (walkDelayCurr / walkDelay);
        currAnimFrameDelay -= delta;
        if (currAnimFrameDelay < 0) {
            currAnimFrameDelay = animFrameDelay;
            animIndex += 1;
            if (animIndex >= 4)
                animIndex = 0;
        }
    } else {
        moveAnimationOffset *= 0;
        animIndex = 4;
    }

    setSprite(sprites[lastDir][animIndex]);
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
        if (!ev.key.repeat && ev.key.state == SDL_PRESSED && ev.key.keysym.sym == keys[4]) {
            if (bombDelayCurr <= 0) {
                Vector2 bombPos = pos;
                switch (lastDir) {
                    case 0:
                        bombPos.y(pos.y() + 1);
                        break;
                    case 1:
                        bombPos.x(pos.x() + 1);
                        break;
                    case 2:
                        bombPos.y(pos.y() - 1);
                        break;
                    case 3:
                        bombPos.x(pos.x() - 1);
                        break;
                }
                auto bomb = new Bomb(window, gameLogic, bombPos);
                bomb->adjustDelay(bombStepAdjust);
                gameLogic.addObject(bomb);
                bombDelayCurr = bombDelay;
            }
        }
    }
}

void Character::loadSprites() {
    std::string index1 = std::to_string(index);
    int j;
    std::string index2;
    for(int i = 0; i < 5; i++) {
        j = i;
        if (i == 3) j = 1;
        if (i == 4) j = 3;
        index2 = std::to_string(j);
        sprites[0][i] = window.loadSurface(("Sprites/Character/" + index1 + "/Walk_Up/" + index2 + ".png").c_str());
        sprites[1][i] = window.loadSurface(("Sprites/Character/" + index1 + "/Walk_Left/" + index2 + ".png").c_str());
        sprites[2][i] = window.loadSurface(("Sprites/Character/" + index1 + "/Walk_Down/" + index2 + ".png").c_str());
        sprites[3][i] = window.loadSurface(("Sprites/Character/" + index1 + "/Walk_Right/" + index2 + ".png").c_str());
    }

    setSprite(sprites[2][4]);
}

void Character::selectControls() {
    int controls[4][5] = {
        {SDL_SCANCODE_W, SDL_SCANCODE_A, SDL_SCANCODE_S, SDL_SCANCODE_D, SDLK_e},
        {SDL_SCANCODE_T, SDL_SCANCODE_F, SDL_SCANCODE_G, SDL_SCANCODE_H, SDLK_y},
        {SDL_SCANCODE_I, SDL_SCANCODE_J, SDL_SCANCODE_K, SDL_SCANCODE_L, SDLK_o},
        {SDL_SCANCODE_UP, SDL_SCANCODE_LEFT, SDL_SCANCODE_DOWN, SDL_SCANCODE_RIGHT, SDLK_RCTRL}
    };

    for(int i = 0; i < 5; i ++) keys[i] = controls[index][i];
}
