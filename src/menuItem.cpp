#include "../include/menuItem.hpp"

void MenuItem::writeName() {
    std::string mapName = path;
    std::size_t len = mapName.find_last_of('.');
    len -= 5;
    if (len > 15) len = 15;
    mapName = mapName.substr(5, len);
    SDL_Surface* text = TTF_RenderText_Shaded(font, mapName.c_str(), fgCol, bgCol);
    SDL_Rect textLocation = { textPos.x(), textPos.y(), 0, 0 };
    SDL_BlitSurface(text, NULL, sprite, &textLocation);
    SDL_FreeSurface(text);
}
