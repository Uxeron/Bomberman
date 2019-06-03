#include "../include/menu.hpp"

Menu::Menu() {
    window = std::make_unique<Window> (menuSize.x(), menuSize.y(), "Bomberman!");

    menuTitleSprite = window->loadSurface("Sprites/UI/Title.png");
    menuArrowUpSprite = window->loadSurface("Sprites/UI/ArrowUp.png");
    menuArrowDownSprite = window->loadSurface("Sprites/UI/ArrowDown.png");
    menuItemSprite = window->loadSurface("Sprites/UI/MenuItem.png");
    menuItemSelectedSprite = window->loadSurface("Sprites/UI/MenuItemSelected.png");
}

Menu::~Menu() {
    SDL_FreeSurface(menuTitleSprite);
    SDL_FreeSurface(menuArrowUpSprite);
    SDL_FreeSurface(menuArrowDownSprite);
    SDL_FreeSurface(menuItemSprite);
    SDL_FreeSurface(menuItemSelectedSprite);

    menuItems.clear();
}

std::unique_ptr<GameLogic> Menu::menuLoop() {
    // Main loop flag
    bool quit = false;

    // Event handler
    SDL_Event e;

    debugWrite("Starting main loop");
    while (!quit) {
        // Handle events on queue
        while (SDL_PollEvent(&e) != 0) {
            // User pressed x
            if (e.type == SDL_QUIT) quit = true;
        }

        // Clear screen
        window->fillScreen(107, 64, 28);

        drawStaticMenu();

        // Update the screen
        window->update();

        // Limit framerate
        limitFPS();
    }
    return NULL;
}

void Menu::limitFPS() {
    if (prevTime + FRAME_TIME > SDL_GetTicks())
        SDL_Delay(prevTime + FRAME_TIME - SDL_GetTicks());
    prevTime = SDL_GetTicks();
}

void Menu::drawStaticMenu() {
    window->drawImage(menuTitleSprite, menuTitleRect);
    window->drawImage(menuArrowUpSprite, arrowUpRect);
    window->drawImage(menuArrowDownSprite, arrowDownRect);
}
