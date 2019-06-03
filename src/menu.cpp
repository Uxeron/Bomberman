#include "../include/menu.hpp"

Menu::Menu() {
    window = std::make_unique<Window> (menuSize.x(), menuSize.y(), "Bomberman!");

    menuTitleSprite = window->loadSurface("Sprites/UI/Title.png");
    menuArrowUpSprite = window->loadSurface("Sprites/UI/ArrowUp.png");
    menuArrowDownSprite = window->loadSurface("Sprites/UI/ArrowDown.png");
    menuItemSprite = window->loadSurface("Sprites/UI/MenuItem.png");
    menuItemSelectedSprite = window->loadSurface("Sprites/UI/MenuItemSelected.png");

    
    std::string path;
    std::ifstream mapsList;
    int i = 0;

    mapsList.open("Maps/maps.txt");
    while (std::getline(mapsList, path)) {
        menuItems.push_back(std::move(std::make_unique<MenuItem> (i++, window->loadSurface("Sprites/UI/MenuItem.png"), ("Maps/" + path).c_str())));
        debugWrite("Item " << i << " created");
    }
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

            if (!e.key.repeat && e.key.state == SDL_PRESSED && e.key.keysym.sym == SDLK_w)
                    if (selectedItem > 0) selectedItem--;
            if (!e.key.repeat && e.key.state == SDL_PRESSED && e.key.keysym.sym == SDLK_s)
                    if (selectedItem < menuItems.size() - 1) selectedItem++;
        }

        // Clear screen
        window->fillScreen(107, 64, 28);

        drawStaticMenu();

        for (auto it = menuItems.begin(); it != menuItems.end(); it++) {
            if (selectedItem == 0) {
                if ((*it)->index > selectedItem + 2) continue;

                window->drawImage((*it)->sprite, menuRects[(*it)->index]);
                if ((*it)->index == selectedItem)
                    window->drawImage(menuItemSelectedSprite, menuRects[0]);
            } else if (selectedItem == menuItems.size() - 1) {
                if ((*it)->index < selectedItem - 2) continue;

                window->drawImage((*it)->sprite, menuRects[(*it)->index - selectedItem + 2]);
                if ((*it)->index == selectedItem)
                    window->drawImage(menuItemSelectedSprite, menuRects[2]);
            } else {
                if ((*it)->index < selectedItem - 1 || (*it)->index > selectedItem + 1) continue;
            
                window->drawImage((*it)->sprite, menuRects[(*it)->index - selectedItem + 1]);
                if ((*it)->index == selectedItem)
                    window->drawImage(menuItemSelectedSprite, menuRects[1]);
            }
        }

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
