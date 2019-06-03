#include "../include/menuItem.hpp"

void MenuItem::writeName() {
    // Get map name from map file path
    std::string mapName = path;
    std::size_t len = mapName.find_last_of('.');
    len -= 5;
    if (len > 15) len = 15; // Limit name length to 15 characters
    mapName = mapName.substr(5, len);

    // Render the text
    SDL_Surface* text = TTF_RenderText_Shaded(font, mapName.c_str(), fgCol, bgCol);

    // Draw the text on the sprite
    SDL_Rect textLocation = { textPos.x(), textPos.y(), 0, 0 };
    SDL_BlitSurface(text, NULL, sprite, &textLocation);
    SDL_FreeSurface(text);
}
