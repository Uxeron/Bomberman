#pragma once

#ifdef __linux__
  #include <SDL2/SDL.h>
  #include <SDL2/SDL_image.h>
#else
  #include "../SDL2/include/SDL.h"
  #include "../SDL2/include/SDL_image.h"
#endif

#include "gameLogic.hpp"
#include "vector2.hpp"
#include "menuItem.hpp"
#include <memory>
#include <iostream>
#include <vector>

class Menu {
    const int FPS = 60;
    const int FRAME_TIME = 1000 / FPS;

    const Vector2 menuSize = Vector2(600, 700);

    const Rect menuTitleRect = { Vector2(0, 0), Vector2(600, 200) };
    const Rect arrowUpRect = { Vector2(50, 200), Vector2(500, 50) };
    const Rect arrowDownRect = { Vector2(50, 550), Vector2(500, 50) };

    const Rect menuRects[3] = { { Vector2(50, 250), Vector2(500, 100) },
                                { Vector2(50, 350), Vector2(500, 100) },
                                { Vector2(50, 450), Vector2(500, 100) } };

    Uint32 prevTime = 0;
    std::unique_ptr<Window> window;

    SDL_Surface* menuTitleSprite;
    SDL_Surface* menuArrowUpSprite;
    SDL_Surface* menuArrowDownSprite;
    SDL_Surface* menuItemSprite;
    SDL_Surface* menuItemSelectedSprite;
    
    int selectedItem = 0;

    std::vector<MenuItem> menuItems;

    std::unique_ptr<GameLogic> gameLogic;

    void drawStaticMenu();
    void limitFPS();
  public:
    Menu();
    ~Menu();

    std::unique_ptr<GameLogic> menuLoop();
};
